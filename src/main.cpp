#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

int main() {
    FILE* list_file = fopen("list.txt", "r");
    list list_address = create_list(list_file);
    fclose(list_file);

    ListFunc next_act;
    print_funcs_list();
    while (true) {
        printf("\nChoose action: ");
        scanf("%d", (int*) &next_act);
        switch (next_act) {
            case STOP_PROGRAM:
                stop_program(&list_address);
                exit(0);
            case PRINT_LIST:
                print_list(&list_address);
                break;
            case ADD_TO_HEAD:
                add_to_head(&list_address);
                break;
            case ADD_TO_TAIL:
                add_to_tail(&list_address);
                break;
            case ADD_NEXT_MATCH:
                add_next_match(&list_address);
                break;
            case ADD_PRIOR_MATCH:
                add_prior_match(&list_address);
                break;
            case ADD_TO_MIDDLE:
                add_to_middle(&list_address);
                break;
            case REMOVE_FROM_HEAD:
                remove_from_head(&list_address);
                break;
            case REMOVE_FROM_TAIL:
                remove_from_tail(&list_address);
                break;
            case REMOVE_FROM_MIDDLE:
                remove_from_middle(&list_address);
                break;
            case REMOVE_MATCH:
                remove_match(&list_address);
                break;
            case REMOVE_BY_INDEX:
                remove_by_index(&list_address);
                break;
            default:
                printf("An unexpected entry has been made. To terminate the program, enter '0'.");
                break;
        }
    }
}
list create_list(FILE* list_file) {
    if (!list_file) {
        printf("Warning! File 'list.txt' is not exist. An empty list will be created\n");
        return {nullptr, nullptr, 0, true};
    }
    else {
        size_t list_len = 0;
        fscanf(list_file, "%lld\n", &list_len);
        address* head = nullptr;
        address* tail = nullptr;
        for (size_t i = 0; i < list_len; i++) {
            address* new_node = (address*) calloc(1, sizeof(address));
            fscanf(list_file, "%[^;]; %[^;]; %[^;]; %s\n", new_node->country, 
                new_node->city, new_node->street, new_node->house_num);
            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->next = new_node;
                new_node->prior = tail;
                tail = new_node;
            }
        }
        return {head, tail, list_len, true};
    }
}

void print_funcs_list() {
    printf("List of actions:\nSTOP_PROGRAM - 0\nPRINT_LIST - 1\nADD_TO_HEAD - 2\nADD_TO_TAIL - 3\n"
            "ADD_NEXT_MATCH - 4\nADD_PRIOR_MATCH - 5\nADD_TO_MIDDLE - 6\nREMOVE_FROM_HEAD - 7\nREMOVE_FROM_TAIL - 8\n"
            "REMOVE_FROM_MIDDLE - 9\nREMOVE_MATCH - 10\nREMOVE_BY_INDEX - 11\n");
}

void print_list(list* list_address) {
    address* ptr = list_address->head;
    int index = 0;
    if (ptr == nullptr) {
        printf("List is empty\n");
    }
    else {
        printf("Len of list: %llu\n", list_address->len);
        while (ptr) {
            printf("%d: %s; %s; %s; %s\n", index, ptr->country, ptr->city, ptr->street, ptr->house_num);
            ptr = ptr->next;
            index++;
        }
    }
}

address* get_user_node() {
    address* node = (address*) calloc(1, sizeof(address));
    scanf("\n%[^;]; %[^;]; %[^;]; %[^\n]", node->country, node->city, node->street, node->house_num);
    while (getchar() != '\n');
    return node;
}

void insert_node(list* list_address, address* prior, address* next) {
    printf("Enter new node:\n");
    address* new_node = get_user_node();

    if (prior == nullptr && next == nullptr) {  // Пустой список
        list_address->head = new_node;
        list_address->tail = new_node;
    }
    else if (prior == nullptr) {                // Голова списка
        list_address->head->prior = new_node;
        new_node->next = list_address->head;
        list_address->head = new_node;
    }
    else if (next == nullptr) {                 // Хвост списка
        list_address->tail->next = new_node;
        new_node->prior = list_address->tail;
        list_address->tail = new_node;
    }
    else {
        new_node->prior = prior;
        prior->next = new_node;
        new_node->next = next;
        next->prior = new_node;
    }
    list_address->len = list_address->len + 1;
}

void remove_node(list* list_address, address* curr) {
    if (curr == nullptr) {
        printf("List is empty. Operation cannot be performed\n");
        return;
    }
    else if (curr->prior == nullptr && curr->next == nullptr) {
        if (list_address->is_work) {
            printf("Last item in the list is deleted\n");
        }
        list_address->head = nullptr;
        list_address->tail = nullptr;
    }
    else if (curr->prior == nullptr) {
        curr->next->prior = nullptr;
        list_address->head = curr->next;
    }
    else if (curr->next == nullptr) {
        curr->prior->next = nullptr;
        list_address->tail = curr->prior;
    }
    else {
        curr->next->prior = curr->prior;
        curr->prior->next = curr->next;
    }
    free(curr);
    list_address->len = list_address->len - 1;
}

address* search_node(list* list_address) {
    printf("Enter in the string you're looking for:\n");
    address* searched_node = get_user_node();
    
    size_t min_diff = 140;
    address* matched;
    size_t curr_diff = 0;
    address* ptr = list_address->head;
    
    while (ptr) {
        curr_diff += compare_strings(ptr->country, searched_node->country);
        curr_diff += compare_strings(ptr->city, searched_node->city);
        curr_diff += compare_strings(ptr->street, searched_node->street);
        curr_diff += compare_strings(ptr->house_num, searched_node->house_num);
        if (curr_diff == 0) {
            min_diff = 0;
            matched = ptr;
            break;
        }
        else if (curr_diff < min_diff) {
            matched = ptr;
            min_diff = curr_diff;
        }
        curr_diff = 0;
        ptr = ptr->next;
    }
    free(searched_node);

    if (min_diff == 0) {
        return matched;
    }
    else if (min_diff <= 18) {
        printf("\nNo exact match was found. The closest match was found:\n%s; %s; %s; %s\n"
        "Enter 1 if it is a match and 0 if it is not: ", matched->country, matched->city,
        matched->street, matched->house_num);
        int conitnue = 0;
        scanf("%d", &conitnue);
        if (conitnue) {
            return matched;
        }
        else {
            return nullptr;
        }
    }
    else {
        printf("\nNo exact match was found. The operation was canceled\n");
        return nullptr;
    }
}

size_t compare_strings(char* searched, char* curr) {
    size_t diff = 0;
    while (*searched != '\0') {
        if (*searched == *curr) {
            searched++;
            curr++;
        }
        else if (*searched != *curr && *searched == *(curr + 1) ) {
            diff++;
            curr++;
        }
        else if (*searched != *curr && *(searched + 1) == *curr) {
            diff++;
            searched++;
        }
        else {
            diff++;
            searched++;
            curr++;
        }
    }
    return diff;
}

void stop_program(list* list_address) {
    list_address->is_work = false;
    printf("Do you want to update 'list.txt' with changed list? Input 1 if yes, and 0 if false - ");
    int is_save_data = 0;
    scanf("%d", &is_save_data);
    if (is_save_data == 1) {
        char* output_string = (char*) calloc(list_address->len * len_of_node, sizeof(char));
        address* ptr = list_address->head;
        char* temp = (char*) calloc(10, sizeof(char));
        sprintf(temp, "%llu\n", list_address->len);
        strcat(output_string, temp);
        free(temp);
        while (ptr) {
            char* node = (char*) calloc(len_of_node, sizeof(char));
            sprintf(node, "%s; %s; %s; %s\n", ptr->country, ptr->city, ptr->street, ptr->house_num);
            strcat(output_string, node);
            free(node);
            ptr = ptr->next;
            remove_from_head(list_address);
        }
        FILE* list_file = fopen("list.txt", "w");
        fputs(output_string, list_file);
        fclose(list_file);
        free(output_string);
        printf("The program is corrently terminated. All new data is written to the file\n");
    }
    else {
        while (list_address->head != nullptr) {
            remove_from_head(list_address);
        }
        printf("The program is corrently terminated\n");
    }
    sleep(10);
}

void add_to_head(list* list_address) {
    insert_node(list_address, nullptr, list_address->head);
}

void add_to_tail(list* list_address) {
    insert_node(list_address, list_address->tail, nullptr);
}

void add_next_match(list* list_address) {
    address* searched_node = search_node(list_address);
    if (searched_node != nullptr) {
        insert_node(list_address, searched_node, searched_node->next);
    }
}

void add_prior_match(list* list_address) {
    address* searched_node = search_node(list_address);
    if (searched_node != nullptr) {
        insert_node(list_address, searched_node->prior, searched_node);
    }
}

void add_to_middle(list* list_address) {
    if (list_address->len == 0) {
        printf("List is empty. Add node into head\n");
        add_to_head(list_address);
    }
    else if (list_address->len == 1) {
        add_to_tail(list_address);
    }
    else {
        size_t index = list_address->len / 2;
        address* ptr = list_address->head;
        for (size_t i = 0; i < index; i++) {
            ptr = ptr->next;
        }
        insert_node(list_address, ptr->prior, ptr);
    }
}

void remove_from_head(list* list_address) {
    remove_node(list_address, list_address->head);
}

void remove_from_tail(list* list_address) {
    remove_node(list_address, list_address->tail);
}

void remove_from_middle(list* list_address) {
    if (list_address->len == 0) {
        remove_node(list_address, nullptr);
    }
    else if (list_address->len == 1) {
        remove_node(list_address, list_address->head);
    }
    else {
        size_t index = list_address->len / 2;
        address* ptr = list_address->head;
        for (size_t i = 0; i < index; i++) {
            ptr = ptr->next;
        }
        remove_node(list_address, ptr);
    }
    
}

void remove_match(list* list_address) {
    address* searched_node = search_node(list_address);
    if (searched_node != nullptr) {
        remove_node(list_address, searched_node);
    }
}

void remove_by_index(list* list_address) {
    printf("Enter index of node: ");
    size_t index = 0;
    scanf("%llu", &index);

    address* ptr = list_address->head;
    for (size_t i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    remove_node(list_address, ptr);
}
