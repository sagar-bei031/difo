from myColors import *
import shutil

def print_size(directory, max_size, show_hidden=False):
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
            color = get_file_color(full_path, item.startswith('.'))
            color_bar = COLOR_BAR
            print_colored_text(f"{item.ljust(max_name_length)} {COLOR_BAR}{color_bar}{'=' * bar_length} {COLOR_TEXT}{size_str}", color)

def draw_size_bar(args, path):
    max_size = 0
    for item in os.listdir(path):
        full_path = os.path.join(path, item)
        if args.all or not item.startswith('.'):
            size = os.path.getsize(full_path)
            if size > max_size:
                max_size = size
    print_size(path, max_size, show_hidden=args.all)