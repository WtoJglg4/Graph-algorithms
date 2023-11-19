#ifndef GRAPHS_H
#define GRAPHS_H
using namespace std;


struct edge{
    int source, destination, weight;
};


void PrintMatrix(int** Graph, int n);


void BellmanFord(edge E[], int n, int m, int s, int shortest[], int pred[]);
void FloydWarshall(int** Graph, int size, int** shortest, int** pred);
void Prim(int** Graph, int size, int** tree);
void Kruskal(int** Graph, int size, int** tree);


void PQInsert(int a, int prio);
void PQPrint();
int PQDelete();
bool PQEmpty();
void PQUpdatePriority(int u, int key);


#endif