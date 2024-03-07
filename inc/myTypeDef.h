/**
 ******************************************************************************
 * @file    myTypeDef.h
 * @brief   Defines enums for different view types, sort types, sort orders, and error types.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

/**
 * @brief Enumerates different view types.
 */
enum ViewTypeDef
{
    TREE, /**< Tree view */
    SIZE, /**< Size view */
    SORT, /**< Sort view */
    SLIDE, /**< Slide view */
    HELP /**< Help view */
};

/**
 * @brief Enumerates different sort types.
 */
enum SortTypeDef
{
    SORT_NAME, /**< Sort by name */
    SORT_SIZE, /**< Sort by size */
    SORT_TIME /**< Sort by time */
};

/**
 * @brief Enumerates different sort orders.
 */
enum SortOrderDef
{
    ASC, /**< Ascending order */
    DESC /**< Descending order */
};

/**
 * @brief Enumerates different error types.
 */
enum ErrorTypeDef
{
    SUCCESS, /**< Success */
    ARG_FAILURE, /**< Argument failure */
    OPEN_FAILURE /**< Opening failure */
};
