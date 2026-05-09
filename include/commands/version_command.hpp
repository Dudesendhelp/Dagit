#pragma once
#include "commands/icommand.hpp"
#include <iostream>

class VersionCommand : public ICommand
{
    public:
    void setup(CLI::App &app) override
    {

             auto *sub =
            app.add_subcommand(
                "version",
                "Display DAGit version"
            );
        sub->callback([](){
            std::cout <<"DAGit version 1.0.0" << std::endl;
        });
    }
};