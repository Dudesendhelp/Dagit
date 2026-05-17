#include "../../include/commands/log_command.hpp"
#include "../../include/core/object_store.hpp"

void LogCommand::setup(CLI::App &app)
{
    auto sub=app.add_subcommand("log", "Show commit history");
    this->commit_hash="";
    sub->add_option("commit_hash", this->commit_hash, "Hash of the commit to start from");
    sub->callback([this]() { this->execute(this->commit_hash); });
}

void LogCommand::execute(std::string commit_hash)
{
    if(commit_hash.empty())
    {
        commit_hash=core::Commit::get_head();
    }
    while(true)
    {
        std::unordered_map<std::string, std::string> commit_data=core::Commit::get_commit(commit_hash);
        std::string tree_hash=commit_data["tree_hash"];
        std::string parent_hash=commit_data["parent_hash"];
        std::string message=commit_data["message"];
        std::string content=core::ObjectStore::get_object("commit", commit_hash);
        std::cout << content << std::endl;
        if(parent_hash=="none")
        {
            break;
        }
        commit_hash=parent_hash;
    }
}