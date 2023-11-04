#include <iostream>
using namespace std;

struct PQueue{
    int data;
    PQueue *next;
};

int count = 0;
PQueue *front, *rear;
void Insert(int a){
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
    cout << "\nQueue: ";
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


int main(){
    PQueue *q;
    front = q;
    rear = q;
    Insert(0);
    Insert(1);
    Insert(4);
    Insert(3);
    Insert(2);
    int shortest[] = {0, 5, 2, 1, 4};
    cout << PQEmpty();
    PQPrint();
    PQClear();
    PQPrint();
    cout << PQEmpty();
}