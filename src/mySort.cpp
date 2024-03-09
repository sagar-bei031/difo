/**
 ******************************************************************************
 * @file    mySort.cpp
 * @brief   Implementation of functions for sorting files and directories based on specified criteria.
 *          Includes functions for case-insensitive string comparison and sorting files in a directory.
 *          Sorting can be done based on various criteria such as file name, size, or modification time.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

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

/**
 * @brief Case-insensitive comparison of two strings.
 *
 * This function performs a case-insensitive comparison of two strings.
 *
 * @param a The first string.
 * @param b The second string.
 * @return true if strings are equal (case-insensitive), false otherwise.
 */
bool caseInsensitiveCompare(const std::string &a, const std::string &b)
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](char c1, char c2)
                                        { return std::tolower(c1) < std::tolower(c2); });
}

/**
 * @brief Format size in human-readable format.
 *
 * This function formats the size in a human-readable format, converting bytes to KB, MB, or GB as needed.
 *
 * @param size The size in bytes.
 * @return The formatted size string.
 */
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

/**
 * @brief Merge two sorted subarrays into one sorted array.
 *
 * This function merges two sorted subarrays into one sorted array.
 *
 * @param arr The array to be merged.
 * @param l The left index of the subarray.
 * @param m The middle index of the subarray.
 * @param r The right index of the subarray.
 * @param comparator The function used for comparison.
 */
void merge(std::vector<std::string> &arr, int l, int m, int r, std::function<bool(const std::string &, const std::string &)> comparator)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<std::string> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (comparator(L[i], R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Implementation of merge sort algorithm.
 *
 * This function recursively sorts the array using the merge sort algorithm.
 *
 * @param arr The array to be sorted.
 * @param l The left index of the array.
 * @param r The right index of the array.
 * @param comparator The function used for comparison.
 */
void mergeSort(std::vector<std::string> &arr, int l, int r, std::function<bool(const std::string &, const std::string &)> comparator)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparator);
        mergeSort(arr, m + 1, r, comparator);
        merge(arr, l, m, r, comparator);
    }
}

/**
 * @brief Sort files in a directory based on specified criteria.
 *
 * This function sorts the files in the specified directory based on the provided sort type
 * (e.g., name, size, modification time) and sort order (ascending or descending).
 *
 * @param directory The path to the directory containing the files to be sorted.
 * @param sort_type The type of sorting criteria (e.g., name, size, modification time).
 * @param sort_order The order in which files should be sorted (ascending or descending).
 * @return A vector of sorted file names.
 */
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

    mergeSort(files, 0, files.size() - 1, comparator); // Use custom merge sort here

    if (sort_order == DESC)
        std::reverse(files.begin(), files.end()); // Reverse the sorted order if DESC

    return files;
}

/**
 * @brief Sort files in a directory based on specified criteria and display them.
 *
 * This function sorts the files in the specified directory based on the provided sort type
 * (e.g., name, size, modification time) and sort order (ascending or descending), and then
 * displays the sorted files with optional inclusion of hidden files.
 *
 * @param sort_type The type of sorting criteria (e.g., name, size, modification time).
 * @param order The order in which files should be sorted (ascending or descending).
 * @param path The path to the directory containing the files to be sorted.
 * @param show_hidden Whether to include hidden files in the sorting.
 */
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
