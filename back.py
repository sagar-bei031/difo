#!/usr/bin/env python3

import os
import argparse
import shutil
from datetime import datetime

# ANSI color escape codes
COLOR_RED = "\033[91m"
COLOR_GREEN = "\033[92m"
COLOR_YELLOW = "\033[93m"
COLOR_BLUE = "\033[94m"
COLOR_MAGENTA = "\033[95m"
COLOR_CYAN = "\033[96m"
COLOR_WHITE = "\033[97m"
COLOR_BRIGHT_BLACK = "\033[90m"
COLOR_FAINT_RED = "\033[2;91m"
COLOR_FAINT_GREEN = "\033[2;92m"
COLOR_FAINT_YELLOW = "\033[2;93m"
COLOR_FAINT_BLUE = "\033[2;94m"
COLOR_FAINT_MAGENTA = "\033[2;95m"
COLOR_FAINT_CYAN = "\033[2;96m"
COLOR_FAINT_WHITE = "\033[2;97m"
COLOR_RESET = "\033[0m"

# Define color variables for file types
COLOR_FOLDER = COLOR_YELLOW
COLOR_HIDDEN_FOLDER = COLOR_FAINT_YELLOW
COLOR_FILE = COLOR_GREEN
COLOR_HIDDEN_FILE = COLOR_FAINT_GREEN
COLOR_EXECUTABLE = COLOR_RED
COLOR_HIDDEN_EXECUTABLE = COLOR_FAINT_RED

# Define color variables for bars and text
COLOR_BAR = COLOR_RED
COLOR_TEXT = COLOR_RESET

class TreeNode:
    def __init__(self, full_path, name, is_file=False):
        self.full_path = full_path
        self.name = name
        self.is_file = is_file
        self.children = []

    def add_child(self, node):
        self.children.append(node)

    def is_leaf(self):
        return len(self.children) == 0

def build_tree(directory, show_hidden=False):
    root = TreeNode(directory, os.path.basename(directory), is_file=False)
    if os.path.isdir(directory):
        for item in sorted(os.listdir(directory)):
            full_path = os.path.join(directory, item)
            if os.path.isdir(full_path):
                if show_hidden or not item.startswith('.'):
                    root.add_child(build_tree(full_path, show_hidden))
            else:
                root.add_child(TreeNode(full_path, item, is_file=True))
    return root

def get_file_color(filename, is_hidden):
    """Returns the appropriate color for a file based on its type and visibility."""
    if os.path.isdir(filename):
        if is_hidden:
            return COLOR_HIDDEN_FOLDER
        else:
            return COLOR_FOLDER
    elif os.access(filename, os.X_OK):
        if is_hidden:
            return COLOR_HIDDEN_EXECUTABLE
        else:
            return COLOR_EXECUTABLE
    elif os.path.isfile(filename):
        if is_hidden:
            return COLOR_HIDDEN_FILE
        else:
            return COLOR_FILE
    else:
        return COLOR_FAINT_WHITE  # Not a file or directory

def print_colored_text(text, color):
    """Prints colored text."""
    print(f"{color}{text}{COLOR_RESET}")

def print_tree(node, prefix='', is_last=True, show_hidden=False):
    """Prints the tree structure."""
    color = get_file_color(node.full_path, node.name.startswith('.') and not show_hidden)
    print_colored_text(f"{prefix}{'└── ' if is_last else '├── '}{os.path.basename(node.name)}", color)

    if not node.is_leaf():
        child_count = len(node.children)
        for i, child in enumerate(node.children):
            is_last_child = i == child_count - 1
            print_tree(child, prefix + ('    ' if is_last else '│   '), is_last_child, show_hidden)

def print_size(directory, show_hidden=False):
    """Prints the size of directories and files in the current directory."""
    print("Size of directories and files in current directory:")
    terminal_width = shutil.get_terminal_size().columns
    max_name_length = max(len(item) for item in os.listdir(directory))
    for item in sorted(os.listdir(directory)):
        full_path = os.path.join(directory, item)
        if show_hidden or not item.startswith('.'):
            size = os.path.getsize(full_path)
            max_bar_length = terminal_width - max_name_length - len(f"{size} bytes") - 5  # Adjusted for spacing and units
            bar_length = int(size / max_size * max_bar_length)
            size_str = f"{size} bytes" if size < 1024 else f"{size / 1024:.2f} KB"
            color = get_file_color(full_path, item.startswith('.') and not show_hidden)
            color_bar = COLOR_BAR
            print_colored_text(f"{item.ljust(max_name_length)} {COLOR_TEXT}{color_bar}{'=' * bar_length} {size_str}", color)

def sort_files(directory, sort_type, order):
    files = [f for f in os.listdir(directory) if not f.startswith('.')]
    if sort_type == "name":
        files.sort(reverse=(order == "desc"))
    elif sort_type == "date":
        files.sort(key=lambda x: os.path.getmtime(os.path.join(directory, x)), reverse=(order == "desc"))
    elif sort_type == "size":
        files.sort(key=lambda x: os.path.getsize(os.path.join(directory, x)), reverse=(order == "desc"))
    return files

def main():
    parser = argparse.ArgumentParser(description="Display directory tree and sizes.")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("--sort", nargs=2, metavar=("type", "order"), help="Sort files and folders")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    args = parser.parse_args()

    current_directory = os.getcwd()

    if args.sort:
        sort_type, order = args.sort
        if sort_type not in ["name", "date", "size"]:
            print("Invalid sort type. Choose from 'name', 'date', or 'size'.")
            return
        if order not in ["asc", "desc"]:
            print("Invalid sort order. Choose 'asc' or 'desc'.")
            return
        sorted_files = sort_files(current_directory, sort_type, order)
        for file in sorted_files:
            print(file)
    elif args.tree:
        tree = build_tree(current_directory, args.all)
        print_tree(tree, show_hidden=args.all)
    elif args.size:
        global max_size
        max_size = 0
        for item in os.listdir(current_directory):
            full_path = os.path.join(current_directory, item)
            if args.all or not item.startswith('.'):
                size = os.path.getsize(full_path)
                if size > max_size:
                    max_size = size
        print_size(current_directory, show_hidden=args.all)

if __name__ == "__main__":
    main()
