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
#include <unordered_map>
#include <unordered_set>

namespace fs = std::filesystem;
namespace core
{
    class Tree
    {
        public:
        static std::string write_tree(fs::path root_path);
        static void get_tree(std::unordered_map<std::string, std::string> &tree_data,const std::string& tree_hash,const std::string& tree_path);
        static std::string read_tree( const std::string& tree_hash);
        static void remove_tree(std::string path);
        static void find_dir(std::unordered_set<std::string> &dir_data,const std::string& tree_hash,const std::string& tree_path);
    };
}