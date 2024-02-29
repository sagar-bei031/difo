#pragma once

#include <string>

// ANSI color escape codes
const std::string COLOR_RED             = "\033[91m";
const std::string COLOR_GREEN           = "\033[92m";
const std::string COLOR_YELLOW          = "\033[93m";
const std::string COLOR_BLUE            = "\033[94m";
const std::string COLOR_MAGENTA         = "\033[95m";
const std::string COLOR_CYAN            = "\033[96m";
const std::string COLOR_WHITE           = "\033[97m";
const std::string COLOR_BRIGHT_BLACK    = "\033[90m";
const std::string COLOR_FAINT_RED       = "\033[2;91m";
const std::string COLOR_FAINT_GREEN     = "\033[2;92m";
const std::string COLOR_FAINT_YELLOW    = "\033[2;93m";
const std::string COLOR_FAINT_BLUE      = "\033[2;94m";
const std::string COLOR_FAINT_MAGENTA   = "\033[2;95m";
const std::string COLOR_FAINT_CYAN      = "\033[2;96m";
const std::string COLOR_FAINT_WHITE     = "\033[2;97m";
const std::string COLOR_RESET           = "\033[0m";

// Define color variables for file types
const std::string COLOR_FOLDER              = COLOR_YELLOW;
const std::string COLOR_HIDDEN_FOLDER       = COLOR_FAINT_YELLOW;
const std::string COLOR_FILE                = COLOR_BLUE;
const std::string COLOR_HIDDEN_FILE         = COLOR_FAINT_BLUE;
const std::string COLOR_EXECUTABLE          = COLOR_RED;
const std::string COLOR_HIDDEN_EXECUTABLE   = COLOR_FAINT_RED;

// Define color variables for bars and text
const std::string COLOR_BAR  = COLOR_GREEN;
const std::string COLOR_TEXT = COLOR_CYAN;

void print_colored_text(const std::string &text, const std::string &color);

std::string get_file_color(const std::string &filename, bool is_hidden);