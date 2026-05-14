#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
namespace core
{
    class Commit
    {
       public:
       static std::string create_commit();
       static std::string get_commit(const std::string& commit_hash);
       static std::string iter_commits_and_parents();
    };
}