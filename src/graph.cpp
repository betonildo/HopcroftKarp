#include "graph.hpp"

Graph::Graph() {

}

void Graph::setSize(uint size) {
    m_size = size + 1;
}

void Graph::set(uint u, uint v, uint w) {
    m_graph[u][v] = w;
}

void Graph::set(uint u, uint v) {
    m_graph[u][v] = 1;
}

void Graph::setSource(uint s) {
    source = s;
}

void Graph::setSink(uint t) {
    sink = t;
}

uint Graph::maximumMatching() {

//    std::vector<uint> M;
//    M.clear();
//    M.resize(m_size);
//    while (search_paths(M, P))
//        M = simetricDiff(M, P);
//    return cardinality(M);

//    function Hopcroft-Karp
//        for each u in U
//            Pair_U[u] = NIL
//        for each v in V
//            Pair_V[v] = NIL
//        matching = 0
//        while BFS() == true
//            for each u in U
//                if Pair_U[u] == NIL
//                    if DFS(u) == true
//                        matching = matching + 1
//        return matching

    V1.resize(m_size);
    V2.resize(m_size);
    dist.resize(m_size);

    std::memset(V1.data(), 0, m_size);
    std::memset(V2.data(), 0, m_size);

    uint matching = 0;

    while(breadthFirstSearch()) {

        for (auto uvw : m_graph) {

            uint u = uvw.first;

            if (V1[u] == 0) {
                if (depthFirstSearch(u)) {
                    matching += 1;
                }
            }
        }
    }

    return matching;
}

bool Graph::breadthFirstSearch() {
//    function BFS ()
//        for each u in U
//            if Pair_U[u] == NIL
//                Dist[u] = 0
//                Enqueue(Q,u)
//            else
//                Dist[u] = ∞
//        Dist[NIL] = ∞
//        while Empty(Q) == false
//            u = Dequeue(Q)
//            if Dist[u] < Dist[NIL]
//                for each v in Adj[u]
//                    if Dist[ Pair_V[v] ] == ∞
//                        Dist[ Pair_V[v] ] = Dist[u] + 1
//                        Enqueue(Q,Pair_V[v])
//        return Dist[NIL] != ∞

    std::queue<uint> Q;

    for (auto uvw : m_graph) {

        uint u = uvw.first;
        if (V1[u] == 0) {
            dist[u] = 0;
            Q.push(u);
        }
        else {
            dist[u] = INF;
        }
    }


    dist[0] = INF;

    while(not Q.empty()) {
        uint u = Q.front();
        Q.pop();

        if (dist[u] < dist[0]) {

            for (auto vw : m_graph[u]) {
                uint v = vw.first;

                if (dist[V2[v]] == INF) {
                    dist[V2[v]] = dist[u] + 1;
                    Q.push(V2[v]);
                }
            }
        }
    }

    return dist[0] != INF;
}

bool Graph::depthFirstSearch(uint u) {
/*
function DFS (u)
    if u != NIL
        for each v in Adj[u]
            if Dist[ Pair_V[v] ] == Dist[u] + 1
                if DFS(Pair_V[v]) == true
                    Pair_V[v] = u
                    Pair_U[u] = v
                    return true
        Dist[u] = ∞
        return false
    return true
*/
    if (u != 0) {

        for (auto vw : m_graph[u]) {
            uint v = vw.first;

            if (dist[V2[v]] == dist[u] + 1) {
                if (depthFirstSearch(V2[v])) {
                    V2[v] = u;
                    V1[u] = v;
                    return true;
                }
            }
        }

        dist[u] = INF;
        return false;
    }

    return true;
}
