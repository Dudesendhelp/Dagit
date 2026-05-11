
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

namespace fs = std::filesystem;

    std::string core::Tree::write_tree(fs::path root_path)
    {
        std::vector<std::string> entries;
        for (auto &entry : fs::directory_iterator(root_path))
        {
            if (entry.path().filename() == ".dagit")
            {
                continue;
            }
            else if (entry.is_regular_file())
            {
                std::string content;
                std::ifstream in(entry.path(), std::ios::binary);
                std::ostringstream ss;
                ss << in.rdbuf();
                content = ss.str();
                std::string hash = core::ObjectStore::hash_object(content, "blob");
                entries.push_back("blob " + hash + " " + entry.path().filename().string());
            }

            else if (entry.is_directory())
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
