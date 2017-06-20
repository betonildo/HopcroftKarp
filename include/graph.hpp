#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "common.hpp"

class Graph {

public:
    Graph();
    void setSize(uint size);
    void set(uint u, uint v, uint w);
    void set(uint u, uint v);
    void setSource(uint s);
    void setSink(uint t);
    uint maximumMatching();
    bool breadthFirstSearch();
    bool depthFirstSearch(uint u);

private:
    std::map<uint, std::map<uint, uint> > m_graph;
    uint m_size;
    std::vector<uint> V1, V2;
    std::vector<uint> dist;
    uint source, sink;

};


#endif /*GRAPH_HPP*/
