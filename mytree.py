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


def build_tree(directory, show_hidden=False, is_inner=False):
    root = TreeNode(directory, os.path.basename(directory), is_file=False)
    try:
        for item in sorted(os.listdir(directory)):
            full_path = os.path.join(directory, item)
            if os.path.isdir(full_path):
                if show_hidden or not item.startswith('.'):
                    root.add_child(build_tree(full_path, show_hidden, True))
            else:
                root.add_child(TreeNode(full_path, item, is_file=True))
    except PermissionError:
        print(f"Permission denied for accessing {directory}")
        exit()
    return root


def print_tree(node, prefix='', is_last=True, show_hidden=False):
    """Prints the tree structure."""
    color = get_file_color(node.full_path, node.name.startswith('.'))
    print_colored_text(f"{prefix}{'└── ' if is_last else '├── '}{os.path.basename(node.name)}", color)

    if not node.is_leaf():
        child_count = len(node.children)
        for i, child in enumerate(node.children):
            is_last_child = i == child_count - 1
            print_tree(child, prefix + ('    ' if is_last else '│   '), is_last_child, show_hidden)

def draw_tree(args, path):
    tree = build_tree(path, args.all)
    print_tree(tree, show_hidden=args.all)
