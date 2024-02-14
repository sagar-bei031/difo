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
        draw_tree(args=args)

    if args.size:
        draw_size_bar(args=args)

if __name__ == "__main__":
    main()
