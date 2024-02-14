import os

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

def print_colored_text(text, color):
    """Prints colored text."""
    print(f"{color}{text}{COLOR_RESET}")

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
        if is_hidden:
            return COLOR_FAINT_WHITE  # Hidden, not a file or directory
        else:
            return COLOR_FAINT_WHITE  # Not hidden, not a file or directory
