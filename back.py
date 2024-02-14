#!/usr/bin/env python3

import os
import argparse
import shutil

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


class ListNode:
    def __init__(self, data):
        self.data = data
        self.next = None

def merge_sort_linked_list(head, key):
    if not head or not head.next:
        return head

    mid = get_middle(head)
    next_to_mid = mid.next
    mid.next = None

    left = merge_sort_linked_list(head, key)
    right = merge_sort_linked_list(next_to_mid, key)

    return merge(left, right, key)

def get_middle(head):
    if not head:
        return head

    slow = head
    fast = head

    while fast.next and fast.next.next:
        slow = slow.next
        fast = fast.next.next

    return slow

def merge(left, right, key):
    result = None

    if not left:
        return right
    if not right:
        return left

    if key(left.data) <= key(right.data):
        result = left
        result.next = merge(left.next, right, key)
    else:
        result = right
        result.next = merge(left, right.next, key)

    return result

def convert_to_linked_list(node):
    if not node:
        return None

    head = ListNode(node)
    temp = head

    for child in node.children:
        temp.next = convert_to_linked_list(child)
        temp = temp.next

    return head

def get_key(sort_type):
    if sort_type == 'name':
        return lambda x: x.name.lower()
    elif sort_type == 'date':
        return lambda x: os.path.getmtime(x.full_path)
    elif sort_type == 'size':
        return lambda x: os.path.getsize(x.full_path)

def build_tree(directory, show_hidden=False, is_inner=False):
    root = TreeNode(directory, os.path.basename(directory), is_file=False)
    if os.path.isdir(directory):
        for item in os.listdir(directory):
            full_path = os.path.join(directory, item)
            if os.path.isdir(full_path):
                if show_hidden or not item.startswith('.'):
                    root.add_child(build_tree(full_path, show_hidden, True))
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

def print_sorted_tree(tree_linked_list, show_hidden=False):
    """Prints the sorted tree structure."""
    current = tree_linked_list
    while current:
        color = get_file_color(current.data.full_path, os.path.basename(current.data.name).startswith('.') and not show_hidden)
        print_colored_text(os.path.basename(current.data.name), color)
        current = current.next

def print_size(directory, show_hidden=False):
    """Prints the size of directories and files in the current directory."""
    print("Size of directories and files in current directory:")
    terminal_width = shutil.get_terminal_size().columns
    max_name_length = max(len(item) for item in os.listdir(directory))
    for item in os.listdir(directory):
        full_path = os.path.join(directory, item)
        if show_hidden or not item.startswith('.'):
            size = os.path.getsize(full_path)
            max_bar_length = terminal_width - max_name_length - len(f"{size} bytes") - 5  # Adjusted for spacing and units
            bar_length = int(size / max_size * max_bar_length)
            size_str = f"{size} bytes" if size < 1024 else f"{size / 1024:.2f} KB"
            color = get_file_color(full_path, item.startswith('.') and not show_hidden)
            color_bar = COLOR_BAR
            print_colored_text(f"{item.ljust(max_name_length)} {COLOR_TEXT}{color_bar}{'=' * bar_length} {size_str}", color)

def main():
    parser = argparse.ArgumentParser(description="Display directory tree and sizes.")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    parser.add_argument("--sort", nargs=2, metavar=('sort_type', 'order'), help="Sort files and folders")
    args = parser.parse_args()

    if args.tree:
        current_directory = os.getcwd()  # Use current directory by default
        tree = build_tree(current_directory, args.all)
        
        if args.sort:
            sort_type, order = args.sort
            key = get_key(sort_type)
            tree_linked_list = convert_to_linked_list(tree)
            tree_sorted = merge_sort_linked_list(tree_linked_list, key)
            print_sorted_tree(tree_sorted, show_hidden=args.all)
        else:
            print_tree(tree, show_hidden=args.all)

    if args.size:
        current_directory = os.getcwd()  # Use current directory by default
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
