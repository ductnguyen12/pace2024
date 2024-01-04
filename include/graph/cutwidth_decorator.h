#ifndef CUTWIDTH_H
#define CUTWIDTH_H

#include <graph/bipartite_graph.h>

class CutWidthDecorator : public BipartiteGraph {
private:
    BipartiteGraph* decoratedGraph;
public:
    CutWidthDecorator(BipartiteGraph* graph);
};

#endif