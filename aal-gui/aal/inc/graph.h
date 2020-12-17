#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

struct Node {
    Brick element;
    std::vector<Node*> edgesIn;
    std::vector<Node*> edgesOut;
    size_t topoIndex;
    bool topoVisited;
    double topHeight;

    Node(double w, double h, double d) : 
        element({w, h, d}), topoIndex(-1), topoVisited(false), topHeight(0) {};
};

class DAG {
    size_t maxTopoIdx = 0;

    void doSortTopo(Node* target);
    
public:
    std::vector<Node*> nodes;

    void addNode(double, double, double);
    size_t size();
    void addEdge(Node*, Node*);
    void sortTopo();
    ~DAG();
};

Tower graph_get_highest_tower(std::istream &stream = std::cin);

#endif //GRAPH_H