#include <iostream>
#include <string>
#include <filesystem>
#include "myColors.hpp"
#include "myTree.hpp"
#include "mySize.hpp"
#include "myLinkedList.hpp"
#include "myQueue.hpp"
#include "myType.h"

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
        else if (arg == "--sort-size" || arg == "-d")
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
    }

    if (!std::filesystem::exists(directory))
    {
        std::cerr << "difo: cannot access '" << directory << "': No such file or directory" << std::endl;
        return 1;
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
            return 1;
        }
        print_content_with_slide(path, slide_speed);
        break;

    default:
        std::cout << "difo v1.0\n"
                     "Directory Information\n"
                     "Project: Data Structure and Algorithm\n"
                     "Second Year, Second Part\n\n"
                     "For help, use 'difo --help'"
                  << std::endl;
    }
    return 0;
}
