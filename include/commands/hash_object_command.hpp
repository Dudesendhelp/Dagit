#pragma once
#include "../core/object_store.hpp"
#include <iostream>
#include <string>
#include "../../external/CLI11.hpp"
#include "commands/icommand.hpp"

class HashObjectCommand :public ICommand
{
private:
    std::string file_path = "";
public:
     static std::string execute(const std::string &file_path);
     void setup(CLI::App &app) override;
};
