/**
 ******************************************************************************
 * @file    myTree.cpp
 * @brief   Implementation of functions for building and printing directory trees.
 *          Includes functions for building the tree structure, counting directories and files,
 *          and printing the directory tree with optional inclusion of hidden files/directories.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "myTree.hpp"
#include "myColors.hpp"
#include <iostream>
#include <algorithm>
#include <filesystem>

/**
 * @brief Constructor for TreeNode class.
 * @param fullPath The full path of the node.
 * @param nodeName The name of the node.
 * @param isFile Indicates whether the node is a file.
 */
TreeNode::TreeNode(const std::string &fullPath, const std::string &nodeName, bool isFile)
    : full_path(fullPath), name(nodeName), is_file(isFile) {}

/**
 * @brief Adds a child node to the current node.
 * @param child Pointer to the child node to be added.
 */
void TreeNode::addChild(TreeNode *child)
{
    children.push_back(child);
}

/**
 * @brief Checks if the node is a leaf node (has no children).
 * @return true if the node is a leaf node, false otherwise.
 */
bool TreeNode::isLeaf() const
{
    return children.empty();
}

/**
 * @brief Builds a tree representing the directory structure.
 * @param directory The path to the directory to build the tree from.
 * @param parent The parent node of the current directory.
 * @param show_hidden Flag indicating whether to include hidden files/directories.
 * @param prefix Prefix to prepend to each line in the tree (for formatting).
 */
void build_tree(const std::string &directory, TreeNode *parent, bool show_hidden, const std::string &prefix)
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
                std::cout << std::endl;
                // Recursively traverse directories
                build_tree(full_path, node, show_hidden, prefix + (is_last ? "    " : "│   "));
            }
            else
            {
                // Print file name with appropriate color
                std::string color = get_file_color(full_path, item[0] == '.');
                print_colored_text(item, color);
                std::cout << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Counts the number of directories recursively starting from a given node.
 * @param node The starting node for counting directories.
 * @return The number of directories.
 */
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

/**
 * @brief Counts the number of files recursively starting from a given node.
 * @param node The starting node for counting files.
 * @return The number of files.
 */
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

/**
 * @brief Prints the directory tree rooted at the specified path.
 * @param path The root path of the directory tree.
 * @param show_hidden Flag indicating whether to include hidden files/directories.
 */
void print_tree(const std::string &path, bool show_hidden)
{
    TreeNode root(path, ".", false);
    print_colored_text(path, COLOR_FOLDER);
    std::cout << std::endl;
    build_tree(path, &root, show_hidden);

    // Optionally, you can print the count of directories and files
    std::cout << std::endl;
    std::cout << count_directories(&root) << " directories, " << count_files(&root) << " files" << std::endl;
}
