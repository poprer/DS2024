#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> primMST(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int i = 0; i < V; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;

        for (auto& it : adj[u]) {
            int v = it.first;
            int weight = it.second;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    return parent;
}

int main() {
    int V = 5;
    vector<vector<pair<int, int>>> adj(V);
    adj[0].push_back({ 1, 2 });
    adj[0].push_back({ 3, 6 });
    adj[1].push_back({ 2, 3 });
    adj[1].push_back({ 3, 8 });
    adj[1].push_back({ 4, 5 });
    adj[2].push_back({ 3, 7 });
    adj[2].push_back({ 4, 4 });
    adj[3].push_back({ 4, 9 });

    vector<int> parent = primMST(V, adj);
    cout << "Edge   \tWeight" << endl;
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << adj[i][parent[i]].second << endl;

    return 0;
}