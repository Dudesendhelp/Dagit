#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;
namespace core
{
    class Commit
    {
       public:
       static std::string create_commit(std::string message);
       static std::unordered_map<std::string, std::string> get_commit(const std::string& commit_hash);
       static std::string iter_commits_and_parents();
    };
}