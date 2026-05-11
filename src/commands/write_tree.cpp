#include "../../include/commands/write_tree.hpp"
#include <iostream>


    std::string WriteTreeCommand::execute(const std::string &file_path)
        {
            std::string hash = core::Tree::write_tree(file_path);
            std::cout << hash << std::endl;
            return hash;
        }
        void WriteTreeCommand::setup(CLI::App &app) {
            auto *sub= app.add_subcommand("write-tree", "Write a tree object from the current directory and print its hash");
            sub->add_option(
                "file",
                this->file_path,
                "Path to the directory to write the tree from"
            );
            sub->callback([this]()
            {
                execute(this->file_path);
            });
        }

