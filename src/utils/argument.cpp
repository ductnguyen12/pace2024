//
// Created by ducnt on 12/24/23.
//
#include <utils/argument.h>
#include <algorithms/brute_force.h>
#include <algorithms/genetic_algorithm.h>
#include <algorithms/simulated_annealing.h>
#include <algorithms/random_search.h>
#include <stopping_conditions/combined_stopping_condition.h>
#include <stopping_conditions/time_stopping_condition.h>
#include <stopping_conditions/iteration_stopping_condition.h>

ProgramArgument *ProgramArgument::instance = nullptr;

ProgramArgument::ProgramArgument(const std::string &programName) {
    program = std::make_unique<argparse::ArgumentParser>(programName);
}

ProgramArgument *ProgramArgument::getInstance(const std::string &programName) {
    if (instance == nullptr) {
        instance = new ProgramArgument(programName);
    }
    return instance;
}

void ProgramArgument::parseArguments(int argc, char **args) const {
    program->add_argument("-f", "--file")
        .required()
        .help("input file to be read.");
    program->add_argument("-a", "--algorithm")
        .required()
        .default_value("BF")
        .choices("SA", "GA", "BF", "RS")
        .help("The algorithm to run. "
                "Either Simulated Annealing ('SA'), Genetic Algorithm ('GA'), or Brute Force ('BF').");
    program->add_argument("-t", "--time")
        .default_value("-1")
        .help("The maximum runtime (in milli-seconds) for the algorithm "
                "per repetition before the search is stopped.");
    program->add_argument("-i", "--iterations")
        .default_value("-1")
        .help("The maximum number of iterrators an algorithm would try to iterate.");

    try {
        program->parse_args(argc, args);
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        /*
        @Thang: Got 
            error: no match for ‘operator<<’ (operand types are ‘std::ostream’ {aka ‘std::basic_ostream<char>’} and ‘const std::unique_ptr<argparse::ArgumentParser>’)
        TODO: Fix this
        */
        // std::cerr << program;
        std::exit(1);
    }
}

std::string ProgramArgument::getFile() const {
    return program->get<std::string>("--file");
}

Algorithm* ProgramArgument::getAlgorithm(StoppingCondition &stoppingCondition) const {
    std::string name = program->get<std::string>("--algorithm");
    if (name == "SA") return new SimulatedAnnealing(stoppingCondition);
    else if (name ==  "GA") return new GeneticAlgorithm(stoppingCondition);
    else if (name == "BF") return new BruteForceAlgorithm(stoppingCondition);
    else if (name == "RS") return new RandomSearchAlgorithm(stoppingCondition);
    return nullptr;
}

StoppingCondition* ProgramArgument::getStoppingCondition() const {
    CombinedStoppingCondition* combined = new CombinedStoppingCondition();
    int time = std::stoi(program->get<std::string>("--time"));
    if (time >= 0) {
        combined->addCondition(new TimeStoppingCondition(time));
    }
    int iterations = std::stoi(program->get<std::string>("--iterations"));
    if (iterations >= 0) {
        combined->addCondition(new IterationStoppingCondition(iterations));
    }
    return combined;
}

unsigned int ProgramArgument::getPopulationSize() const {
    return program->get<unsigned int>("--size");
}

ProgramArgument::~ProgramArgument() = default;

