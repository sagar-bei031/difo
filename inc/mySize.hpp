#pragma once

#include <string>

void print_size(const std::string &directory, long long max_size, bool show_hidden);

void draw_size_bar(bool show_hidden, const std::string &path);