#include "../../include/core/commit.hpp"
#include "../../include/core/object_store.hpp"
#include "../../include/core/repository.hpp"
#include "../../include/core/tree.hpp"

std::string core::Commit::create_commit(std::string message)
{    fs::path repo_root = fs::path(core::Repository::find_repo_root()) ;
    std::string tree_hash = core::Tree::write_tree(repo_root);
    repo_root=repo_root/".dagit/objects";
    std::string content="tree " + tree_hash + "\n"+message;
    return core::ObjectStore::hash_object(content, "commit");
}

std::unordered_map<std::string, std::string> core::Commit::get_commit(const std::string& commit_hash)
{
    std::string content=core::ObjectStore::get_object("commit",commit_hash);
    std::string tree_hash=content.substr(5,40);
    std::string commit_message=content.substr(46);
    return {{"tree_hash", tree_hash}, {"message", commit_message}};
}

std::string core::Commit::get_head()
{
    fs::path repo_root = fs::path(core::Repository::find_repo_root());
    repo_root = repo_root / ".dagit/HEAD";
    

}