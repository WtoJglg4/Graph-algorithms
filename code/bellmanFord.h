#ifndef BELLMANFORD_H
#define BELLMANFORD_H
using namespace std;

struct edge{
    int source, destination, weight;
};

void BellmanFord(edge E[], int n, int m, int s, int shortest[], int pred[]);


#endif