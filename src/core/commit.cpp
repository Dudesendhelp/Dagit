#include "../../include/core/commit.hpp"
#include "../../include/core/object_store.hpp"
#include "../../include/core/repository.hpp"
#include "../../include/core/tree.hpp"
using namespace std;

std::string core::Commit::create_commit(std::string message)
{    fs::path repo_root = fs::path(core::Repository::find_repo_root()) ;
    std::string tree_hash = core::Tree::write_tree(repo_root);
    
    fs::path head_path = repo_root / ".dagit/HEAD";
    std::ifstream head_file(head_path);
     std::stringstream buffer;
    buffer << head_file.rdbuf();
    std::string content = buffer.str();
    if(content.empty())
    {
        content="tree " + tree_hash + "\n" + "parent none" + "\n" + message;
        std::string commit_hash = core::ObjectStore::hash_object(content, "commit");
        set_head(commit_hash);
        return commit_hash;
    }
   
    content="tree " + tree_hash + "\n"+ "parent " + get_head() + "\n\n" + message;
    std::string commit_hash = core::ObjectStore::hash_object(content, "commit");
    set_head(commit_hash);
    return commit_hash;
}

std::unordered_map<std::string, std::string> core::Commit::get_commit(const std::string& commit_hash)
{
    std::string content=core::ObjectStore::get_object("commit",commit_hash);
    std::stringstream ss(content);

std::string line;
std::string tree_hash;
std::string parent_hash;
std::string commit_message;
while (std::getline(ss, line))
{
    if (line.substr(0, 4) == "tree")
    {
        tree_hash = line.substr(5);
    }
    else if (line.substr(0, 6) == "parent")
    {
        parent_hash = line.substr(7);
    }
    else if (line.empty())
    {
        std::getline(ss, commit_message);
        break;
    }
}
    
    return {{"tree_hash", tree_hash}, {"parent_hash", parent_hash}, {"message", commit_message}};
}

std::string core::Commit::get_head()
{
    fs::path repo_root = fs::path(core::Repository::find_repo_root());
    repo_root = repo_root / ".dagit/HEAD";
    std::ifstream head_file(repo_root);
       std::stringstream buffer;
    buffer << head_file.rdbuf();

    std::string content = buffer.str();
    return content.substr(0, 40);
}

void core::Commit::set_head(const std::string& commit_hash)
{
    fs::path repo_root = fs::path(core::Repository::find_repo_root());
    repo_root = repo_root / ".dagit/HEAD";
    std::ofstream file(repo_root);

    file << commit_hash;

    file.close();
    }