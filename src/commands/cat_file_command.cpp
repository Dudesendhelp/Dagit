#include "../../include/commands/cat_file_command.hpp"
#include "../../include/core/object_store.hpp"


  void CatFileCommand::execute(const std::string &hash)
   {
        if(core::ObjectStore::object_exists(hash))
        {
            std::string content=core::ObjectStore::get_object("",hash);
            std::cout << content << std::endl;
        }
        else
        {
            std::cerr << "Object with hash " << hash << " does not exist." << std::endl;
        }
   }
   void CatFileCommand::setup(CLI::App &app){
        auto *sub=app.add_subcommand("cat-file", "Print the content of an object given its hash");
        sub->add_option(
            "hash",
            this->hash,
            "Hash of the object to print"
        )->required();
        sub->callback([this]()
        {
            execute(this->hash);
        });
   }

