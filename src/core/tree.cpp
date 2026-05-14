
#include "../../include/core/object_store.hpp"
#include "../../include/core/repository.hpp"
#include "../../include/core/tree.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <vector>
#include <algorithm>
using namespace std;

namespace fs = std::filesystem;

    std::string core::Tree::write_tree(fs::path root_path)
    {
        std::vector<std::string> entries;
        std::error_code ec;
        for (auto &entry : fs::directory_iterator(root_path, fs::directory_options::skip_permission_denied, ec))
        {
            if (entry.path().filename() == ".dagit" || entry.path().filename() == ".git" || entry.is_symlink(ec))
            {
                continue;
            }
            else if (entry.is_regular_file(ec))
            {
                std::string content;
                std::ifstream in(entry.path(), std::ios::binary);
                std::ostringstream ss;
                ss << in.rdbuf();
                content = ss.str();
                std::string hash = core::ObjectStore::hash_object(content, "blob");
                entries.push_back("blob " + hash + " " + entry.path().filename().string());
            }

            else if (entry.is_directory(ec))
            {
                std::string hash = write_tree(entry.path());
                entries.push_back("tree " + hash + " " + entry.path().filename().string());
            }
        }
        std::sort(entries.begin(), entries.end());
        std::string tree_content;
        for (const auto &entry : entries)
        {
            tree_content += entry + "\n";
        }
        return core::ObjectStore::hash_object(tree_content, "tree");

    }


    void core::Tree::get_tree(std::unordered_map<std::string, std::string> &tree_data, const std::string& tree_hash,const std::string& tree_path)
    {
        std::string content=core::ObjectStore::get_object("",tree_hash);
        std::stringstream ss(content);
        std::string type;
        std::string hash;
        std::string name;
        while (ss >> type >> hash >> name)
        {
            if(type=="blob")
            {
                if(tree_path.empty())
                {
                    tree_data[name]=hash;
                }
                else
                {
                    tree_data[tree_path+"/"+name]=hash;
                }
            }
            else if(type=="tree" && name!=".dagit")
            {
                if(tree_path.empty())
                {
                    get_tree(tree_data,hash,name);
                }
                else    
                get_tree(tree_data,hash,tree_path+"/"+name);
            }
        }
    }

    std::string core::Tree::read_tree(const std::string& tree_hash)
    {
       remove_tree(fs::current_path().string());
       unordered_set<string> dir_data;
       find_dir(dir_data,tree_hash,"");
       vector<string> dirs;
       for(const auto& dir:dir_data)
       {
              dirs.push_back(dir);
       }
       int i;
       int j;
       std::string temp;
       for(i=0;i<dirs.size();i++)
       {
           for(j=0;j<dirs.size()-i-1;j++)
           {
               if(count(dirs[j].begin(),dirs[j].end(),'/')<count(dirs[j+1].begin(),dirs[j+1].end(),'/'))
               {
                   temp=dirs[j];
                   dirs[j]=dirs[j+1];
                   dirs[j+1]=temp;
               }
           }
       }
        fs::path restore_root=fs::current_path();
       std::string repo_root=core::Repository::find_repo_root(fs::current_path());
       for(const auto& dir:dirs)
       {
           fs::create_directories(restore_root/dir);
       }
       std::unordered_map<std::string,std::string> tree_data;
       get_tree(tree_data,tree_hash,"");
       
           
        for(const auto& [path,hash]:tree_data)
        {
            std::string content=core::ObjectStore::get_object("blob",tree_data[path]);
            fs::path full_path = restore_root / path;

          fs::create_directories(full_path.parent_path());

            std::ofstream out(full_path, std::ios::binary);
            out << content;
            out.close();
        }
      
         return "";
    }

    void core::Tree::remove_tree(std::string path)
{
    for (auto &entry : fs::directory_iterator(path))
    {
        if (entry.path().filename() == ".dagit")
        {
            continue;
        }

        if (entry.is_directory())
        {
            remove_tree(entry.path().string());

            fs::remove(entry.path());
        }
        else
        {
            fs::remove(entry.path());
        }
    }
}


void core::Tree::find_dir(std::unordered_set<std::string> &dir_data,const std::string& tree_hash,const std::string& tree_path)
{
    std::string content=core::ObjectStore::get_object("",tree_hash);
    std::stringstream ss(content);
    std::string type;
    std::string hash;
    std::string name;
    while (ss >> type >> hash >> name)
    {
        if(type=="tree" && name!=".dagit")
        {
            if(tree_path.empty())
            {
                dir_data.insert(name);
                find_dir(dir_data,hash,name);
            }
            else    
            {
                dir_data.insert(tree_path+"/"+name);
                find_dir(dir_data,hash,tree_path+"/"+name);
            }
        }
    }
}

   
    




    


    
