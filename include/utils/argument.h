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

    std::string getFile() const;
    bool getLowerBound() const;
    size_t getSeed() const;
    Algorithm* getAlgorithm() const;
    int getRepetition() const;
    StoppingCondition* getStoppingCondition() const;
int getPopulationSize() const;
};

#endif //ARGUMENTS_H