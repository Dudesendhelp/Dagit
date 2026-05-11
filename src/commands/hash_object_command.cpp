#include "../../include/commands/hash_object_command.hpp"
#include "../../include/core/object_store.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string HashObjectCommand::execute(const std::string &file_path)
{
    std::ifstream in(file_path, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Could not open file: " << file_path << std::endl;
        return "";
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string content = ss.str();
    
    std::string hash = core::ObjectStore::hash_object(content, "blob");
    std::cout << hash << std::endl;
    return hash;
}
     void HashObjectCommand::setup(CLI::App &app){
        auto *sub = app.add_subcommand("hash-object", "Hash a file and print its hash");

        sub->add_option(
            "file",
            this->file_path,
            "Path to the file to hash"  
        )->required();

        sub->callback([this]()
        {
            execute(this->file_path);
        });
     }
