#pragma once
#include "repository.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
namespace fs = std::filesystem;

namespace core
{
    class ObjectStore
    {
        public:
        std::string static hash_object(std::string content,std::string type);
        std::string static generate_hash(std::string content);
        std::string static get_object(std::string type,std::string hash);
        bool static object_exists(std::string hash);
    };
}