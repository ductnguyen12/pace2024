//
// Created by ducnt on 12/24/23.
//
#include <utils/argument.h>
#include <algorithms/brute_force.h>
#include <algorithms/genetic_algorithm.h>
#include <algorithms/simulated_annealing.h>
#include <algorithms/ilp_algorithm.h>

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
    program->add_argument("-i", "--input")
        .required()
        .help("input file to be read.");
    program->add_argument("-a", "--algorithm")
        .required()
        .default_value("BF")
        .choices("SA", "GA", "BF", "ILP")
        .help("The algorithm to run. "
                "Either Simulated Annealing ('SA'), Genetic Algorithm ('GA'), "
                "Brute Force ('BF'), or Integer Linear Programming ('ILP').");
    program->add_argument("-t", "--time")
        .default_value("1000")
        .help("The maximum runtime (in milli-seconds) for the algorithm "
                "per repetition before the search is stopped.");
    // program->add_argument("-z", "--size")
    //         .default_value(20)
    //         .help("The population size 𝑧 > 1 to be used for genetic algorithms");

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

std::string ProgramArgument::getInput() const {
    return program->get<std::string>("--input");
}

Algorithm* ProgramArgument::getAlgorithm(StoppingCondition &stoppingCondition) const {
    std::string name = program->get<std::string>("--algorithm");
    if (name == "SA") return new SimulatedAnnealing(stoppingCondition);
    else if (name ==  "GA") return new GeneticAlgorithm(stoppingCondition);
    else if (name == "BF") return new BruteForceAlgorithm(stoppingCondition);
    else if (name == "ILP") return new ILPAlgorithm(stoppingCondition);
    return nullptr;
}

int ProgramArgument::getMaxTime() const {
    return std::stoi(program->get<std::string>("--time"));
}

unsigned int ProgramArgument::getPopulationSize() const {
    return program->get<unsigned int>("--size");
}

ProgramArgument::~ProgramArgument() = default;

