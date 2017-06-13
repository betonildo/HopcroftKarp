#include "graph.hpp"

Graph::Graph() {

}

void Graph::setSize(uint size) {
    m_size = size + 1;
    m_v_graph.resize(m_size);
}

void Graph::set(uint u, uint v, uint w) {
    m_graph[u][v] = w;
}

void Graph::set(uint u, uint v) {
    m_v_graph[u] = v;
    m_graph[u][v] = 1;
}

void Graph::setSource(uint s) {

}

void Graph::setSink(uint t) {

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

    Pair_U.resize(m_size);
    Pair_V.resize(m_size);
    dist.resize(m_size);

    std::memset(Pair_U.data(), 0, m_size);
    std::memset(Pair_V.data(), 0, m_size);

    for (auto uvw : m_graph) {

        uint u = uvw.first;
        Pair_U[u] = 0;

        for (auto vw : uvw.second) {
            uint v = vw.first;
            Pair_V[v] = 0;
        }
    }

    uint matching = 0;

    while(breadthFirstSearch()) {

        for (auto uvw : m_graph) {

            uint u = uvw.first;

            if (Pair_U[u] == 0) {
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
        if (Pair_U[u] == 0) {
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

                if (dist[Pair_V[v]] == INF) {
                    dist[Pair_V[v]] = dist[u] + 1;
                    Q.push(Pair_V[v]);
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

            if (dist[Pair_V[v]] == dist[u] + 1) {
                if (depthFirstSearch(Pair_V[v])) {
                    Pair_V[v] = u;
                    Pair_U[u] = v;
                    return true;
                }
            }
        }

        dist[u] = INF;
        return false;
    }

    return true;
}

bool Graph::search_paths(std::vector<uint>& M, std::vector<uint>& P) {
    std::vector<bool> m;
    m.resize(m_size);

    std::vector<uint> d;
    d.resize(m_size);
    std::vector<uint> U1 = getFreeVertices();
    for (uint u : U1)
        d[u] = 0;

    std::vector<uint> U2;
    bool found;

    do {

        // verify termination
        bool shouldTerminate = true;
        for (bool mi : m) {
            if (!mi) shouldTerminate = false;
        }

        if (shouldTerminate) break;


        U2.clear();

        for (uint u : U1) {
            m[u] = false;

            for (auto vw : m_graph[u]) {

                uint v = vw.first;
                if (M[v] == 0) {

                    if (NOT m[v]) {
                        d[v] = d[u] + 1;
                        U2.push_back(v);
                    }
                }
            }
        }

        found = false;

        U1.clear();

        for (uint u : U2) {
            m[u] = true;

            if (isFree(u)) {
                found = true;
            }
            else {
                uint v = m[u];
                if (NOT m[v]) {
                    d[v] = d[u] + 1;
                    U1.push_back(v);
                }
            }
        }

    }while(NOT found);

    return found;
}

std::vector<uint> Graph::getFreeVertices() {
    std::vector<uint> freeVertices;

    for (uint i = 0; i < m_v_graph.size(); i++) {
        if (m_v_graph[i] == 0)
            freeVertices.push_back(i);
    }

    return freeVertices;
}

bool Graph::isFree(uint u) {
    return m_v_graph[u] == 0;
}
