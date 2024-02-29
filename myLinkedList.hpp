#pragma once

#include "myColors.hpp"
#include "myType.h"

class ListNode
{
public:
    std::string data;
    ListNode *next;

    ListNode(const std::string &data) : data(data), next(nullptr) {}
};

class LinkedList
{
public:
    ListNode *head;

    LinkedList() : head(nullptr) {}

    void insert(const std::string &data)
    {
        ListNode *new_node = new ListNode(data);
        if (!head)
        {
            head = new_node;
        }
        else
        {
            ListNode *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = new_node;
        }
    }
};

LinkedList create_linked_list(const std::vector<std::string> &files, bool show_hidden)
{
    LinkedList linked_list;
    for (const std::string &file : files)
    {
        if (show_hidden || file[0] != '.')
        {
            linked_list.insert(file);
        }
    }
    return linked_list;
}

ListNode *merge_sort_linked_list(ListNode *head, bool reverse = false);

ListNode *split_linked_list(ListNode *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *mid = slow->next;
    slow->next = nullptr;
    return mid;
}

ListNode *merge(ListNode *left, ListNode *right, bool reverse = false)
{
    if (!left)
    {
        return right;
    }
    if (!right)
    {
        return left;
    }

    ListNode *result;
    if ((!reverse && left->data < right->data) || (reverse && left->data > right->data))
    {
        result = left;
        result->next = merge(left->next, right, reverse);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next, reverse);
    }
    return result;
}

ListNode *merge_sort_linked_list(ListNode *head, bool reverse)
{
    if (!head || !head->next)
    {
        return head;
    }

    ListNode *left_half;
    ListNode *right_half;
    left_half = head;
    right_half = split_linked_list(head);

    left_half = merge_sort_linked_list(left_half, reverse);
    right_half = merge_sort_linked_list(right_half, reverse);

    return merge(left_half, right_half, reverse);
}

void print_linked_list(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        std::string color = get_file_color(current->data, false); // Assuming all files are not hidden
        print_colored_text(current->data, color);
        current = current->next;
    }
}

std::vector<std::string> sort_files(const std::string &directory, const SortTypeDef &sort_type, const SortOrderDef &sort_order)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(directory.c_str())) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            std::string filename = entry->d_name;
            if (entry->d_type == DT_REG)
            {
                files.push_back(filename);
            }
        }
        closedir(dir);
    }

    if (sort_type == SORT_NAME)
    {
        std::sort(files.begin(), files.end(), [&](const std::string &a, const std::string &b)
                  { return sort_order == ASC ? a < b : a > b; });
    }
    else if (sort_type == SORT_DATE)
    {
        std::sort(files.begin(), files.end(), [&](const std::string &a, const std::string &b)
                  {
            struct stat stat_a, stat_b;
            stat((directory + "/" + a).c_str(), &stat_a);
            stat((directory + "/" + b).c_str(), &stat_b);
            return sort_order == ASC ? difftime(stat_a.st_mtime, stat_b.st_mtime) < 0 : difftime(stat_a.st_mtime, stat_b.st_mtime) > 0; });
    }
    else if (sort_type == SORT_SIZE)
    {
        std::sort(files.begin(), files.end(), [&](const std::string &a, const std::string &b)
                  {
            struct stat stat_a, stat_b;
            stat((directory + "/" + a).c_str(), &stat_a);
            stat((directory + "/" + b).c_str(), &stat_b);
            return sort_order == ASC ? stat_a.st_size < stat_b.st_size : stat_a.st_size > stat_b.st_size; });
    }
    return files;
}

void sort(const SortTypeDef &sort_type, const SortOrderDef &order, const std::string &path, bool show_hidden)
{
    std::vector<std::string> sorted_files = sort_files(path, sort_type, order);
    for (const std::string &file : sorted_files)
    {
        std::string color = get_file_color(path + "/" + file, file[0] == '.' && !show_hidden);
        if (sort_type == SORT_DATE)
        {
            struct stat stat_buf;
            stat((path + "/" + file).c_str(), &stat_buf);
            std::string date_str = std::to_string(stat_buf.st_mtime);
            print_colored_text(file + " " + date_str, color);
        }
        else if (sort_type == SORT_SIZE)
        {
            struct stat stat_buf;
            stat((path + "/" + file).c_str(), &stat_buf);
            double size = stat_buf.st_size;
            std::string size_str = size < 1024 ? std::to_string(size) + " bytes" : std::to_string(size / 1024) + " KB";
            print_colored_text(file + " " + size_str, color);
        }
        else
        {
            print_colored_text(file, color);
        }
    }
}
