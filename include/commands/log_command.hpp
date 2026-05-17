#pragma once
#include "../../external/CLI11.hpp"
#include "../../include/core/commit.hpp"
#include "../../include/core/repository.hpp"
#include <iostream>
#include "icommand.hpp"

class LogCommand : public ICommand
{
    private:
    std::string commit_hash;
    void execute(std::string commit_hash);
    public:
    void setup(CLI::App& app) override;
};