#pragma once
#include "icommand.hpp"
#include "../core/tree.hpp"
#include "../../external/CLI11.hpp"

class ReadTreeCommand : public ICommand
{
private:
    std::string tree_hash;
public:
    void execute(const std::string& tree_hash)
    {
        core::Tree::read_tree(tree_hash);
    }
    void setup(CLI::App &app) override
    {
        auto read_tree_cmd = app.add_subcommand("read-tree", "Restore the working directory to match the state of a specific tree.");
        read_tree_cmd->add_option("tree_hash", this->tree_hash, "The hash of the tree to restore")->required();
        read_tree_cmd->callback([this]() {this->execute(this->tree_hash); });
    }
};