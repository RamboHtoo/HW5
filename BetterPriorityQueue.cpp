#include "BetterPriorityQueue.h"
#include <utility>

using namespace std;


// I used ChatGPT to discuss priority queue behavior,
// binary-heap ordering, testing, and code review.


bool BetterPriorityQueue::Contains(const BPQNode &node) const
{
    for(const BPQNode &current : this->c)
    {
        if(current == node)
        {
            return true;
        }
    }

    return false;
}


bool BetterPriorityQueue::Update(const BPQNode &node)
{
    for(size_t i = 0; i < this->c.size(); i++)
    {
        if(this->c[i] == node)
        {
            // Dijkstra only needs a priority to become smaller.
            // Equal or larger priorities do not improve the path.
            if(node.pri >= this->c[i].pri)
            {
                return false;
            }

            this->c[i].pri = node.pri;

            // Lowering a priority may violate the min-heap ordering.
            // Move the changed node upward until its parent has a
            // priority less than or equal to it.
            size_t current = i;

            while(current > 0)
            {
                size_t parent = (current - 1) / 2;

                if(this->c[current].pri <
                   this->c[parent].pri)
                {
                    std::swap(this->c[current],
                            this->c[parent]);

                    current = parent;
                }
                else
                {
                    break;
                }
            }

            return true;
        }
    }

    return false;
}


string BetterPriorityQueue::BPQNodeToString(
    const BPQNode &node)
{
    return "(" +
           to_string(node.gnode) +
           ", pri: " +
           to_string(node.pri) +
           ")";
}


string BetterPriorityQueue::ToString() const
{
    string result = "[";

    for(size_t i = 0; i < this->c.size(); i++)
    {
        result += BPQNodeToString(this->c[i]);

        if(i != this->c.size() - 1)
        {
            result += ", ";
        }
    }

    result += "]";

    return result;
}