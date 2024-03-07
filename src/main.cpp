#include <iostream>
#include <string>
#include <filesystem>
#include "myColors.hpp"
#include "myTree.hpp"
#include "mySize.hpp"
#include "myLinkedList.hpp"
#include "myQueue.hpp"
#include "myTypeDef.h"

std::string help_msg =
"Directory Information: display tree view, directory sizes and do sorting.\n\n"
"usage: difo.py [-h] [--tree] [--size] [--sort <type> <order>] [-a] [--slide <speed>] [directory]\n\n"
"positional arguments:\n"
"  directory                 Directory path (default: current directory)\n\n"
"options:\n"
"  -h, --help                Show this help message and exit\n"
"  --tree                    Display directory tree\n"
"  --size                    Display size of directories and files in current directory\n"
"  --sort [sorting options]  Sort by type in order (-asc or -desc)\n"
"  -a, --all                 Show hidden files and directories\n"
"  --slide, -l [speed]       Slide speed in seconds (default: 1.0 impled 1 character per 20ms)\n\n"
"sorting options:\n"
"  --sort-name, -n           Sort by name\n"
"  --sort-date, -d           Sort by date\n"
"  --sort-size, -s           Sort by size\n"
"  --ascending, -asc         Sort in ascending order\n"
"  --descending, -desc       Sort in descending order\n\n"
"slide speed:\n"
"  -f[speed]                 Adjust speed: 1.0 = one character per 20ms\n\n"
"return:\n"
"  0                         success\n"
"  1                         invalid argument\n"
"  2                         failure on accessing (file or directory)\n"
"  3                         failure on opening file\n"
"  4                         memory failure (segmentation fault)\n\n";



int main(int argc, char *argv[])
{
    // Default values
    ViewTypeDef view = TREE;
    SortTypeDef sort_type = SORT_NAME;
    SortOrderDef sort_order = ASC;
    bool show_hidden = false;
    float slide_speed = 1.0f;
    std::string directory = ".";

       // Parse arguments
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
        else if (arg == "--sort-date" || arg == "-d")
        {
            view = SORT;
            sort_type = SORT_DATE;
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
            return ARG_FAILURE;
        }
    }

    if (!std::filesystem::exists(directory))
    {
        std::cerr << "difo: cannot access '" << directory << "': No such file or directory" << std::endl;
        return ACCESS_FAILURE;
    }

    std::string path = std::filesystem::absolute(directory).string();

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
            return FILE_OPEN_FAILURE;
        }
        print_content_with_slide(path, slide_speed);
        break;

    case HELP:
        std::cout << help_msg << std::flush;
        break;

    default:
        std::cout << "difo v1.0\n"
                     "Directory Information\n"
                     "Project: Data Structure and Algorithm\n"
                     "Second Year, Second Part\n\n"
                     "For help, use 'difo --help'"
                  << std::endl;
    }
    return SUCCESS;
}
