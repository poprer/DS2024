#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<stack>
using namespace std;

// ͼ���ڽӱ��ʾ
class Graph {
    int V; // ������
    vector<int>* adj; // �ڽӱ�

public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s);
    void DFS(int v);
    void dijkstra(int src);
    void primMST();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // ����ͼ
}

void Graph::BFS(int s) {
    vector<bool> visited(V, false);
    queue<int> queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        cout << s << " ";
        queue.pop();

        for (int i : adj[s]) {
            if (!visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

void Graph::DFS(int v) {
    stack<int> stack;
    vector<bool> visited(V, false);

    stack.push(v);
    while (!stack.empty()) {
        v = stack.top();
        stack.pop();
        cout << v << " ";
        for (int i : adj[v]) {
            if (!visited[i]) {
                visited[i] = true;
                stack.push(i);
            }
        }
    }
}

// Dijkstra�㷨��Prim�㷨��ʵ�ֽ����Ӹ��ӣ�����ֻ�ṩ��BFS��DFS�ļ�ʾ����

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "BFS starting from vertex 2: ";
    g.BFS(2);

    cout << "\nDFS starting from vertex 2: ";
    g.DFS(2);

    return 0;
}