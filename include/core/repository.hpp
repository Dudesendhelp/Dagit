#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace core
{
    class Repository
    {
        public:
        bool static init(const std::string &path=".");
    };
}