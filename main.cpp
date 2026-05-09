#include "CLI11.hpp"
#include "commands/icommand.hpp"
#include "commands/init_command.hpp"
#include "commands/version_command.hpp"
#include <memory>
#include <vector>

int main(int argc, char *argv[])
{
    CLI::App app{"DAGit - A simple version control system"};
    
    app.require_subcommand(1);

    std:: vector<std::unique_ptr<ICommand>> commands;

    commands.push_back(std::make_unique<InitCommand>());
    commands.push_back(std::make_unique<VersionCommand>());

    for(auto &cmd : commands)
    {
        cmd->setup(app);
    }

    CLI11_PARSE(app, argc, argv);
    return 0;
}