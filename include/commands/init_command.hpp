#pragma once
#include "commands/icommand.hpp"
#include "core/repository.hpp"


using namespace core;
class InitCommand :public ICommand
{
    public:
    void setup(CLI::App &app) override
    {
        auto *sub =
            app.add_subcommand(
                "init",
                "Initialize a new DAGit repository in the current directory"
            );
        sub->callback([](){
            core::Repository::init();
        });
    }
};