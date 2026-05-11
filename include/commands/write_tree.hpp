#pragma once
#include "../core/tree.hpp"
#include "icommand.hpp"
#include <string>

class WriteTreeCommand : public ICommand
{
public:    
     static std::string execute(const std::string &file_path);
     void setup(CLI::App &app) override;
};
        