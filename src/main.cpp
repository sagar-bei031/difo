/**
 ******************************************************************************
 * @file    main.cpp
 * @brief   Entry point for the Directory Information program.
 *          Parses command-line arguments and initiates the corresponding actions.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "myTypeDef.h"
#include "myTree.hpp"
#include "mySize.hpp"
#include "mySort.hpp"
#include "mySlide.hpp"
#include "myColors.hpp"
#include <iostream>
#include <string>
#include <filesystem>

/**
 * @brief   Help message providing usage instructions and options for the program.
 */
std::string help_msg =
    "Directory Information: display tree view, directory sizes and do sorting.\n\n"
    "usage: difo.py [-h] [--tree] [--size] [--sort <type> <order>] [-a] [--slide <speed>] [directory]\n\n"
    "positional arguments:\n"
    "  directory                 Directory path (default: current directory)\n\n"
    "options:\n"
    "  --tree, -t                Display directory tree\n"
    "  --size, -z                Display size of directories and files in current directory\n"
    "  --sort [sorting options]  Sort by type in order (-asc or -desc)\n"
    "  --slide, -l [speed]       Slide speed in seconds (default: 1.0 impled 1 character per 20ms)\n"
    "  -a, --all                 Show hidden files and directories\n"
    "  -h, --help                Show this help message and exit\n\n"
    "sorting options:\n"
    "  --sort-name, -n           Sort by name\n"
    "  --sort-time, -d           Sort by time\n"
    "  --sort-size, -s           Sort by size\n"
    "  --ascending, -asc         Sort in ascending order\n"
    "  --descending, -desc       Sort in descending order\n\n"
    "slide speed:\n"
    "  -f[speed]                 Adjust speed: 1.0 = one character per 20ms\n\n"
    "return:\n"
    "  0                         success\n"
    "  1                         invalid argument\n"
    "  2                         failure on opening (file or directory)\n\n";

/**
 * @brief   Main function where program execution begins.
 *          Parses command-line arguments and initiates the corresponding actions.
 * @param   argc Number of command-line arguments.
 * @param   argv Array of command-line arguments.
 * @return  An integer representing the exit status of the program.
 *          0 for success, 1 for invalid argument, 2 for failure on opening.
 */
int main(int argc, char *argv[])
{
    // Default values and variables for parsing command-line arguments
    ViewTypeDef view = TREE;
    SortTypeDef sort_type = SORT_NAME;
    SortOrderDef sort_order = ASC;
    bool show_hidden = false;
    float slide_speed = 1.0f;
    std::string directory = ".";

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--tree" || arg == "-t")
        {
            view = TREE;
        }
        else if (arg == "--size" || arg == "-z")
        {
            view = SIZE;
        }
        else if (arg == "--sort" || arg == "-s")
        {
            view = SORT;
        }
        else if (arg == "--sort-name" || arg == "-n")
        {
            view = SORT;
            sort_type = SORT_NAME;
        }
        else if (arg == "--sort-time" || arg == "-d")
        {
            view = SORT;
            sort_type = SORT_TIME;
        }
        else if (arg == "--sort-size" || arg == "-s") // Change from -d to -s
        {
            view = SORT;
            sort_type = SORT_SIZE;
        }
        else if (arg == "--ascending" || arg == "-asc")
        {
            sort_order = ASC;
        }
        else if (arg == "--descending" || arg == "-desc")
        {
            sort_order = DESC;
        }
        else if (arg == "--slide" || arg == "-l")
        {
            view = SLIDE;
        }
        else if (arg.substr(0, 2) == "-f")
        {
            slide_speed = std::stof(arg.substr(2));
        }
        else if (arg == "--help" || arg == "-h")
        {
            view = HELP;
        }
        else if (arg[0] != '-')
        {
            directory = arg;
        }
        else
        {
            std::cerr << "difo: invalid argument '" << arg << "'" << std::endl;
            std::cout << "see 'difo --help'" << std::endl;
            return ARG_FAILURE;
        }
    }

    // Check if the specified directory exists
    if (!std::filesystem::exists(directory))
    {
        std::cerr << "difo: cannot access '" << directory << "': No such file or directory" << std::endl;
        return OPEN_FAILURE;
    }

    // Get the absolute path of the directory
    std::string path = std::filesystem::absolute(directory).string();

    // Perform the action based on the specified view
    switch (view)
    {
    case TREE:
        print_tree(path, show_hidden);
        break;

    case SIZE:
        draw_size_bar(show_hidden, path);
        break;

    case SORT:
        sort(sort_type, sort_order, path, show_hidden);
        break;

    case SLIDE:
        if (!std::filesystem::is_regular_file(path))
        {
            std::cerr << "difo: cannot open: '" << directory << "' is not a file" << std::endl;
            return OPEN_FAILURE;
        }
        print_content_with_slide(path, slide_speed);
        break;

    case HELP:
        std::cout << help_msg << std::flush;
        break;
    }

    return SUCCESS;
}
