#pragma once

#include <string>
#include <vector>

class TreeNode
{
public:
    std::string full_path;
    std::string name;
    bool is_file;
    std::vector<TreeNode *> children;

    TreeNode(const std::string &fullPath, const std::string &nodeName, bool isFile);

    void addChild(TreeNode * child);

    bool isLeaf() const;
};

void build_tree(const std::string &directory, TreeNode *parent, bool show_hidden = false, const std::string &prefix = "");

// Function to count directories recursively
int count_directories(TreeNode *node);

// Function to count files recursively
int count_files(TreeNode *node);

void print_tree(const std::string &path, bool show_hidden);