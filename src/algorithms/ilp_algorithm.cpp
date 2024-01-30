//
// Created by ducnt on 1/29/24.
//

#include <algorithms/ilp_algorithm.h>
#include <gurobi_c++.h>
#include <algorithm>
#include <stopping_conditions/time_stopping_condition.h>

ILPAlgorithm::ILPAlgorithm(StoppingCondition &stoppingCondition) : Algorithm(stoppingCondition) {
    auto *timeStoppingCondition = dynamic_cast<TimeStoppingCondition *>(&stoppingCondition);
    if (timeStoppingCondition != nullptr) {
        duration = &timeStoppingCondition->getDuration();
    }
}

Solution ILPAlgorithm::findSolution(BipartiteGraph *graph) {
    // Crossing matrix
    auto c = graph->computeCrossingMatrix();
    // Order matrix
    auto *m = new std::vector<std::vector<GRBVar>>();

    // Create an environment
    GRBEnv env = GRBEnv(true);
    // env.set("LogFile", "mip1.log");
    env.set(GRB_IntParam_OutputFlag, 0);
    env.start();

    // Create an empty model
    GRBModel model = GRBModel(env);
    // Force model use only 1 thread
    model.set(GRB_IntParam_Threads, 1);
    if (duration != nullptr)
        model.set(GRB_DoubleParam_TimeLimit, double(duration->count()) / 1000000);

    // Create variables
    for (int i = 0; i < graph->getN1(); i++) {
        m->emplace_back();
        for (int j = 0; j < graph->getN1(); j++) {
            m->at(i).push_back(model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "m[" + std::to_string(i) + "]"));
        }
    }

    // Set objective: maximize x + y + 2 z
    GRBLinExpr objective;
    std::vector<GRBTempConstr> constraints;
    for (int i = 0; i < graph->getN1(); i++) {
        for (int j = 0; j < graph->getN1(); j++) {
            if (i == j)
                continue;
            objective = objective + m->at(i).at(j) * c.at(i).at(j);
            constraints.push_back(m->at(i).at(j) + m->at(j).at(i) == 1);
            for (int k = 0; k < graph->getN1(); k++) {
                if (k != j && k != i) {
                    constraints.push_back(
                            m->at(i).at(j)
                            + m->at(j).at(k)
                            - m->at(i).at(k)
                            <= 1
                    );
                }
            }
        }
    }
    model.setObjective(objective, GRB_MINIMIZE);
    // Add constraint: x + 2 y + 3 z <= 4
    for (const auto &constraint: constraints) {
        model.addConstr(constraint);
    }

    // Optimize model
    model.optimize();

    int minCross = int(model.get(GRB_DoubleAttr_ObjVal));
    auto *order = new std::vector<int>();
    for (int i = 0; i < graph->getN1(); i++) {
        order->push_back(i);
    }

    auto crossingComparator = [&m](auto const &i, auto const &j) {
        return int(m->at(i).at(j).get(GRB_DoubleAttr_X)) == 1;
    };

    std::sort(order->begin(), order->end(), crossingComparator);

    return {
            minCross,
            order,
    };
}
