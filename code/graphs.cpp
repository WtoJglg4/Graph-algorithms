#include <iostream>
#include <limits.h>
#include <iomanip>
#include <set>
#include <map>
#include "graphs.h"
using namespace std;


//печать матрицы
void PrintMatrix(int** Graph, int n){
    //ищем максимальную ширину элемента таблицы
    int maxWidth = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int width = to_string(Graph[i][j]).length();
            maxWidth = max(maxWidth, width);
        }
    }

    maxWidth++;
    for(int i = 0; i < n; i++){
        //печать номеров вершин по горизонтали
        if(i == 0){
            cout << setw(maxWidth) << " ";
            for(int j = 0; j < n; j++){
                cout << setw(maxWidth) << j;
            } 
            cout << endl;
        }
        cout << setw(maxWidth) << i; //номера по вертикали
        

        for(int j = 0; j < n; j++){
            if (Graph[i][j] == INT_MAX){
                cout << setw(maxWidth) << "INF";
            } else{
                cout << setw(maxWidth) << Graph[i][j];
            }
        }
        cout << endl;
    }
}


//печать shortest или pred
void PrintTable(int arr[], int size, map<int, char> nodeNames, string tableName){
    cout << tableName << ":\n";
    for(int i = 0; i < size; i++){
        cout << nodeNames.at(i) << " ";
    }
    cout << endl;
    if (tableName == "Pred"){
        for(int i = 0; i < size; i++){
        cout << nodeNames.at(arr[i]) << " ";
        }
    } else{
        for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
        }
    }
    
    cout << endl;
}






//алгоритм Беллмана-Форда
//граф задается массивом рёбер
void BellmanFord(int** Graph, int n, int s, int shortest[], int pred[], map<int, char> nodeNames, map<char, int> nodeNamesLetters){
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Graph[i][j] != 0) m++;
        }
    }
    edge *E = new edge[m];
    m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Graph[i][j] != 0){
                E[m] = edge{i, j, Graph[i][j]};
                m++;
            }
        }
    }

    //первичная инициализация массивов
    for (int i = 0; i < n; i++){
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }
    //s - начальная вершина, считаем относительно неё
    shortest[s] = 0;
    
    //по количеству вершин
    for (int i = 0; i < n; i++){
        //по всем рёбрам
        for(int j = 0; j < m; j++){
            int u = E[j].source;
            int v = E[j].destination;
            int weight = E[j].weight;

            //релаксация
            if(shortest[u] != INT_MAX && shortest[v] > shortest[u] + weight){
                shortest[v] = shortest[u] + weight;
                pred[v] = u;
            }
        }
        cout << "Итерация " << i << endl;
        PrintTable(shortest, n, nodeNames, "Shortest");
        PrintTable(pred, n, nodeNames, "Pred");
        cout << endl;
    }
    
    //если можно сделать n+1-ю итерацию, значит есть отрицательный цикл
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

    cout << "Введите конечную вершину: ";
    char letter;
    cin >> letter;
    // int path[n - 1];
    int path[n];
    int nodeNum = nodeNamesLetters.at(letter);
    path[0] = nodeNum;
    int i = 1;
    while (true) {
        if (pred[nodeNum] == -1){
            break;
        }
        path[i] = pred[nodeNum];
        nodeNum = pred[nodeNum];
        i++;
    }
    for (i = i-1;i> -1; i--){
        cout << nodeNames.at(path[i]);
        if (i != 0){
            cout << "->";
        }
    }

}


//алгоритм Флойда-Уоршалла
void FloydWarshall(int** Graph, int size, int** shortest, int** pred){
    //первичная инициализация массивов
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
    for(int x = 0; x < size; x++){  //перебираем x
        for(int u = 0; u < size; u++){
            for(int v = 0; v < size; v++){
                //релаксация
                if(shortest[u][v] > shortest[u][x] + shortest[x][v] && shortest[u][x] != INT_MAX && shortest[x][v] != INT_MAX){
                    shortest[u][v] = shortest[u][x] + shortest[x][v];
                    pred[u][v] = x;
                }
            }
        }
    }
}

//очередь с приоритетом для алгоритма Примы
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
    cout << "\nPriority: ";
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

//проверка на пустоту
bool PQEmpty(){
    return !front;
}

//обновление приоритета в очереди
void PQUpdatePriority(int value, int newPriority){
    PQueue *curr = front;
    while(curr){
        if(curr->data == value){
            curr->priority = newPriority;
            return;
        }
        curr = curr->next;
    }
}


//алгоритм Прима
void Prim(int** Graph, int size, int** tree){
    int* distToTree = new int[size];    //дистанция до остовного дерева
    int* predInTree = new int[size];    //элемент, к которому присоединен элемент в остовном дереве

    //первичная инициализация массивов        
    for(int i = 0; i < size; i++){
        distToTree[i] = INT_MAX;
        predInTree[i] = -1;
    }

    set<int> U;         //множество вершин остовного дерева
    distToTree[0] = 0;  //0-я вершина - начальная, ее приоритет 0(меньше всех, чтобы она вышла с очереди первой)

    set<int> V;         //изначальное множество всех вершин графа         
    for(int i = 0; i< size; i++) V.insert(i);

    PQueue Q;           //приоритетная очередь
    for(int v: V) PQInsert(v, distToTree[v]);   //помещаем все вершины в очередь, передавая приоритеты
    PQPrint();

    while(!PQEmpty()) {     //пока очередь не пустая
        int v = PQDelete(); //получаем элемент 
        V.erase(v);         //удалить из множества вершин графа
        U.insert(v);        //добавить ее во множество вершин оставного дерева
        cout << "v: " << v << endl;
        
        //по всем смежным вершинам
        cout << "u: ";
        for(int u = 0; u < size; u++){
            cout << u << " " << V.count(u) << " ";
            //если вершина еще не в дереве, имеет связь с v, можно обновить ее приоритет
            if(V.count(u) == 1 && Graph[v][u] != 0 && distToTree[u] > Graph[v][u]){
                predInTree[u] = v;              //установить v - ближайшей к u в дереве
                distToTree[u] = Graph[v][u];    //обновить дистанцию = приоритет 

                //обновить приоритет в очереди
                PQUpdatePriority(u, distToTree[u]);
            }
        }
        //промежуточный вывод
        cout << endl;
        PQPrint();
        cout << "distToTree: ";
        for (int i = 0; i < size; i++) {
            cout << distToTree[i] << " ";
        } cout << endl;
    }

    //обнулить дерево
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tree[i][j] = 0;
        }   
    }

    //заполнить дерево согласно полученным distToTree, predInTree
    for (int i = 1; i < size; i++) {
        int u = i, v = predInTree[i];
        tree[u][v] = distToTree[u]; //зеркалим, т.к. остовное дерево - неориентированный граф
        tree[v][u] = distToTree[u];
    }
}


//алгоритм Краскала
void Kruskal(int** Graph, int size, int** tree){
    //очистить дерево
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            tree[i][j] = 0;
        }
    }

    int egdeCount = 0;  //количество рёбер
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            tree[i][j] = 0;
            if(Graph[i][j]  != 0) egdeCount++;
        }
    }
    egdeCount /= 2;

    //создадим массив ребер графа(уникальных)
    edge* edgeArr = new edge[egdeCount];
    int edgeIndex = 0;
    //идем только по правому верхнему треугольнику матрицы, т.к. граф неориентированный
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
            if(Graph[i][j] != 0){
                edgeArr[edgeIndex] = edge{i, j, Graph[i][j]};
                edgeIndex++;    
            }
        }
    }  

    //отсортируем пузырьком по весу)) за nlogn лень))
    for(int i = 0; i < edgeIndex -1; i++){
        for(int j = i + 1; j < edgeIndex; j++){
            if(edgeArr[i].weight > edgeArr[j].weight){
                swap(edgeArr[i], edgeArr[j]);
            }
        }   
    }
    //промежуточная печать
    cout << "Edges:\n";
    for(int i = 0; i < edgeIndex; i++){
        cout << edgeArr[i].source << " " << edgeArr[i].destination << " " << edgeArr[i].weight << endl;
    }
    cout << endl;
    

    set<set<int>> subsetNodes;  //множество, состоящее из подмножеств вершин графа
    //изначально инициализируем одиночными изолированными вершинами
    for(int i = 0; i < size; i++){
        set<int> subset = {i};  //множество из одной изолированной вершины
        subsetNodes.insert(subset);
    }
    
    //идем по отсортированному массиву рёбер
    for(int i = 0; i < edgeIndex; i++){
        set<int> Uset, Vset;    //множества, в которые запишем подмножества, содержащие вершину u и v соответственно

        for(set<int> subset: subsetNodes){  //идем по всем подмножествам вершин
            if(subset.count(edgeArr[i].source) == 1){
                Uset = subset;  //записали подмножества, содержащее edge.source = u
            }
            if(subset.count(edgeArr[i].destination) == 1){
                Vset = subset;  //записали подмножества, содержащее edge.destination = v
            }
        }
        if(Uset != Vset){   //если это разные подмножества
            subsetNodes.erase(Uset);    //удалим их из общего множества subsetNodes
            subsetNodes.erase(Vset);
            set<int> merge;
            for(int el: Uset) merge.insert(el); //смёрджим их в одно общее подмножество вершин
            for(int el: Vset) merge.insert(el);
            subsetNodes.insert(merge);          //поместим обратно в subsetNodes

            int u = edgeArr[i].source, v = edgeArr[i].destination, w = edgeArr[i].weight;
            tree[u][v] = w; //запишем соответствующие значения в остовное дерево
            tree[v][u] = w;
        }
    }

    //вывод полученных подмножеств для наглядности
    for(set<int> subset: subsetNodes){
        for(int el: subset) cout << el << " "; 
        cout << endl;
    }
}
