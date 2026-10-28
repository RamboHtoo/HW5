#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

// nodes are essentially just their key value
#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

// Each GraphEdge is created on the heap.
struct GraphEdge {
    nodekey_t from;
    nodekey_t to;
    unsigned int weight;
};

class Graph {

public:
    ~Graph();

    // Throws invalid_argument for invalid input.
    void AddNode(nodekey_t key = 0);

    const GraphEdge* AddEdge(
        nodekey_t fromNodeKey,
        nodekey_t toNodeKey,
        unsigned int weight = 0
    );

    // Returns true if the node key exists.
    bool IsPresent(nodekey_t key) const;

    // Testing/debugging helpers.
    string NodesToString() const;
    string EdgesToString() const;

    // Returns all outward edges from the given node.
    set<const GraphEdge*> GetOutwardEdgesFrom(nodekey_t nodeKey) const;

    // Returns all node keys.
    set<nodekey_t> GetNodes() const;

    // Number of edges.
    size_t Size() const;

    // Number of nodes.
    size_t Order() const;

private:
    // A vector keeps insertion order for NodesToString().
    vector<nodekey_t> nodes;

    // GraphEdge objects are allocated on the heap.
    vector<GraphEdge*> edges;
};

#endif