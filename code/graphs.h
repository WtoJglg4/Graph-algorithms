#ifndef GRAPHS_H
#define GRAPHS_H
using namespace std;

//ребро графа
struct edge{
    //вершина начало, вершина конец, вес ребра
    int source, destination, weight;
};

//вспомогательные функции печати
void PrintTable(int arr[], int size, map<int, char> nodeNames, string tableName);
void PrintMatrix(int** Graph, int n);


//исследуемые алгоритмы
void BellmanFord(edge E[], int n, int m, int s, int shortest[], int pred[]);
void FloydWarshall(int** Graph, int size, int** shortest, int** pred);
void Prim(int** Graph, int size, int** tree);
void Kruskal(int** Graph, int size, int** tree);


//методы приоритетной очереди
void PQInsert(int a, int prio);
void PQPrint();
int PQDelete();
bool PQEmpty();
void PQUpdatePriority(int u, int key);

#endif