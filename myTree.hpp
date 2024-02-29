#pragma once

#include <iostream>
#include <filesystem>
#include <algorithm>
#include "myColors.hpp"

struct TreeNode
{
    std::string full_path;
    std::string name;
    bool is_file;
    std::vector<TreeNode *> children;

    TreeNode(const std::string &fullPath, const std::string &nodeName, bool isFile = false)
        : full_path(fullPath), name(nodeName), is_file(isFile) {}

    void addChild(TreeNode *child)
    {
        children.push_back(child);
    }

    bool isLeaf() const
    {
        return children.empty();
    }
};

void build_tree(const std::string &directory, TreeNode *parent, bool show_hidden = false, const std::string &prefix = "")
{
    try
    {
        std::vector<std::string> items;
        for (const auto &entry : std::filesystem::directory_iterator(directory))
        {
            std::string item = entry.path().filename().string();
            items.push_back(item);
        }
        std::sort(items.begin(), items.end());

        for (size_t index = 0; index < items.size(); ++index)
        {
            std::string item = items[index];
            std::string full_path = directory + "/" + item;
            bool is_last = index == items.size() - 1;

            if (!show_hidden && item[0] == '.')
            {
                continue;
            }

            std::cout << prefix << (is_last ? "└── " : "├── ");

            TreeNode *node = new TreeNode(full_path, item, std::filesystem::is_regular_file(full_path));
            parent->addChild(node);

            if (std::filesystem::is_directory(full_path))
            {
                // Print directory name with appropriate color
                std::string color = get_file_color(full_path, item[0] == '.');
                print_colored_text(item, color);
                // Recursively traverse directories
                build_tree(full_path, node, show_hidden, prefix + (is_last ? "    " : "│   "));
            }
            else
            {
                // Print file name with appropriate color
                std::string color = get_file_color(full_path, item[0] == '.');
                print_colored_text(item, color);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to count directories recursively
int count_directories(TreeNode *node)
{
    int count = 0;
    if (!node)
        return 0;

    for (const auto &child : node->children)
    {
        if (!child->is_file)
        {
            count++;                           // Increment count for directory
            count += count_directories(child); // Recursively count directories in children
        }
    }
    return count;
}

// Function to count files recursively
int count_files(TreeNode *node)
{
    int count = 0;
    if (!node)
        return 0;

    for (const auto &child : node->children)
    {
        if (child->is_file)
        {
            count++; // Increment count for file
        }
        else
        {
            count += count_files(child); // Recursively count files in children
        }
    }
    return count;
}

void print_tree(const std::string &path, bool show_hidden)
{
    TreeNode root(path, ".", false); // Assuming root directory is not hidden
    print_colored_text(path, COLOR_FOLDER);
    build_tree(path, &root, show_hidden);

    // Optionally, you can print the count of directories and files
    std::cout << std::endl;
    std::cout << count_directories(&root) << " directories, " << count_files(&root) << " files" << std::endl;
}
