/**
 ******************************************************************************
 * @file    myColors.hpp
 * @brief   Definitions of ANSI color escape codes and functions for colored text output.
 * @author  Arun, Sagar, Saurav
 * @date    March 7 2024
 ******************************************************************************
 */

#pragma once

#include <string>

/**
 * @brief ANSI color escape codes for text formatting.
 *
 * These escape codes are used to format text with colors.
 */
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

/**
 * @brief Color variables for file types.
 *
 * These variables define colors for different types of files and folders.
 */
const std::string COLOR_FOLDER              = COLOR_YELLOW;            /**< Color for regular folders */
const std::string COLOR_HIDDEN_FOLDER       = COLOR_FAINT_YELLOW;     /**< Color for hidden folders */
const std::string COLOR_FILE                = COLOR_BLUE;              /**< Color for regular files */
const std::string COLOR_HIDDEN_FILE         = COLOR_FAINT_BLUE;       /**< Color for hidden files */
const std::string COLOR_EXECUTABLE          = COLOR_RED;               /**< Color for executable files */
const std::string COLOR_HIDDEN_EXECUTABLE   = COLOR_FAINT_RED;        /**< Color for hidden executable files */

/**
 * @brief Color variables for bars and text
 */
const std::string COLOR_BAR  = COLOR_GREEN;
const std::string COLOR_TEXT = COLOR_CYAN;

/**
 * @brief Print colored text to the console.
 *
 * This function prints the given text in the specified color.
 *
 * @param text The text to be printed.
 * @param color The color to be used for printing.
 */
void print_colored_text(const std::string &text, const std::string &color);

/**
 * @brief Get the color for a file based on its name and visibility.
 *
 * This function determines the appropriate color for a file based on its name and visibility.
 *
 * @param filename The name of the file.
 * @param is_hidden A boolean indicating whether the file is hidden or not.
 * @return The color code for the file.
 */
std::string get_file_color(const std::string &filename, bool is_hidden);
