#include "../../include/commands/hash_object_command.hpp"
#include "../../include/core/tree.hpp"
#include <string>


      std::string HashObjectCommand::execute(const std::string &file_path)
     {
        std::string hash= core::Tree::write_tree(file_path);
        std::cout << hash << std::endl;
        return hash;
     }
     void HashObjectCommand::setup(CLI::App &app){
        auto *sub = app.add_subcommand("hash-object", "Hash a file and print its hash");
            std::string file_path;

        sub->add_option(
            "file",
            file_path,
            "Path to the file to hash"  
        )->required();

        sub->callback([&file_path]()
        {
            execute(file_path);
        });
     }
