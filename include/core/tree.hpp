#pragma once
#include "repository.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

namespace fs = std::filesystem;
namespace core
{
    class Tree
    {
        public:
        static std::string write_tree(fs::path root_path);
    };
}