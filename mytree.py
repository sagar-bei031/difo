from mycolors import *

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


def build_tree(directory, show_hidden=False, is_inner=False, prefix=''):
    try:
        items = sorted(os.listdir(directory))
        for index, item in enumerate(items):
            full_path = os.path.join(directory, item)
            is_last = index == len(items) - 1
            if not show_hidden and item.startswith('.'):
                continue
            if os.path.isdir(full_path):
                print_colored_text(f"{prefix}{'└── ' if is_last else '├── '}{os.path.basename(item)}", COLOR_CYAN)
                build_tree(full_path, show_hidden, True, prefix + ('    ' if is_last else '│   '))
            else:
                color = get_file_color(full_path, item.startswith('.'))
                print_colored_text(f"{prefix}{'└── ' if is_last else '├── '}{os.path.basename(item)}", color)
    except PermissionError:
        print(f"Permission denied for accessing {directory}")
        exit()



def print_tree(args, path):
    build_tree(path, args.all)

