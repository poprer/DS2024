#include <iostream>
#include <vector>
#include <climits>
#include<prior_queue>
using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, src });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& it : adj[u]) {
            int v = it.first;
            int weight = it.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

int () {
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

    vector<int> distances = dijkstra(V, adj, 0);
    cout << "Shortest distances from vertex 0:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "To " << i << " : " << distances[i] << endl;
    }

    return 0;
}