#pragma once
#include "../core/object_store.hpp"
#include "../core/tree.hpp"
#include "icommand.hpp"
#include <iostream>
#include <string>
 
class CatFileCommand : public ICommand
{
private:
    std::string hash = "";
public:
   static void execute(const std::string &hash);
   void setup(CLI::App &app) override;
};

