#pragma once

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
namespace fs = std::filesystem;;
namespace core
{
    class Repository
    {
        public:
        bool static init(const std::string &path=".");
        std::string static find_repo_root( fs::path path = fs::current_path() );
    };
}