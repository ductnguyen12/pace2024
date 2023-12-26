//
// Created by ducnt on 12/24/23.
//
#include <utils/argument.h>

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
    program->add_argument("-a", "--algorithm")
            .required()
            .choices("SA", "GA")
            .help("The algorithm to run. "
                  "Either Simulated Annealing ('SA') or Genetic Algorithm ('GA').");
    program->add_argument("-t", "--time")
            .default_value(300)
            .help("The maximum runtime (in seconds) for the algorithm "
                  "per repetition before the search is stopped.");
    program->add_argument("-z", "--size")
            .default_value(20)
            .help("The population size 𝑧 > 1 to be used for genetic algorithms");

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

std::string ProgramArgument::getAlgorithm() const {
    return program->get<std::string>("--algorithm");
}

int ProgramArgument::getMaxTime() const {
    return program->get<int>("--time");
}

unsigned int ProgramArgument::getPopulationSize() const {
    return program->get<unsigned int>("--size");
}

ProgramArgument::~ProgramArgument() = default;

