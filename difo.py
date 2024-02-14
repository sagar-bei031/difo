#!/usr/bin/env python3

from mycolors import *
from mytree import *
from mysize import *
from myLinkedList import *
from myQueue import *
import argparse  

def main():
    parser = argparse.ArgumentParser(description="Directory Information: display tree view, directory sizes and do sorting.")
    parser.add_argument("directory", nargs="?", default=os.getcwd(), help="Directory path (default: current directory)")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("--sort", nargs=2, metavar=('type', 'order'), help="Sort by type in order (asc or desc)")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    parser.add_argument("--slide", type=float, default=1.0, help="Slide speed in seconds (default: 1.0)")
    args = parser.parse_args()

    if not os.path.exists(args.directory):
        print(f"vizz: cannot access '{args.directory}': No such file or directory")
        return
    
    path = os.path.abspath(args.directory)

    if args.tree:
        print_tree(args=args, path=path)

    elif args.size:
        draw_size_bar(args=args, path=path)

    elif args.sort:
        sort(args=args, path=path)

    elif args.slide:
        if not os.path.isfile(path):
            print(f"difo: cannot open: '{args.directory}' is not a file")
            exit()
        print_content_with_slide(file_path=path, slide_speed=args.slide)

    else:
        print("difo v1.0\n \
              Directory Information\n \
              Project: Data Structure and Algorithm\n \
              Second Year, Second Part\n \
              \n \
              For help, use 'difo --help'")

if __name__ == "__main__":
    main()
