#include "aal/inc/graph.h"

/*
 * DAG implementation
 */
void DAG::addNode(double w, double h, double d) {
    nodes.push_back(new Node(w, h, d));
}

size_t DAG::size() {
    return nodes.size();
}

void DAG::addEdge(Node* a, Node* b) {
    a->edgesOut.push_back(b);
    b->edgesIn.push_back(a);
}

void DAG::doSortTopo(Node* target) {
    for(size_t i = 0; i < target->edgesOut.size(); i++) {
        Node* dst = target->edgesOut[i];
        
        if(!dst->topoVisited) {
            dst->topoVisited = true;
            doSortTopo(dst);
        }
    }
    target->topoIndex = maxTopoIdx++;
}
    
void DAG::sortTopo() {
    for(size_t i = 0; i < size(); i++)
        if(!nodes[i]->topoVisited) {
            nodes[i]->topoVisited = true;
            doSortTopo(nodes[i]);
        }

    std::sort(nodes.begin(), nodes.end(), 
        [](Node*& a, Node*& b){return a->topoIndex > b->topoIndex;});
}

DAG::~DAG() {
    for (Node* node : nodes)
        delete node;
}


/*
 * Task solver
 */
Tower graph_get_highest_tower(std::istream &stream) {
    size_t n;
    double w, h, d;
    DAG graph;

    stream >> n;
    for(size_t i = 0; i < n; i++) {
        stream >> w >> h >> d;
        graph.addNode(w, h, d);
        graph.addNode(w, d, h);
        graph.addNode(d, h, w);
    }

    std::sort(graph.nodes.begin(), graph.nodes.end(), [](Node*& a, Node*& b) {
        return a->element.width < b->element.width;
    });

    // Connect nodes A,B if A can be put on B, i.e. A < B
    for(size_t i = 0; i < graph.nodes.size(); i++)
        for(size_t j = i; j < graph.nodes.size(); j++)
            if(graph.nodes[i]->element < graph.nodes[j]->element) {
                graph.addEdge(graph.nodes[i], graph.nodes[j]);
            }

    // Sort topologicaly
    graph.sortTopo();

    // Find highest piramid
    for(Node* node : graph.nodes) {
        node->topHeight += node->element.depth;

        for(Node* target : node->edgesOut) {
            if(target->topHeight < node->topHeight)
                target->topHeight = node->topHeight;
        }
    }

    double maxHeight = -1;
    Node* topBrick = NULL;
    for(Node* node : graph.nodes) {
        if(maxHeight < node->topHeight)
            maxHeight = node->topHeight, topBrick = node;
    }


    // Backtrack
    std::vector<Node*> nodes;
    nodes.push_back(topBrick);
    
    while(topBrick->edgesIn.size() > 0) {
        for(auto edgeIn : topBrick->edgesIn) {
            if(topBrick->element.depth + edgeIn->topHeight == topBrick->topHeight) {
                nodes.push_back(edgeIn);
                topBrick = edgeIn;
                break;
            }
        }
    }

    Tower tower;
    for(auto ir = nodes.rbegin(); ir != nodes.rend(); ++ir) {
        tower.bricks.push_back((*ir)->element);
        tower.depth += (*ir)->element.depth;
    }
    return tower;
}
