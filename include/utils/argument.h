//
// Created by ducnt on 12/24/23.
//

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <argparse/argparse.hpp>

class ProgramArgument {
private:
    std::unique_ptr<argparse::ArgumentParser> program;
    static ProgramArgument *instance;

    explicit ProgramArgument(const std::string &programName);

public:
    ProgramArgument(const ProgramArgument &obj) = delete;

    ~ProgramArgument();

    static ProgramArgument *getInstance(const std::string &programName);

    void parseArguments(int argc, char **args) const;

    [[nodiscard]] std::string getAlgorithm() const;

    [[nodiscard]] int getMaxTime() const;

    [[nodiscard]] unsigned int getPopulationSize() const;
};

#endif //ARGUMENTS_H