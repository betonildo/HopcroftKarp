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
    bool search_paths(std::vector<uint>& M, std::vector<uint>& P);
    std::vector<uint> getFreeVertices();
    bool isFree(uint u);

private:
    std::map<uint, std::map<uint, uint> > m_graph;
    std::vector<uint> m_v_graph;
    uint m_size;
    std::vector<uint> Pair_U, Pair_V;
    std::vector<uint> dist;

};


#endif /*GRAPH_HPP*/
