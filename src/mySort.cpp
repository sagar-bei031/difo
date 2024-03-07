#include "mySort.hpp"
#include "myColors.hpp"
#include "myTypeDef.h"
#include <string>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>

bool caseInsensitiveCompare(const std::string &a, const std::string &b)
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](char c1, char c2)
                                        { return std::tolower(c1) < std::tolower(c2); });
}

// Function to format size in human-readable format
std::string format_size(double size)
{
    const char *suffixes[] = {"bytes", "KB", "MB", "GB"};
    int suffix_index = 0;
    while (size >= 1024 && suffix_index < 3)
    {
        size /= 1024;
        suffix_index++;
    }
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << size << " " << suffixes[suffix_index];
    return ss.str();
}


// Function to sort files in a directory based on given criteria
std::vector<std::string> sort_files(const std::string &directory, const SortTypeDef &sort_type, const SortOrderDef &sort_order)
{
    std::vector<std::string> files;

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(directory.c_str())) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            std::string filename = entry->d_name;
            if (filename == "." || filename == "..")
                continue; // Skip current and parent directory entries
            files.push_back(filename);
        }
        closedir(dir);
    }

    auto comparator = [&](const std::string &a, const std::string &b)
    {
        std::string path_a = directory + "/" + a;
        std::string path_b = directory + "/" + b;
        struct stat stat_a, stat_b;
        stat(path_a.c_str(), &stat_a);
        stat(path_b.c_str(), &stat_b);

        if (sort_type == SORT_TIME)
        {
            return sort_order == ASC ? stat_a.st_mtime < stat_b.st_mtime : stat_a.st_mtime > stat_b.st_mtime;
        }
        else if (sort_type == SORT_SIZE)
        {
            return sort_order == ASC ? stat_a.st_size < stat_b.st_size : stat_a.st_size > stat_b.st_size;
        }
        else
        {
            return sort_order == ASC ? caseInsensitiveCompare(a, b) : caseInsensitiveCompare(b, a);
        }
    };

    std::sort(files.begin(), files.end(), comparator);

    if (sort_order == DESC)
        std::reverse(files.begin(), files.end()); // Reverse the sorted order if DESC

    return files;
}
void sort(const SortTypeDef &sort_type, const SortOrderDef &order, const std::string &path, bool show_hidden)
{
    // Sort the files based on the specified criteria
    std::vector<std::string> sorted_files = sort_files(path, sort_type, order);

    // Reverse the order if DESC is specified
    if (order == DESC)
        std::reverse(sorted_files.begin(), sorted_files.end());

    // Get maximum file name length
    size_t max_filename_length = 0;
    for (const std::string &file : sorted_files)
    {
        max_filename_length = std::max(max_filename_length, file.size());
    }

    // Iterate through the sorted files and print details for each file
    for (const std::string &file : sorted_files)
    {
        std::string color;
        if (file[0] == '.')
        {
            if (show_hidden)
            {
                color = get_file_color(path + "/" + file, false);
            }
            else
            {
                continue; // Skip hidden files if not showing hidden
            }
        }
        else
        {
            color = get_file_color(path + "/" + file, false);
        }

        // Print file name with color
        print_colored_text(file, color);
        std::cout << std::setw(max_filename_length + 4 - file.size()) << std::left << "";

        // Print file details based on sort type
        if (sort_type == SORT_TIME)
        {
            struct stat stat_buf;
            stat((path + "/" + file).c_str(), &stat_buf);

            // Convert timestamp to human-readable date format
            char time_str[20];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&stat_buf.st_mtime));

            // Print file details
            std::cout << time_str;
        }
        else if (sort_type == SORT_SIZE)
        {
            struct stat stat_buf;
            stat((path + "/" + file).c_str(), &stat_buf);
            double size = stat_buf.st_size;

            // Convert size to human-readable format
            std::string size_str = format_size(size);

            // Print file details
            std::cout << size_str;
        }
        std::cout << std::endl;
    }
}
