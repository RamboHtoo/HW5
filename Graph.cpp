#include "Graph.h"

#include <stdexcept>
#include <string>

using namespace std;

// I used ChatGPT to discuss the Graph data structure,
// testing strategy, memory management, and code review.

bool Graph::IsPresent(nodekey_t key) const
{
    for(nodekey_t node : nodes)
    {
        if(node == key)
        {
            return true;
        }
    }

    return false;
}


void Graph::AddNode(nodekey_t key)
{
    // INVALID_NODE_KEY is reserved to mean that no valid node exists.
    if(key == INVALID_NODE_KEY)
    {
        throw invalid_argument("Invalid node key.");
    }

    if(IsPresent(key))
    {
        throw invalid_argument("Node already exists.");
    }

    nodes.push_back(key);
}


const GraphEdge* Graph::AddEdge(
    nodekey_t fromNodeKey,
    nodekey_t toNodeKey,
    unsigned int weight)
{
    // Both endpoints must already exist in the graph.
    if(!IsPresent(fromNodeKey) || !IsPresent(toNodeKey))
    {
        throw invalid_argument("Node does not exist.");
    }

    // Do not allow the same directed edge more than once.
    for(GraphEdge* edge : edges)
    {
        if(edge->from == fromNodeKey &&
           edge->to == toNodeKey)
        {
            throw invalid_argument("Edge already exists.");
        }
    }

    // GraphEdges are stored on the heap as required by the assignment.
    GraphEdge* newEdge = new GraphEdge;

    newEdge->from = fromNodeKey;
    newEdge->to = toNodeKey;
    newEdge->weight = weight;

    edges.push_back(newEdge);

    return newEdge;
}


string Graph::NodesToString() const
{
    string result = "[";

    for(size_t i = 0; i < nodes.size(); i++)
    {
        result += "(" + to_string(nodes[i]) + ")";

        if(i != nodes.size() - 1)
        {
            result += ", ";
        }
    }

    result += "]";

    return result;
}


string Graph::EdgesToString() const
{
    string result = "[";

    for(size_t i = 0; i < edges.size(); i++)
    {
        GraphEdge* edge = edges[i];

        result += "((";
        result += to_string(edge->from);
        result += ")->(";
        result += to_string(edge->to);
        result += ") w:";
        result += to_string(edge->weight);
        result += ")";

        if(i != edges.size() - 1)
        {
            result += ", ";
        }
    }

    result += "]";

    return result;
}


set<const GraphEdge*> Graph::GetOutwardEdgesFrom(
    nodekey_t nodeKey) const
{
    if(!IsPresent(nodeKey))
    {
        throw invalid_argument("Node does not exist.");
    }

    set<const GraphEdge*> result;

    for(GraphEdge* edge : edges)
    {
        if(edge->from == nodeKey)
        {
            result.insert(edge);
        }
    }

    return result;
}


set<nodekey_t> Graph::GetNodes() const
{
    set<nodekey_t> result;

    for(nodekey_t node : nodes)
    {
        result.insert(node);
    }

    return result;
}


size_t Graph::Size() const
{
    return edges.size();
}


size_t Graph::Order() const
{
    return nodes.size();
}


Graph::~Graph()
{
    // The Graph owns every GraphEdge created with new,
    // so each edge must be deleted when the Graph is destroyed.
    for(GraphEdge* edge : edges)
    {
        delete edge;
    }
}