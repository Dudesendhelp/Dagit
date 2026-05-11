
#include "../../include/core/repository.hpp"
#include "../../include/core/object_store.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

namespace fs = std::filesystem;


        // ############################################################################################
        std::string core::ObjectStore::hash_object(std::string content, std::string type)
        {
            fs::path repo_root = fs::path(core::Repository::find_repo_root()) / ".dagit/objects";
            std::string hash = generate_hash(type + '\0' + content);
            if(object_exists(hash))
            {
                return hash;
            }
            std::string object = type + '\0' + content;
            fs::path object_path = repo_root / hash;
            
            std::ofstream out(
                object_path,
                std::ios::binary);

            out.write(
                object.data(),
                object.size());
            out.close();
            return hash;
        }
        // ############################################################################################

        std::string core::ObjectStore::generate_hash(std::string data)
        {
            unsigned char hash[SHA_DIGEST_LENGTH];

            SHA1(
                reinterpret_cast<const unsigned char *>(data.data()),
                data.size(),
                hash);

            std::stringstream ss;

            for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
            {
                ss << std::hex
                   << std::setw(2)
                   << std::setfill('0')
                   << (int)hash[i];
            }

            return ss.str();
        }
        // ############################################################################################

        std::string core::ObjectStore::get_object(std::string type, std::string hash)
        {
            fs::path repo_root = fs::path(core::Repository::find_repo_root()) / ".dagit/objects";
            fs::path object_path = repo_root / hash;

            if (!fs::exists(object_path))
            {
                throw std::runtime_error("Object not found: " + hash);
            }

            std::ifstream in(
                object_path,
                std::ios::binary);

            std::stringstream ss;
            ss << in.rdbuf();
            std::string s = ss.str();
            int i;
            for (i = 0; i < s.size(); i++)
            {
                if (s[i] == '\0')
                {
                    break;
                }
            }
            std::string object_type = s.substr(0, i);
            std::string content = s.substr(i + 1);
            if(object_type != type && type != "")
            {
                throw std::runtime_error("Object type mismatch: expected " + type + ", got " + object_type);
            }
            return content;
        }
        // ############################################################################################

        bool core::ObjectStore::object_exists(std::string hash)
        {
            fs::path repo_root = fs::path(core::Repository::find_repo_root()) / ".dagit/objects";
            fs::path object_path = repo_root / hash;
            return fs::exists(object_path);
        }
    
            

