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

    void shortestPath(char startL[], char endL[]) {
        int start = findVertex(startL);
        int end = findVertex(endL);

        if (start == -1 || end == -1) return;

        int dist[MAX], prev[MAX];
        bool visited[MAX];

        for (int i = 0; i < count; i++) {
            dist[i] = INT_MAX;
            prev[i] = -1;
            visited[i] = false;
        }

        dist[start] = 0;

        for (int i = 0; i < count; i++) {
            int cur = -1, min = INT_MAX;

            for (int j = 0; j < count; j++)
                if (!visited[j] && dist[j] < min) {
                    min = dist[j];
                    cur = j;
                }

            if (cur == -1) break;

            visited[cur] = true;

            for (int j = 0; j < count; j++)
                if (adj[cur][j] > 0 &&
                    dist[cur] != INT_MAX &&
                    dist[cur] + adj[cur][j] < dist[j]) {
                    dist[j] = dist[cur] + adj[cur][j];
                    prev[j] = cur;
                }
        }

        if (dist[end] == INT_MAX) {
            cout << "No path\n";
            return;
        }

        int path[MAX], size = 0;

        for (int v = end; v != -1; v = prev[v])
            path[size++] = v;

        for (int i = size - 1; i >= 0; i--) {
            cout << labels[path[i]];
            if (i) cout << " -> ";
        }

        cout << "\nTotal: " << dist[end] << endl;
    }
};

int main() {
    Graph g;
    int choice, weight;
    char a[50], b[50];

    while (true) {
        cout << "\n1 Add Vertex";
        cout << "\n2 Add Edge";
        cout << "\n3 Remove Vertex";
        cout << "\n4 Remove Edge";
        cout << "\n5 Shortest Path";
        cout << "\n6 Print";
        cout << "\n7 Quit";
        cout << "\nChoice: ";

        cin >> choice;

        if (choice == 1) {
            cin >> a;
            g.addVertex(a);
        }
        else if (choice == 2) {
            cin >> a >> b >> weight;
            g.addEdge(a, b, weight);
        }
        else if (choice == 3) {
            cin >> a;
            g.removeVertex(a);
        }
        else if (choice == 4) {
            cin >> a >> b;
            g.removeEdge(a, b);
        }
        else if (choice == 5) {
            cin >> a >> b;
            g.shortestPath(a, b);
        }
        else if (choice == 6) {
            g.printTable();
        }
        else if (choice == 7) {
            break;
        }
    }

    return 0;
}
