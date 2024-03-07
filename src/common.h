#pragma once

#include <stdio.h>
#include <stdlib.h>

int len_of_node = 150;

struct address {
    char country[40] = "";
    char city[40] = "";
    char street[50] = "";
    char house_num[10] = "";
    address* next = nullptr;
    address* prior = nullptr;
};

struct list {
    address* head = nullptr;
    address* tail = nullptr;
    size_t len = 0;
    bool is_work = true;
};

enum ListFunc {
    STOP_PROGRAM        = 0,
    PRINT_LIST          = 1,
    ADD_TO_HEAD         = 2,
    ADD_TO_TAIL         = 3,
    ADD_NEXT_MATCH      = 4,
    ADD_PRIOR_MATCH     = 5,
    ADD_TO_MIDDLE       = 6,
    REMOVE_FROM_HEAD    = 7,
    REMOVE_FROM_TAIL    = 8,
    REMOVE_FROM_MIDDLE  = 9,
    REMOVE_MATCH        = 10,
    REMOVE_BY_INDEX     = 11,
};

list create_list(FILE* list_file);
void print_funcs_list();
void print_list(list* list_address);

address* get_user_node();
void insert_node(list* list_address, address* prior, address* next);
void remove_node(list* list_address, address* curr);
address* search_node(list* list_address);
size_t compare_strings(char* searched, char* curr);

void stop_program(list* list_address);

void add_to_head(list* list_address);
void add_to_tail(list* list_address);
void add_next_match(list* list_address);
void add_prior_match(list* list_address);
void add_to_middle(list* list_address);

void remove_from_head(list* list_address);
void remove_from_tail(list* list_address);
void remove_from_middle(list* list_address);
void remove_match(list* list_address);
void remove_by_index(list* list_address);