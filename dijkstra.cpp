#include <iostream>
#include <climits>
#include <map>
using namespace std;

struct PQueue{
    int data;
    PQueue *next;
};

int count = 0;
PQueue *front, *rear;

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

void PQPrint(){
    PQueue *curr = front;
    cout << "Queue: ";
    while(curr){
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int PQDelete(int shortest[]) {
    if (!front) {
        cerr << "queue is empty\n";
        exit(1);
    } else {
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

int main(){    
    //это граф из лекции
    //H = head
    const map<int, char> nodeNames = { {0, 'S'}, {1, 'T'}, {2, 'Y'}, {3, 'X'}, {4, 'C'}, {-1, 'H'} };
    int Graph[5][10] = {    {0, 6, 4, 0, 0},
                            {0, 0, 2, 3, 0},
                            {0, 1, 0, 9, 3},
                            {0, 0, 0, 0, 4},
                            {7, 0, 0, 5, 0}};

    //это мой граф сам придумал
    // const map<int, char> nodeNames = { {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {-1, 'H'} };
    // int Graph[5][10] = {    {0, 3, 10, 0, 4},
    //                         {0, 0, 2, 0, 3},
    //                         {0, 0, 0, 0, 0},
    //                         {0, 0, 1, 0, 0},
    //                         {0, 0, 0, 5, 0}};

    int shortest[5];
    int pred[5];
    shortest[0] = 0;
    pred[0] = -1;
    for (int i = 1; i <= 4; i++){
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }  

    PQueue *q;
    front = q;
    rear = q;
    for (int i = 0; i <= 4; i++){
        PQInsert(i);
    }
    // PQPrint();
    while(!PQEmpty()){
        int u = PQDelete(shortest);
        // cout << u << endl;
        // PQPrint();
        
        for(int i = 0; i < size(Graph[u]); i++){
            if (Graph[u][i] > 0){
                int v = i, weight = Graph[u][i]; 
                if (shortest[u] + weight < shortest[v]){
                    shortest[v] = shortest[u] + weight;
                    pred[v] = u;
                }
            }
        }
    }
    PrintTable(shortest, size(shortest), nodeNames, "Shortest");
    PrintTable(pred, size(pred), nodeNames, "Pred");
}