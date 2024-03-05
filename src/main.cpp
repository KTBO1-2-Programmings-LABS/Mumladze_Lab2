#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int main() {
    FILE* list_file = fopen("list.txt", "r");
    size_t list_len = 0;
    fscanf(list_file, "%lld\n", &list_len);
    list list_address = {nullptr, nullptr, list_len};

    for (size_t i = 0; i < list_len; i++) {
        address* new_node = (address*) calloc(1, sizeof(address));
        fscanf(list_file, "%[^;]; %[^;]; %[^;]; %s\n", new_node->country, 
            new_node->city, new_node->street, new_node->house_num);
        if (list_address.head == nullptr) {
            list_address.head = new_node;
            list_address.tail = new_node;
        }
        else {
            list_address.tail->next = new_node;
            new_node->prior = list_address.tail;
            list_address.tail = new_node;
        }
    }

    ListFunc next_act;
    print_funcs_list();
    while (true) {
        printf("\nChoose action: ");
        scanf("%d", (int*) &next_act);
        switch (next_act) {
            case STOP_PROGRAM:
                // Запись в файл и завершение программы
                exit(0);
                break;
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
            case REMOVE_FROM_MIDDLE:
                //
                break;
            case REMOVE_MATCH:
                //
                break;
            case REMOVE_BY_INDEX:
                //
                break;
            case REMOVE_FROM_TAIL:
                //
                break;
            case REMOVE_FROM_HEAD:
                //
                break;
            default:
                printf("An unexpected entry has been made. to terminate the program, enter '0'.");
                break;
        }
    }
}

void print_funcs_list() {
    printf("List of actions:\nSTOP_PROGRAM - 0\nPRINT_LIST - 1\nADD_TO_HEAD - 2\nADD_TO_TAIL - 3\n"
            "ADD_NEXT_MATCH - 4\nADD_PRIOR_MATCH - 5\nADD_TO_MIDDLE - 6\nREMOVE_FROM_MIDDLE - 7\n"
            "REMOVE_MATCH - 8\nREMOVE_BY_INDEX - 9\nREMOVE_FROM_TAIL - 10\nREMOVE_FROM_HEAD - 11\n");
}

void print_list(list* list_address) {
    address* ptr = list_address->head;
    while (ptr) {
        printf("%s; %s; %s; %s\n", ptr->country, ptr->city, ptr->street, ptr->house_num);
        ptr = ptr->next;
    }
}

void insert_node(list* list_address, address* prior, address* next) {
    printf("Enter new node:\n");
    address* new_node = (address*) calloc(1, sizeof(address));
    scanf("\n%[^;]; %[^;]; %[^;]; %[^\n]", new_node->country, new_node->city, new_node->street, new_node->house_num);
    while (getchar() != '\n');

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
}

void remove_node(list* list_address, address* curr) {
    if (curr->prior == nullptr) {
        
    }
    else if (curr->next == nullptr) {

    }
    else {
        
    }
}

address* search_node(list* list_address) {
    printf("Enter in the string you're looking for:\n");
    address* searched_node = (address*) calloc(1, sizeof(address));
    scanf("\n%[^;]; %[^;]; %[^;]; %[^\n]", searched_node->country, 
        searched_node->city, searched_node->street, searched_node->house_num);
    while (getchar() != '\n');
    
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
    else if (min_diff <= 10) {
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
            continue;
        }
        else if (*searched != *curr && (*searched == *(curr + 1) || *(searched + 1) == *curr)) {
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
        ptr = ptr->prior;
        insert_node(list_address, ptr, ptr->next);
    }
}
