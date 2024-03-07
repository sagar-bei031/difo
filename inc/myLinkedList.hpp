#pragma once

#include "myColors.hpp"
#include "myTypeDef.h"
#include <vector>

class ListNode
{
public:
    std::string data;
    ListNode *next;

    ListNode(const std::string &data) : data(data), next(nullptr) {}
};

class LinkedList
{
    ListNode *head;

public:

    LinkedList() : head(nullptr) {}

    void insert(const std::string &data);
};

LinkedList create_linked_list(const std::vector<std::string> &files, bool show_hidden);

ListNode *merge_sort_linked_list(ListNode *head, bool reverse = false);

ListNode *split_linked_list(ListNode *head);

ListNode *merge(ListNode *left, ListNode *right, bool reverse = false);

ListNode *merge_sort_linked_list(ListNode *head, bool reverse);

void print_linked_list(ListNode *head);

bool caseInsensitiveCompare(const std::string &a, const std::string &b);

std::vector<std::string> sort_files(const std::string &directory, const SortTypeDef &sort_type, const SortOrderDef &sort_order);

void sort(const SortTypeDef &sort_type, const SortOrderDef &order, const std::string &path, bool show_hidden);