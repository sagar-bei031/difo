/**
 ******************************************************************************
 * @file    mySort.hpp
 * @brief   Declarations of functions for sorting files and directories based on specified criteria.
 *          Includes functions for case-insensitive string comparison and sorting files in a directory.
 *          Sorting can be done based on various criteria such as file name, size, or modification time.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

#include "myColors.hpp"
#include "myTypeDef.h"
#include <vector>
#include <functional>

/**
 * @brief Case-insensitive comparison of two strings.
 *
 * This function performs a case-insensitive comparison of two strings.
 *
 * @param a The first string.
 * @param b The second string.
 * @return true if strings are equal (case-insensitive), false otherwise.
 */
bool caseInsensitiveCompare(const std::string &a, const std::string &b);

/**
 * @brief Format size in human-readable format.
 *
 * This function formats the size in a human-readable format, converting bytes to KB, MB, or GB as needed.
 *
 * @param size The size in bytes.
 * @return The formatted size string.
 */
std::string format_size(double size);

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
void merge(std::vector<std::string> &arr, int l, int m, int r, std::function<bool(const std::string &, const std::string &)> comparator);

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
void mergeSort(std::vector<std::string> &arr, int l, int r, std::function<bool(const std::string &, const std::string &)> comparator);

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
std::vector<std::string> sort_files(const std::string &directory, const SortTypeDef &sort_type, const SortOrderDef &sort_order);

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
void sort(const SortTypeDef &sort_type, const SortOrderDef &order, const std::string &path, bool show_hidden);
