#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>

using namespace std;

#define uint unsigned int
#define INFINITY numeric_limits<int>::max()
#define OneDimArray vector<uint>
#define TwoDimArray vector<OneDimArray>
#define KeyValue pair<int, uint>
#define Dictionary vector<KeyValue>

const int NUMBER_OF_NODES = 7;
const int MIN_DIST = 1;
const int MAX_DIST = 100;
int START_NODE = 0;

class Dijkstra
{
private:
    class NodesVisited
    {
    private:
        OneDimArray mVisited;

    public:
        void add(int &node)
        {
            mVisited.push_back(node);
        }
        bool hasVisited(int &node) const
        {
            bool result = false;
            if (find(mVisited.begin(), mVisited.end(), node) != mVisited.end())
            {
                result = true;
            }
            return result;
        }
        int Count() const { return mVisited.size(); }
    };

    class NodeDistance
    {
    private:
        TwoDimArray mCurrentDists;

    public:
        NodeDistance(TwoDimArray &currentDists) : mCurrentDists(currentDists) {}
        int Count() const { return mCurrentDists.size(); }
        int Position(int row, int col) const { return mCurrentDists[row][col]; }
        friend ostream &operator<<(ostream &output, NodeDistance const &obj)
        {
            for (int row = 0; row < obj.Count(); row++)
            {
                for (int col = 0; col < obj.Count(); col++)
                    output << obj.Position(row, col) << " ";
                cout << endl;
            }
            return output;
        }
    };

    NodeDistance mCurrentDists;
    Dictionary mDistSoFar;
    Dictionary mResultingEdges;
    int mNumberOfNodes;
    int mStartingNode;
    const int M_NON_NODE = -1;
    NodesVisited mNodesVisited;

    void mUpdateDistances(int updatedNode)
    {
        for (int i = 0; i < mNumberOfNodes; i++)
        {
            if (i == updatedNode)
                continue;

            if (mDistSoFar[i].second > mCurrentDists.Position(updatedNode, i))
                mDistSoFar[i] = KeyValue(updatedNode, mCurrentDists.Position(updatedNode, i));
        }
    }

public:
    Dijkstra(int &startingNode, TwoDimArray &currentDists)
        : mCurrentDists(currentDists), mNumberOfNodes(mCurrentDists.Count()), mStartingNode(startingNode)
    {
        for (int i = 0; i < mNumberOfNodes; i++)
            mDistSoFar.push_back(KeyValue(M_NON_NODE, INFINITY));

        mUpdateDistances(mStartingNode);
    }

    void FindNextClosestNode()
    {
        if (Completed())
            return;

        int source, destination;
        int currentMin = INFINITY;
        for (int i = 0; i < mNumberOfNodes; i++)
        {
            if (mDistSoFar[i].second < currentMin and !mNodesVisited.hasVisited(i))
            {
                destination = i;
                source = mDistSoFar[i].first;
                currentMin = mDistSoFar[i].second;
            }
        }
        mUpdateDistances(destination);
        mNodesVisited.add(destination);
        mResultingEdges.push_back(KeyValue(source, destination));
    }

    bool Completed() const { return mNodesVisited.Count() == mNumberOfNodes; }
    NodeDistance Distances() const { return mCurrentDists; }

    friend ostream &operator<<(ostream &output, Dijkstra const &obj)
    {
        for (int i = 0; i < obj.mNumberOfNodes; i++)
            output << obj.mResultingEdges[i].first << "-" << obj.mResultingEdges[i].second << endl;
        return output;
    }
};

int getRandInt(int lower, int upper)
{
    return rand() % upper + lower;
}

void initializeDistances(TwoDimArray &distances)
{
    for (int i = 0; i < NUMBER_OF_NODES; i++)
    {
        OneDimArray partial;
        for (int j = 0; j < NUMBER_OF_NODES; j++)
            if (i == j)
                partial.push_back(0);
            else
                partial.push_back(getRandInt(MIN_DIST, MAX_DIST));
        distances.push_back(partial);
    }
}

int main()
{
    srand(time(0));

    TwoDimArray dist;
    initializeDistances(dist);

    Dijkstra alg(START_NODE, dist);

    cout << alg.Distances();

    while (!alg.Completed())
        alg.FindNextClosestNode();

    cout << alg;

    return 0;
}
