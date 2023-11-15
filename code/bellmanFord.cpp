#include <iostream>
#include <limits.h>
#include "bellmanFord.h"
using namespace std;



void BellmanFord(edge E[], int n, int m, int s, int shortest[], int pred[]){
    for (int i = 0; i < n; i++){
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }
    shortest[s] = 0;
    
    for (int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int u = E[j].source;
            int v = E[j].destination;
            int weight = E[j].weight;

            if(shortest[u] != INT_MAX && shortest[v] > shortest[u] + weight){
                shortest[v] = shortest[u] + weight;
                pred[v] = u;
            }
        }
    }
    
    bool negativeCycles = false;
    for(int j = 0; j < m; j++){
        int u = E[j].source;
        int v = E[j].destination;
        int weight = E[j].weight;
        if (shortest[v] > shortest[u] + weight){
            negativeCycles = true;
            break;
        }
    }

    if(negativeCycles){
        cout << "Граф содержит отрицательные циклы\n";
    } else{
        cout << "Граф не содержит отрицательные циклы\n";
    }
}