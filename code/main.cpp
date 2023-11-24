#include <iostream>
#include <map>
#include <set>
#include <limits.h>
#include "graphs.h"
using namespace std;

//g++ main.cpp graphs.cpp -o output
int main(){

    //граф без отрицательных циклов(из лекции)
    // const int n = 5, m = 10;    //кол-во вершин и ребер
    // edge Edges[] =     {edge{0, 1, 6}, edge{0, 2, 7}, edge{1, 3, 6}, edge{1, 2, 8}, edge{1, 4, -4}, 
    //                 edge{3, 1, -2}, edge{2, 3, -3}, edge{2, 4, 9}, edge{4, 3, 7}, edge{4, 0, 2}};
    // const map<int, char> nodeNames = { {0, 'S'}, {1, 'T'}, {2, 'Y'}, {3, 'X'}, {4, 'Z'}, {-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'S', 0}, {'T', 1}, {'Y', 2}, {'X', 3}, {'Z', 4}, {'H', -1} };

    //граф с отрицательными циклами(тоже из лекции)
    // const int n = 4, m = 5;    //кол-во вершин и ребер
    // edge Edges[] =     {edge{0, 1, 3}, edge{0, 2, 6}, edge{1, 2, 5}, edge{2, 3, 2}, edge{3, 1, -10}};
    // const map<int, char> nodeNames = { {0, 'S'}, {1, 'A'}, {2, 'B'}, {3, 'C'}, {-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'S', 0}, {'A', 1}, {'B', 2}, {'C', 3}, {'H', -1} };

    //граф без отрицательных циклов(bellmanFord picture)
    // const int n = 12, m = 17;    //кол-во вершин и ребер
    // edge Edges[] =     {edge{0, 1, 1}, edge{1, 2, 4}, edge{2, 3, 5}, 
    //                     edge{4, 0, 7}, edge{5, 1, 2}, edge{6, 2, 3},
    //                     edge{3, 7, -3}, edge{5, 4, 5}, edge{5, 6, -2},
    //                     edge{6, 7, 7}, edge{8, 4, -6}, edge{5, 9, 4},
    //                     edge{6, 10, 6}, edge{7, 11, 4}, edge{9, 8, 3},
    //                     edge{9, 10, 1}, edge{10, 11, 2}};
    
    // const map<int, char> nodeNames = {  {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
    //                                     {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, 
    //                                     {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {-1, 'H'} };
    // const map<char, int> nodeNamesLetters = {   {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
    //                                             {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
    //                                             {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'H', -1}};

    //мой граф(dijkstra picture) 
    // const map<int, char> nodeNames = { {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'},{-1, 'H'} };
    // const map<char, int> nodeNamesLetters = { {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', -1} };
    const int fwSize = 7;
    int Graph[fwSize][fwSize] = {   {0, 2, 1, 0, 0, 6, 0},
                                    {0, 0, 0, 0, 0, 7, 0},
                                    {0, 0, 0, 5, 2, 0, 0},
                                    {0, 0, 0, 0, 1, 2, 0},
                                    {0, 0, 0, 2, 0, 1, 4},
                                    {0, 0, 0, 0, 0, 0, 1},
                                    {0, 0, 0, 0, 0, 0, 1}};
    const map<int, char> nodeNames = { {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'},{-1, 'H'} };
    const map<char, int> nodeNamesLetters = { {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', -1} };
    // edge Edges[] =     {edge{0, 1, 2}, edge{0, 2, 1}, edge{0, 5, 6}, 
    //                     edge{1, 5, 7}, edge{2, 3, 5}, edge{2, 4, 2},
    //                     edge{3, 4, 1}, edge{3, 5, 2}, edge{4, 3, 2},
    //                     edge{4, 5, 1}, edge{4, 6, 4}, edge{5, 6, 1}};

    int* graphMatr[fwSize];
    for(int i = 0; i < fwSize; i++){
        graphMatr[i] = Graph[i];
    }

    int shortest[fwSize];
    int pred[fwSize];
    int s;
    char sLetter;
    cout << "Bellman-Ford\n";
    cout << "Введите начальную вершину: ";
    // cin >> s;
    cin >> sLetter;
    s = nodeNamesLetters.at(sLetter);
    BellmanFord(graphMatr, fwSize, s, shortest, pred, nodeNames, nodeNamesLetters);
    cout << endl; 
    PrintTable(shortest, fwSize, nodeNames, "Shortest");
    PrintTable(pred, fwSize, nodeNames, "Pred");
    cout << endl;



    //FloydWarshall
    //(bellmanFord picture graph)
    // const int fwSize = 12;
    // int Graph[fwSize][fwSize] = {
    // //   0  1  2  3  4  5  6  7  8  9  10 11
    //     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0},
    //     {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 2, 0, 0, 5, 0, -2, 0, 0, 4, 0, 0},
    //     {0, 0, 3, 0, 0, 0, 0, 7, 0, 0, 6, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    //     {0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    // };

    //floydWarshall small test picture
    // const int fwSize = 4;
    // int Graph[fwSize][fwSize] = {
    // //   0  1  2  3
    //     {0, 5, 0, 0},
    //     {0, 0, 5, 3},
    //     {-3, 0, 0, 0},
    //     {2, 0, -5, 0},
    // };

    //itmo wiki graph
    // const int fwSize = 5;
    // int Graph[fwSize][fwSize] = {
    // //   0  1  2  3  4
    //     {0, 3, 4, 0, 1},
    //     {3, 0, 5, 0, 0},
    //     {4, 5, 0, 2, 6},
    //     {0, 0, 2, 0, 7},
    //     {1, 0, 6, 7, 0},
    // };

    //(bellmanFord picture graph)
    //неориентированный
    // int Graph[fwSize][fwSize] = {
    // //   0  1  2  3  4  5  6  7  8  9  10 11
    //     {0, 1, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 4, 0, 0, 2, 0, 0, 0, 0, 0, 0},
    //     {0, 4, 0, 5, 0, 0, 3, 0, 0, 0, 0, 0},
    //     {0, 0, 5, 0, 0, 0, 0,-3, 0, 0, 0, 0},
    //     {7, 0, 0, 0, 0, 5, 0, 0,-6, 0, 0, 0},
    //     {0, 2, 0, 0, 5, 0,-2, 0, 0, 4, 0, 0},
    //     {0, 0, 3, 0, 0,-2, 0, 7, 0, 0, 6, 0},
    //     {0, 0, 0,-3, 0, 0, 7, 0, 0, 0, 0, 4},
    //     {0, 0, 0, 0,-6, 0, 0, 0, 0, 3, 0, 0},
    //     {0, 0, 0, 0, 0, 4, 0, 0, 3, 0, 1, 0},
    //     {0, 0, 0, 0, 0, 0, 6, 0, 0, 1, 0, 2},
    //     {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2, 0}
    // };

   
    int* shortestMatr[fwSize];
    int* predMatr[fwSize];
    for (int i = 0; i < fwSize; i++) {
        shortestMatr[i] = new int[fwSize];
        predMatr[i] = new int[fwSize];
        graphMatr[i] = Graph[i];
    }
    cout << "FloydWarshall\n";
    PrintMatrix(graphMatr, fwSize);
    FloydWarshall(graphMatr, fwSize, shortestMatr, predMatr);
    cout << "FW end\nShortest:\n";
    PrintMatrix(shortestMatr, fwSize);
    cout << "Pred:\n";
    PrintMatrix(predMatr, fwSize);
    cout << endl;


    //Prim
    //сделаем граф неориентированным
    for(int i = 0; i < fwSize; i++){
        for(int j = 0; j < fwSize; j++){
            if(Graph[i][j] != 0) Graph[j][i] = Graph[i][j];
        }
    }
    for(int i = 0; i < fwSize; i++){
        graphMatr[i] = Graph[i];
    }

    int* tree[fwSize];
    for (int i = 0; i < fwSize; i++) {
        tree[i] = new int[fwSize];
    }
    cout << "Prim\n";
    PrintMatrix(graphMatr, fwSize);
    Prim(graphMatr, fwSize, tree);
    cout << "Tree: \n";
    PrintMatrix(tree, fwSize);

    //Kruskal
    cout << "\nKruskal\n";
    PrintMatrix(graphMatr, fwSize);
    Kruskal(graphMatr, fwSize, tree);
    cout << "Tree: \n";
    PrintMatrix(tree, fwSize);

    int a;
    cin >> a;
}