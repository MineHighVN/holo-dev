#include "split.h"

namespace utils {
    std::vector<std::string> split (std::string str, char dlt) {
        std::vector<std::string> res;

        res.reserve(str.length() / 2);

        const char* ptr = str.data();
        size_t size = 0;

        for (const char c : str) {
            if (c == dlt) {
                res.emplace_back(ptr, size);
                ptr += size + 1;
                size = 0;
                continue;
            }

            ++size;
        }

        if (size > 0)
            res.emplace_back(ptr, size);

        return res;
    }
}
