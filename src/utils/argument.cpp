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
#if defined(GUROBI_REQUIRED)
#include <algorithms/ilp_algorithm.h>
#endif

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
    program->add_argument("-l", "--lowerbound")
        .default_value(false)
        .implicit_value(true)
        .help("find the lower bound only, will ignore other arguemnts except -f (--file)");
    program->add_argument("-f", "--file")
        .required()
        .help("input file to be read.");
    program->add_argument("-a", "--algorithm")
        .required()
        .default_value("BF")
        .choices("SA", "GA", "BF", "RS", "ILP")
        .help("The algorithm to run. "
                "Either Simulated Annealing ('SA'), Genetic Algorithm ('GA'), "
                "Brute Force ('BF'), or Integer Linear Programming ('ILP').");
    program->add_argument("-t", "--time")
        .default_value("-1")
        .help("The maximum runtime (in milli-seconds) for the algorithm "
                "per repetition before the search is stopped.");
    program->add_argument("-i", "--iterations")
        .default_value("-1")
        .help("The maximum number of iterrators an algorithm would try to iterate.");
    program->add_argument("-s", "--size")
        .default_value("100")
        .help("Population size for heuristic algorithms");
    program->add_argument("-r", "--repetitions")
        .default_value("1")
        .help("The repetitions number");
    program->add_argument("--seed")
        .default_value("-1")
        .help("Specific seed for the algorithm");

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

Algorithm* ProgramArgument::getAlgorithm() const {
    std::string name = program->get<std::string>("--algorithm");
    if (name == "SA") return new SimulatedAnnealing();
    else if (name ==  "GA") {
        return new GeneticAlgorithm(getPopulationSize());
    }
    else if (name == "BF") return new BruteForceAlgorithm();
    else if (name == "RS") return new RandomSearchAlgorithm();
#if defined(GUROBI_REQUIRED)
    else if (name == "ILP") return new ILPAlgorithm();
#endif
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

int ProgramArgument::getPopulationSize() const {
    return std::stoi(program->get<std::string>("--size"));
}

int ProgramArgument::getRepetition() const {
    return std::stoi(program->get<std::string>("--repetitions"));
}

bool ProgramArgument::getLowerBound() const {
    return program->get<bool>("--lowerbound");
}

size_t ProgramArgument::getSeed() const {
    size_t seed;
    sscanf(program->get<std::string>("--seed").c_str(), "%zu", &seed);
    return seed;
}

ProgramArgument::~ProgramArgument() = default;

