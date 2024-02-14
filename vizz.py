#!/usr/bin/env python3


from mycolors import *
from mytree import *
from mysize import *

import argparse


def main():
    parser = argparse.ArgumentParser(description="Display directory tree and sizes.")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    args = parser.parse_args()

    if args.tree:
        current_directory = os.getcwd()  # Use current directory by default
        tree = build_tree(current_directory, args.all)
        print_tree(tree, show_hidden=args.all)

    if args.size:
        current_directory = os.getcwd()  # Use current directory by default
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
