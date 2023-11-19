#include <iostream>
#include <limits.h>
#include <iomanip>
#include <set>
#include "graphs.h"
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

void FloydWarshall(int** Graph, int size, int** shortest, int** pred){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            shortest[i][j] = INT_MAX;
            pred[i][j] = -1;
        }
    }

    //изначально инициализируем матрицу
    for(int u = 0; u < size; u++){
        for(int v = 0; v < size; v++){
            if (Graph[u][v] != 0){
                shortest[u][v] = Graph[u][v];
                pred[u][v] = u;
            }
                        
            if(u == v){
                shortest[u][v] = 0;
                pred[u][v] = u;
            }
        }
    }
    cout << "FW init:\nshortest\n";
    PrintMatrix(shortest, size);
    cout << "pred:\n";
    PrintMatrix(pred, size);
    cout << endl;

    //идем u -> x -> v, обновляя кратчайшие пути
    //в pred записываем последнюю пройденную вершину до v
    for(int x = 0; x < size; x++){
        for(int u = 0; u < size; u++){
            for(int v = 0; v < size; v++){
                if(shortest[u][v] > shortest[u][x] + shortest[x][v] && shortest[u][x] != INT_MAX && shortest[x][v] != INT_MAX){
                    shortest[u][v] = shortest[u][x] + shortest[x][v];
                    pred[u][v] = x;
                }
            }
        }
        // cout << "shortest:\n";
        // PrintMatrix(shortest, size);
        // cout << "pred:\n";
        // PrintMatrix(pred, size);
        // cout << endl;
    }
}



void PrintMatrix(int** Graph, int n){
    int maxWidth = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int width = to_string(Graph[i][j]).length();
            maxWidth = max(maxWidth, width);
        }
    }

    for(int i = 0; i < n; i++){
        // cout << (*Graph)[i];
        for(int j = 0; j < n; j++){
            if (Graph[i][j] == INT_MAX){
                cout << setw(maxWidth) << "INF ";
            } else{
                cout << setw(maxWidth) << Graph[i][j] << " ";
            }
        }
        cout << endl;
    }
}







//экземпляр элемента очереди с приоритетом
struct PQueue{
    int data; //значение элемента
    int priority; //приоритет
    PQueue *next; //указатель на следующий элемент
};

int count = 0;
PQueue *front, *rear; //начало, конец

//добавление элемента(неприоритетное)
void PQInsert(int a, int prio){
    PQueue *q = new PQueue;
    if (count == 0){
        front = q;
    } else{
        rear->next = q;
    }
    q->data = a;
    q->priority = prio;
    rear = q;
    rear->next = NULL;
    count++;
}

//печать всей очереди
void PQPrint(){
    PQueue *curr = front;
    cout << "Queue: ";
    while(curr){
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
    curr = front;
    while(curr){
        cout << curr->priority << " ";
        curr = curr->next;
    }
    cout << endl;
}

//удаление элемента(приоритетное)
int PQDelete(){
    //пустая очередь
    if (!front) {
        cerr << "queue is empty\n";
        exit(1);
    } else {
        //непустая

        //поиск элемента, с минимальным значением priority
        int minPrior = front->priority;
        int minKey = front->data;
        PQueue *curr = front->next;
        PQueue *prev = front;

        while (curr) {
            if (curr->priority < minPrior) {
                minPrior = curr->priority;
                minKey = curr->data;
            }
            prev = curr;
            curr = curr->next;
        }

        if (front->data == minKey) {
            curr = front->next;
            delete front;
            front = curr;
        } else {
            prev = front;
            curr = front->next;
            while (curr) {
                if (curr->data == minKey) {
                    prev->next = curr->next;
                    delete curr;
                    break;
                }

                prev = curr;
                curr = curr->next;
            }
        }

        count--;
        return minKey;
    }
}

bool PQEmpty(){
    return !front;
}

void PQUpdatePriority(int u, int key){
    PQueue *curr = front;
    while(curr){
        if(curr->data == u){
            curr->priority = key;
            return;
        }
        curr = curr->next;
    }
}


//Prima
void Prim(int** Graph, int size, int** tree){
    int* distToTree = new int[size];
    int* predInTree = new int[size];
    for(int i = 0; i < size; i++){
        distToTree[i] = INT_MAX;
        predInTree[i] = -1;
    }

    set<int> U = {};
    distToTree[0] = 0;

    set<int> V;    
    for(int i = 0; i< size; i++) V.insert(i);

    PQueue Q;
    for(int v: V) PQInsert(v, distToTree[v]);
    PQPrint();

    while(!PQEmpty()) {
        int v = PQDelete();
        V.erase(v);
        U.insert(v);
        cout << "v: " << v << endl;
        // PQPrint();
        // cout << "distToTree:\n";
        // for (int i = 0; i < size; i++) {
        //     cout << distToTree[i] << " ";
        // } cout << endl;

        //по всем смежным вершинам
        cout << "u: ";
        for(int u = 0; u < size; u++){
            cout << u << " " << V.count(u) << " ";
            if(V.count(u) == 1 && Graph[v][u] != 0 && distToTree[u] > Graph[v][u]){
                predInTree[u] = v;
                distToTree[u] = Graph[v][u];

                //обновить приоритет в очереди
                PQUpdatePriority(u, distToTree[u]);
            }
        }
        cout << endl;
        PQPrint();
        cout << "distToTree:\n";
        for (int i = 0; i < size; i++) {
            cout << distToTree[i] << " ";
        } cout << endl;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tree[i][j] = 0;
        }   
    }
    for (int i = 1; i < size; i++) {
        int u = i, v = predInTree[i];
        tree[u][v] = distToTree[u];
        tree[v][u] = distToTree[u];
    }
    cout << "Tree: \n";
    PrintMatrix(tree, size);

    // cout << "distToTree:\n";
    // for (int i = 0; i < size; i++) {
    //     cout << distToTree[i] << " ";
    // }
    // cout << "\npredInTree:\n";
    // for (int i = 0; i < size; i++) {
    //     cout << predInTree[i] << " ";
    // }
}




























// void BellmanFordMatrix(int** Graph, int n, int m, int s, int shortest[], int pred[]){
//     for (int i = 0; i < n; i++){
//         shortest[i] = INT_MAX;
//         pred[i] = -1;
//     }
//     shortest[s] = 0;
    
//     for (int k = 0; k < n; k++){
//         for(int u = 0; u < n; u++){
//             for(int v = 0; v < n; v++){
//                 int weight = Graph[u][v];
//                 // int weight = (*Graph + u)[v];
//                 if(weight != 0){
//                     if(shortest[u] != INT_MAX && shortest[v] > shortest[u] + weight){
//                         shortest[v] = shortest[u] + weight;
//                         pred[v] = u;
//                     }
//                 }
//             }   
//         }
//     }
    
//     bool negativeCycles = false;
//     for(int u = 0; u < n; u++){
//         for(int v = 0; v < n; v++){
//             int weight = Graph[u][v];
//             if(weight != 0 && shortest[u] != INT_MAX && shortest[v] > shortest[u] + weight){
//                 negativeCycles = true;
//                 break;
//             }
//         }   
//         if(negativeCycles) break;       
//     }

//     if(negativeCycles){
//         cout << "Граф содержит отрицательные циклы\n";
//     } else{
//         cout << "Граф не содержит отрицательные циклы\n";
//     }
// }