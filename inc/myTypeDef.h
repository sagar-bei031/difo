#pragma once

enum ViewTypeDef
{
    TREE,
    SIZE,
    SORT,
    SLIDE,
    HELP,
};

enum SortTypeDef
{
    SORT_NAME,
    SORT_SIZE,
    SORT_DATE
};

enum SortOrderDef
{
    ASC,
    DESC
};


enum ErrorTypeDef
{
    SUCCESS,
    ARG_FAILURE,
    ACCESS_FAILURE,
    FILE_OPEN_FAILURE,
    MEMORY_FAILURE
};