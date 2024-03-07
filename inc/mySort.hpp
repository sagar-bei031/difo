#pragma once

#include "myColors.hpp"
#include "myTypeDef.h"
#include <vector>

bool caseInsensitiveCompare(const std::string &a, const std::string &b);

std::vector<std::string> sort_files(const std::string &directory, const SortTypeDef &sort_type, const SortOrderDef &sort_order);

void sort(const SortTypeDef &sort_type, const SortOrderDef &order, const std::string &path, bool show_hidden);