#pragma once

#include <stdio.h>
#include <stdlib.h>

struct address {
    char country[40] = "";
    char city[40] = "";
    char street[50] = "";
    char house_num[10] = "";
    address* next = NULL;
    address* prior = NULL;
};

struct list {
    address* head = NULL;
    address* tail = NULL;
    size_t len = 0;
};

enum ListFunc {
    STOP_PROGRAM        = 0,
    PRINT_LIST          = 1,
    ADD_TO_HEAD         = 2,
    ADD_TO_TAIL         = 3,
    ADD_NEXT_MATCH      = 4,
    ADD_PRIOR_MATCH     = 5,
    ADD_TO_MIDDLE       = 6,
    REMOVE_FROM_MIDDLE  = 7,
    REMOVE_MATCH        = 8,
    REMOVE_BY_INDEX     = 9,
    REMOVE_FROM_TAIL    = 10,
    REMOVE_FROM_HEAD    = 11
};

void print_funcs_list();
void print_list(list* list_address);

void insert_node(list* list_address, address* prior, address* next);
void remove_node(list* list_address, address* curr);
address* search_node(list* list_address);
size_t compare_strings(char* searched, char* curr);

void add_to_head(list* list_address);
void add_to_tail(list* list_address);
void add_next_match(list* list_address);
void add_prior_match(list* list_address);
void add_to_middle(list* list_address);