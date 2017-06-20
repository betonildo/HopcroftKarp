#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace boost;

// graph element descriptors
typedef adjacency_list_traits<vecS, vecS, undirectedS>::vertex_descriptor Node;
typedef adjacency_list_traits<vecS, vecS, undirectedS>::edge_descriptor Edge;

// information stored in vertices
struct VertexInformation
{
    Node mate; // partner or graph_traits<Graph>::null_vertex()
};
// information stored in edges
struct EdgeInformation
{
};

// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS, vecS, undirectedS, VertexInformation, EdgeInformation> Graph;

void biPartedGraphGenerator(unsigned n, unsigned m, const char *outputFile)
{

    srand48(time(0));

    std::ofstream outFileHandler(outputFile);

    // (1) generate random bi-partite graph
    Graph g;

    int middle_of_vertices = n / 2;

    for (unsigned i = 0; i < n; i++)
        add_vertex(g);

    double edges_per_vertex = ((double)m) / n;
    int vertex_number = 0;
    unsigned edge_countdown = m;

    for (unsigned i = 0; edge_countdown > 0; edge_countdown--) {
        unsigned j = middle_of_vertices + vertex_number;
        Edge e = add_edge(i, j, g).first;
        vertex_number++;
        i = (i + 1) % middle_of_vertices;
    }

    // (2) get maximum matching
    edmonds_maximum_cardinality_matching(g, get(&VertexInformation::mate, g));
    unsigned card = 0;
    graph_traits<Graph>::vertex_iterator vb, ve;
    for (tie(vb, ve) = vertices(g); vb != ve; vb++)
        if (g[*vb].mate != graph_traits<Graph>::null_vertex())
            card++;
    outFileHandler << "c The cardinality of a maximum matching is " << card / 2 << "." << endl;

    // (3) print out in DIMACS format
    outFileHandler << "c Bi-partite graph" << endl
                   << endl;
    outFileHandler << "p edge " << num_vertices(g) << " " << num_edges(g) << endl;
    graph_traits<Graph>::edge_iterator eb, ee;
    for (tie(eb, ee) = edges(g); eb != ee; eb++)
        outFileHandler << "e " << source(*eb, g) + 1 << " " << target(*eb, g) + 1 << endl;
}
