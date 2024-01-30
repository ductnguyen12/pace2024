//
// Created by ducnt on 12/24/23.
//

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <argparse/argparse.hpp>
#include <algorithms/brute_force.h>
#include <algorithms/genetic_algorithm.h>
#include <memory>

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

    [[nodiscard]] std::string getFile() const;

    [[nodiscard]] Algorithm* getAlgorithm() const;

    [[nodiscard]] StoppingCondition* getStoppingCondition() const;

    [[nodiscard]] int getPopulationSize() const;
};

#endif //ARGUMENTS_H