#!/usr/bin/env python3

import os
import argparse
import shutil

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


def print_size(directory):
    print("Size of directories and files in current directory:")
    terminal_width = shutil.get_terminal_size().columns
    max_name_length = max(len(item) for item in os.listdir(directory))
    for item in os.listdir(directory):
        full_path = os.path.join(directory, item)
        size = os.path.getsize(full_path)
        max_bar_length = terminal_width - max_name_length - len(f"{size} bytes") - 5  # Adjusted for spacing and units
        bar_length = int(size / max_size * max_bar_length)
        size_str = f"{size} bytes" if size < 1024 else f"{size / 1024:.2f} KB"
        print(f"{item.ljust(max_name_length)} {'=' * bar_length} {size_str}")



def main():
    parser = argparse.ArgumentParser(description="Display directory tree and sizes.")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    args = parser.parse_args()

    if args.tree:
        current_directory = os.getcwd()  # Use current directory by default
        tree = build_tree(current_directory)
        print_tree(tree)

    if args.size:
        current_directory = os.getcwd()  # Use current directory by default
        global max_size
        max_size = 0
        for item in os.listdir(current_directory):
            full_path = os.path.join(current_directory, item)
            size = os.path.getsize(full_path)
            if size > max_size:
                max_size = size
        print_size(current_directory)


if __name__ == "__main__":
    main()
