#!/usr/bin/env python3


from mycolors import *
from mytree import *
from mysize import *
from myLinkedList import *
import argparse  

def main():
    parser = argparse.ArgumentParser(description="Display directory tree and sizes.")
    parser.add_argument("directory", nargs="?", default=os.getcwd(), help="Directory path (default: current directory)")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("--sort", nargs=2, metavar=('type', 'order'), help="Sort by type in order (asc or desc)")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    args = parser.parse_args()

    if not os.path.exists(args.directory):
        print(f"vizz: cannot access '{args.directory}': No such file or directory")
        return
    
    path = os.path.abspath(args.directory)

    if args.tree:
        draw_tree(args=args, path=path)

    elif args.size:
        draw_size_bar(args=args, path=path)

    elif args.sort:
        sort(args=args, path=path)

if __name__ == "__main__":
    main()
