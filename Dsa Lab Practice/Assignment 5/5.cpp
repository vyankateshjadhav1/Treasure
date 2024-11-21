#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Define a pair to store nodes and their weights
typedef pair<int, int> NodeWeight;

// Function to find the shortest path using Dijkstra's algorithm
vector<int> dijkstra(int src, int n, const vector<vector<NodeWeight>>& graph) {
    vector<int> dist(n, INT_MAX);  // Distance array to store shortest distances
    dist[src] = 0;

    priority_queue<NodeWeight, vector<NodeWeight>, greater<NodeWeight>> pq;
    pq.push({0, src});  // Push the source node with distance 0

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // If the current distance is greater, skip processing
        if (currentDist > dist[currentNode]) continue;

        // Explore all neighbors of the current node
        for (const auto& neighbor : graph[currentNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;

            // Relaxation step
            if (dist[currentNode] + weight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cout << "Enter the number of locations (nodes): ";
    cin >> n;
    cout << "Enter the number of roads (edges): ";
    cin >> m;

    vector<vector<NodeWeight>> graph(n);

    cout << "Enter the roads (u v w) where u and v are locations and w is travel time:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});  // Assuming undirected graph
    }

    int source, destination;
    cout << "Enter the source and destination locations: ";
    cin >> source >> destination;

    // Get shortest path distances
    vector<int> dist = dijkstra(source, n, graph);

    if (dist[destination] == INT_MAX) {
        cout << "No path exists from source to destination." << endl;
    } else {
        cout << "Shortest time from " << source << " to " << destination << " is: " << dist[destination] << endl;
    }

    return 0;
}
