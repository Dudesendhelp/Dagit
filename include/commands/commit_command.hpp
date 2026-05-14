#pragma once
#include "../../external/CLI11.hpp"
#include "../core/commit.hpp"
#include "icommand.hpp"

class CommitCommand : public ICommand
{
private:
     std::string message;
     void execute(std::string message)
     {
        std::string commit_hash=core::Commit::create_commit(message);
        std::cout<<commit_hash<<std::endl;
     }
public:
    void setup(CLI::App &app) override
    {
        auto commit_cmd = app.add_subcommand("commit", "Create a new commit with the current state of the working directory.");
        commit_cmd->add_option("-m", this->message, "The commit message")->required();
        commit_cmd->callback([this]() { this->execute(this->message); });
    }
};