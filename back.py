import os
import argparse

def main():
    parser = argparse.ArgumentParser(description="Directory Information: display tree view, directory sizes, do sorting, and view file content.")
    parser.add_argument("directory", nargs="?", default=os.getcwd(), help="Directory path or file to display (default: current directory)")
    parser.add_argument("--tree", action="store_true", help="Display directory tree")
    parser.add_argument("--size", action="store_true", help="Display size of directories and files in current directory")
    parser.add_argument("--sort", nargs=2, metavar=('type', 'order'), help="Sort by type in order (asc or desc)")
    parser.add_argument("-a", "--all", action="store_true", help="Show hidden files and directories")
    parser.add_argument("--slide", type=float, default=1.0, help="Slide speed in seconds (default: 1.0)")
    args = parser.parse_args()

    path = os.path.abspath(args.directory)

    if not os.path.exists(path):
        print(f"vizz: cannot access '{path}': No such file or directory")
        return

    if args.tree:
        draw_tree(args=args, path=path)

    elif args.size:
        draw_size_bar(args=args, path=path)

    elif args.sort:
        sort(args=args, path=path)

    else:
        slide_file(args=args, path=path)

if __name__ == "__main__":
    main()
