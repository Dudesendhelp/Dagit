#include "core/repository.hpp"
#include <filesystem>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

namespace core {
    bool Repository::init(const std::string &path)
    {
        if(fs::exists(path+"/.dagit"))
        {
            std::cout << "DAGit already initiated in this directory." << std::endl;
            return true;
        }
        else{
            try
                {fs::create_directory(path+"/.dagit");
                std::cout << "DAGit repository initialized successfully." << std::endl;
                return true;
                }
            catch(const fs::filesystem_error& e)
            {
                std::cout << "Error initializing DAGit repository: " << e.what() << std::endl;
                return false;
            }
        }
    }

    std::string Repository::find_repo_root( fs::path path )
    {
        while(true)
        {
             if(fs::exists(path/".dagit"))
             {
                return path;
             }
             else if(path.has_parent_path())
             {
                path = path.parent_path();
             }
             else
             {
                throw std::runtime_error("No DAGit repository found in the current directory or any parent directories.");
             }
        }
    }
}