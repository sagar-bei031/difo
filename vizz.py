#!/usr/bin/env python3

import os


class TreeNode:
    def __init__(self, name, is_file=False):
        self.name = name
        self.is_file = is_file
        self.children = []

    def add_child(self, node):
        self.children.append(node)

    def is_leaf(self):
        return len(self.children) == 0


def build_tree(directory):
    root = TreeNode(os.path.basename(directory))
    if os.path.isdir(directory):
        for item in os.listdir(directory):
            full_path = os.path.join(directory, item)
            if os.path.isdir(full_path):
                root.add_child(build_tree(full_path))
            else:
                root.add_child(TreeNode(item, is_file=True))
    return root


def print_tree(node, prefix='', is_last=True):
    """Prints the tree structure in a visually appealing format.

    Args:
        node: The node to print.
        prefix: The prefix to use for indentation.
        is_last: Whether the current node is the last child of its parent.
    """

    print(prefix, end='')
    print('└── ' if is_last else '├── ', end='')
    print(node.name)

    if not node.is_leaf():
        child_count = len(node.children)
        for i, child in enumerate(node.children):
            is_last_child = i == child_count - 1
            print_tree(child, prefix + ('    ' if is_last else '│   '), is_last_child)


def main():
    current_directory = os.getcwd()  # Use current directory by default
    tree = build_tree(current_directory)

    # Count directories and files
    num_dirs, num_files = count_nodes(tree)

    print_tree(tree)
    print(f"{num_dirs} directories, {num_files} files")


def count_nodes(node):
    num_dirs = 0
    num_files = 0

    if node.is_file:
        num_files += 1
    else:
        num_dirs += 1
        for child in node.children:
            child_dirs, child_files = count_nodes(child)
            num_dirs += child_dirs
            num_files += child_files

    return num_dirs, num_files


if __name__ == "__main__":
    main()
