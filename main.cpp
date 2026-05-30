#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

class Graph {
    static const int MAX = 20;
    char labels[MAX][50];
    int adj[MAX][MAX];
    int count;

    int findVertex(char label[]) {
        for (int i = 0; i < count; i++)
            if (strcmp(labels[i], label) == 0)
                return i;
        return -1;
    }

public:
    Graph() {
        count = 0;
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                adj[i][j] = 0;
    }

    void addVertex(char label[]) {
        if (count < MAX)
            strcpy(labels[count++], label);
    }

    void addEdge(char from[], char to[], int w) {
        int a = findVertex(from);
        int b = findVertex(to);
        if (a != -1 && b != -1)
            adj[a][b] = w;
    }
