#pragma once

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

// ANSI color escape codes
const string COLOR_RED = "\033[91m";
const string COLOR_GREEN = "\033[92m";
const string COLOR_YELLOW = "\033[93m";
const string COLOR_BLUE = "\033[94m";
const string COLOR_MAGENTA = "\033[95m";
const string COLOR_CYAN = "\033[96m";
const string COLOR_WHITE = "\033[97m";
const string COLOR_BRIGHT_BLACK = "\033[90m";
const string COLOR_FAINT_RED = "\033[2;91m";
const string COLOR_FAINT_GREEN = "\033[2;92m";
const string COLOR_FAINT_YELLOW = "\033[2;93m";
const string COLOR_FAINT_BLUE = "\033[2;94m";
const string COLOR_FAINT_MAGENTA = "\033[2;95m";
const string COLOR_FAINT_CYAN = "\033[2;96m";
const string COLOR_FAINT_WHITE = "\033[2;97m";
const string COLOR_RESET = "\033[0m";

// Define color variables for file types
const string COLOR_FOLDER = COLOR_YELLOW;
const string COLOR_HIDDEN_FOLDER = COLOR_FAINT_YELLOW;
const string COLOR_FILE = COLOR_BLUE;
const string COLOR_HIDDEN_FILE = COLOR_FAINT_BLUE;
const string COLOR_EXECUTABLE = COLOR_RED;
const string COLOR_HIDDEN_EXECUTABLE = COLOR_FAINT_RED;

// Define color variables for bars and text
const string COLOR_BAR = COLOR_GREEN;
const string COLOR_TEXT = COLOR_CYAN;

void print_colored_text(const string &text, const string &color)
{
    cout << color << text << COLOR_RESET << endl;
}

string get_file_color(const string &filename, bool is_hidden)
{
    struct stat file_stat;
    if (stat(filename.c_str(), &file_stat) != 0)
    {
        // Error occurred while retrieving file information
        return COLOR_FAINT_WHITE;
    }

    if (S_ISDIR(file_stat.st_mode))
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_FOLDER;
        }
        else
        {
            return COLOR_FOLDER;
        }
    }
    else if (access(filename.c_str(), X_OK) == 0)
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_EXECUTABLE;
        }
        else
        {
            return COLOR_EXECUTABLE;
        }
    }
    else if (S_ISREG(file_stat.st_mode))
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_FILE;
        }
        else
        {
            return COLOR_FILE;
        }
    }
    else
    {
        if (is_hidden)
        {
            return COLOR_FAINT_WHITE; // Hidden, not a file or directory
        }
        else
        {
            return COLOR_FAINT_WHITE; // Not hidden, not a file or directory
        }
    }
}
