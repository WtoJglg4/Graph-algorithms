#include <iostream>
#include <climits>
#include <map>
using namespace std;

//экземпляр элемента очереди с приоритетом
struct PQueue{
    int data; //значение элемента
    PQueue *next; //указатель на следующий элемент
};

int count = 0;
PQueue *front, *rear; //начало, конец

//добавление элемента(неприоритетное)
void PQInsert(int a){
    PQueue *q = new PQueue;
    if (count == 0){
        front = q;
    } else{
        rear->next = q;
    }
    q->data = a;
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
}

//удаление элемента(приоритетное)
int PQDelete(int shortest[]) {
    //пустая очередь
    if (!front) {
        cerr << "queue is empty\n";
        exit(1);
    } else {
        //непустая

        //поиск элемента, с минимальным значением shortest
        int minShortest = shortest[front->data];
        int minKey = front->data;
        PQueue *curr = front->next;
        PQueue *prev = front;

        while (curr) {
            if (shortest[curr->data] < minShortest) {
                minShortest = shortest[curr->data];
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

//вернуть последний элемент
int PQFront(){
    int temp;
    if(!front){
        cerr << "PQueue is empty\n";
        exit(1);
    } 
    return front->data;    
}

//очистка очереди
void PQClear(){
    PQueue *q;
    while(front){
        q = front->next;
        delete front;
        front = q;
        count--;
    }
    delete q;
}

bool PQEmpty(){
    return !front;
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

struct edge{
    int source, destination, weight;
};

int main(){    
    // const int n = 7, m = 7;
    //это граф из лекции
    //H = head
    //ключи - численные номера вершин в shortest, pred. значения - соответствующие буквенные
    // const map<int, char> nodeNames = { {0, 'S'}, {1, 'T'}, {2, 'Y'}, {3, 'X'}, {4, 'Z'}, {-1, 'H'} };
    // int Graph[5][10] = {    {0, 6, 4, 0, 0},
    //                         {0, 0, 2, 3, 0},
    //                         {0, 1, 0, 9, 3},
    //                         {0, 0, 0, 0, 4},
    //                         {7, 0, 0, 5, 0}};

    //мой граф 
    // const map<int, char> nodeNames = { {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'},{-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', -1} };
    // int Graph[n][m] = {    {0, 2, 1, 0, 0, 6, 0},
    //                         {0, 0, 0, 0, 0, 7, 0},
    //                         {0, 0, 0, 5, 2, 0, 0},
    //                         {0, 0, 0, 0, 1, 2, 0},
    //                         {0, 0, 0, 2, 0, 1, 4},
    //                         {0, 0, 0, 0, 0, 0, 1},
    //                         {0, 0, 0, 0, 0, 0, 1}};

    const int n = 6, m = 6;
    // const int n = 6, m = 8;
    // edge Edges[] =     {edge{0, 1, 6}, edge{0, 2, 8}, edge{0, 3, 18}, edge{1, 4, 11}, edge{2, 3, 9}, edge{4, 5, 3}, edge{5, 2, 7}, edge{5, 3, 4}};
    const map<int, char> nodeNames = { {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {-1, 'H'} };
    const map<char, int> nodeNamesLetters = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'H', -1} };
    int Graph[n][m] = {    {0, 6, 8, 18, 0, 0},
                            {0, 0, 0, 0, 11, 0},
                            {0, 0, 0, 9, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 3},
                            {0, 0, 7, 4, 0, 0}};

    int shortest[n]; //массив кратчайших путей до каждой из вершин
    int pred[n]; //предыдущая вершина на найденном кратчайшем пути для каждой из вершин
    shortest[0] = 0; //для head
    pred[0] = -1; //тоже для head
    for (int i = 1; i < n; i++){
        shortest[i] = INT_MAX; //для всех остальных
        pred[i] = -1;
    }  

    PQueue *q = new PQueue; //очередь с приоритетом вершин
    front = q; //первый элемент
    rear = q; //последний

    //все узлы поместить в очередь
    for (int i = 0; i < n; i++){
        PQInsert(i);
    }
    // PQPrint();

    //пока не пустая очередь
    while(!PQEmpty()){
        //удалить и вернуть элемент с наибольшим приоритетом
        //замечание: чем МЕНЬШЕ значение shortest[i], тем больше приоритет вершины
        int u = PQDelete(shortest);
        
        //по смежным с вершинам взятой из очереди
        for(int i = 0; i < size(Graph[u]); i++){
            //если есть ребро
            if (Graph[u][i] > 0){
                //смежная вершина v и вес ребра (u, v)
                int v = i, weight = Graph[u][i]; 

                //Relax
                //путь (u, v) короче, чем записанный ранее в sortest -> обновить shortest и pred
                if (shortest[u] + weight < shortest[v]){
                    shortest[v] = shortest[u] + weight;
                    pred[v] = u;
                }
            }
        }
    }

    //форматированный вывод shortest и pred
    PrintTable(shortest, size(shortest), nodeNames, "Shortest");
    PrintTable(pred, size(pred), nodeNames, "Pred");

    char letter;
    cin >> letter;
    int path[n - 1];
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