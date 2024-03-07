/**
 ******************************************************************************
 * @file    myTree.hpp
 * @brief   Declarations of functions and classes for building and printing directory trees.
 *          Includes classes for representing tree nodes and functions for building, counting, and printing trees.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Represents a node in a directory tree.
 */
class TreeNode
{
public:
    std::string full_path; /**< The full path of the node. */
    std::string name; /**< The name of the node. */
    bool is_file; /**< Indicates whether the node is a file. */
    std::vector<TreeNode *> children; /**< Children nodes of the current node. */

    /**
     * @brief Constructor for TreeNode class.
     * @param fullPath The full path of the node.
     * @param nodeName The name of the node.
     * @param isFile Indicates whether the node is a file.
     */
    TreeNode(const std::string &fullPath, const std::string &nodeName, bool isFile);

    /**
     * @brief Adds a child node to the current node.
     * @param child Pointer to the child node to be added.
     */
    void addChild(TreeNode *child);

    /**
     * @brief Checks if the node is a leaf node (has no children).
     * @return true if the node is a leaf node, false otherwise.
     */
    bool isLeaf() const;
};

/**
 * @brief Builds a tree representing the directory structure.
 * @param directory The path to the directory to build the tree from.
 * @param parent The parent node of the current directory.
 * @param show_hidden Flag indicating whether to include hidden files/directories.
 * @param prefix Prefix to prepend to each line in the tree (for formatting).
 */
void build_tree(const std::string &directory, TreeNode *parent, bool show_hidden = false, const std::string &prefix = "");

/**
 * @brief Counts the number of directories recursively starting from a given node.
 * @param node The starting node for counting directories.
 * @return The number of directories.
 */
int count_directories(TreeNode *node);

/**
 * @brief Counts the number of files recursively starting from a given node.
 * @param node The starting node for counting files.
 * @return The number of files.
 */
int count_files(TreeNode *node);

/**
 * @brief Prints the directory tree rooted at the specified path.
 * @param path The root path of the directory tree.
 * @param show_hidden Flag indicating whether to include hidden files/directories.
 */
void print_tree(const std::string &path, bool show_hidden);
