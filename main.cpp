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

    void removeEdge(char from[], char to[]) {
        int a = findVertex(from);
        int b = findVertex(to);
        if (a != -1 && b != -1)
            adj[a][b] = 0;
    }

    void removeVertex(char label[]) {
        int v = findVertex(label);
        if (v == -1) return;

        for (int i = v; i < count - 1; i++)
            strcpy(labels[i], labels[i + 1]);

        for (int i = v; i < count - 1; i++)
            for (int j = 0; j < count; j++)
                adj[i][j] = adj[i + 1][j];

        for (int j = v; j < count - 1; j++)
            for (int i = 0; i < count; i++)
                adj[i][j] = adj[i][j + 1];

        count--;
    }

    void printTable() {
        cout << "  ";
        for (int i = 0; i < count; i++)
            cout << labels[i] << " ";
        cout << endl;

        for (int i = 0; i < count; i++) {
            cout << labels[i] << " ";
            for (int j = 0; j < count; j++)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }
