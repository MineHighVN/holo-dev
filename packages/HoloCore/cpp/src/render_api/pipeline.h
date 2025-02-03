#pragma once

#include <string>
#include <vector>

class Pipeline {
public:
    static std::vector<char> readFile(const std::string& filepath);
};
