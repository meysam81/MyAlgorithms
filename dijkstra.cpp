#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
using namespace std;

#define INFINITY numeric_limits<int>::max()
#define OneDimArray vector<int>
#define TwoDimArray vector<OneDimArray>
#define KeyValue pair<int, int>
#define Dictionary vector<KeyValue>

const int NUMBER_OF_NODES = 7;
const int MIN_DIST = 1;
const int MAX_DIST = 100;
const int START_NODE = 0;

void updateDistances(int updatedNode, Dictionary &distSoFar, TwoDimArray &currentDists)
{
    for (int i = 0; i < NUMBER_OF_NODES; i++)
    {
        if (i == updatedNode)
            continue;
        if (distSoFar[i].second > currentDists[updatedNode][i])
            distSoFar[i] = KeyValue(updatedNode, currentDists[updatedNode][i]);
    }
}

template <typename T>
bool contains(vector<T> vec, const T &elem)
{
    bool result = false;
    if (find(vec.begin(), vec.end(), elem) != vec.end())
    {
        result = true;
    }
    return result;
}

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
        {
            if (i == j)
            {
                partial.push_back(0);
            }
            else
            {
                partial.push_back(getRandInt(MIN_DIST, MAX_DIST));
            }
        }
        distances.push_back(partial);
    }
}

int main()
{
    srand(time(0));

    OneDimArray visited;
    Dictionary distSoFar;
    Dictionary resultingEdges;

    for (int i = 0; i < NUMBER_OF_NODES; i++)
        distSoFar.push_back(KeyValue(INFINITY, INFINITY));

    TwoDimArray dist;
    initializeDistances(dist);

    distSoFar[START_NODE] = KeyValue(START_NODE, 0);
    visited.push_back(START_NODE);
    updateDistances(START_NODE, distSoFar, dist);
    for (auto &x : dist)
    {
        for (auto y : x)
            cout << y << " ";
        cout << endl;
    }
    cout << endl;
    int source = START_NODE;
    while (visited.size() < NUMBER_OF_NODES)
    {
        int destination;
        int currentMin = INFINITY;
        for (int i = 0; i < NUMBER_OF_NODES; i++)
        {
            if (distSoFar[i].second < currentMin and !contains(visited, i))
            {
                destination = i;
                source = distSoFar[i].first;
                currentMin = distSoFar[i].second;
            }
        }
        updateDistances(destination, distSoFar, dist);
        visited.push_back(destination);
        resultingEdges.push_back(KeyValue(source, destination));
    }
    for (auto &x : resultingEdges)
        cout << x.first << "-" << x.second << endl;

    return 0;
}