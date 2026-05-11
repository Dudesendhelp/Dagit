#include "CLI11.hpp"
#include "include/commands/icommand.hpp"
#include "include/commands/init_command.hpp"
#include "include/commands/version_command.hpp"
#include "include/commands/write_tree.hpp"
#include "include/commands/hash_object_command.hpp"
#include "include/commands/cat_file_command.hpp"
#include <memory>
#include <vector>

int main(int argc, char *argv[])
{
    CLI::App app{"DAGit - A simple version control system"};
    
    app.require_subcommand(1);

    std:: vector<std::unique_ptr<ICommand>> commands;

    commands.push_back(std::make_unique<InitCommand>());
    commands.push_back(std::make_unique<VersionCommand>());
    commands.push_back(std::make_unique<WriteTreeCommand>());
    commands.push_back(std::make_unique<HashObjectCommand>());
    commands.push_back(std::make_unique<CatFileCommand>());

    for(auto &cmd : commands)
    {
        cmd->setup(app);
    }

    CLI11_PARSE(app, argc, argv);
    return 0;
}