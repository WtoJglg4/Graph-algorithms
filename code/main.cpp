#include <iostream>
#include <map>
#include <set>
#include <limits.h>
#include "bellmanFord.h"
using namespace std;

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

//g++ main.cpp bellmanFord.cpp -o output
int main(){

    //граф без отрицательных циклов
    // const int n = 5, m = 10;    //кол-во вершин и ребер
    // edge Edges[] =     {edge{0, 1, 6}, edge{0, 2, 7}, edge{1, 3, 6}, edge{1, 2, 8}, edge{1, 4, -4}, 
    //                 edge{3, 1, -2}, edge{2, 3, -3}, edge{2, 4, 9}, edge{4, 3, 7}, edge{4, 0, 2}};
    // const map<int, char> nodeNames = { {0, 'S'}, {1, 'T'}, {2, 'Y'}, {3, 'X'}, {4, 'Z'}, {-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'S', 0}, {'T', 1}, {'Y', 2}, {'X', 3}, {'Z', 4}, {'H', -1} };

    //граф с отрицательными циклами 
    // const int n = 4, m = 5;    //кол-во вершин и ребер
    // edge Edges[] =     {edge{0, 1, 3}, edge{0, 2, 6}, edge{1, 2, 5}, edge{2, 3, 2}, edge{3, 1, -10}};
    // const map<int, char> nodeNames = { {0, 'S'}, {1, 'A'}, {2, 'B'}, {3, 'C'}, {-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'S', 0}, {'A', 1}, {'B', 2}, {'C', 3}, {'H', -1} };

    //граф без отрицательных циклов(есть пикча)
    const int n = 12, m = 17;    //кол-во вершин и ребер
    edge Edges[] =     {edge{0, 1, 1}, edge{1, 2, 4}, edge{2, 3, 5}, 
                        edge{4, 0, 7}, edge{5, 1, 2}, edge{6, 2, 3},
                        edge{3, 7, -3}, edge{5, 4, 5}, edge{5, 6, -2},
                        edge{6, 7, 7}, edge{8, 4, -6}, edge{5, 9, 4},
                        edge{6, 10, 6}, edge{7, 11, 4}, edge{9, 8, 3},
                        edge{9, 10, 1}, edge{10, 11, 2}};
    const map<int, char> nodeNames = {  {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
                                        {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, 
                                        {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {-1, 'H'} };
    const map<char, int> nodeNamesLetters = {   {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
                                                {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
                                                {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'H', -1}};


    int shortest[n];
    int pred[n];
    int s;
    cout << "Введите начальную вершину: ";
    cin >> s;
    BellmanFord(Edges, n, m, s, shortest, pred);
    cout << endl; 
    PrintTable(shortest, n, nodeNames, "Shortest");
    PrintTable(pred, n, nodeNames, "Pred");
    
    int a;
    cin >> a;
}