#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

class Graph {
    // Adjacency List representation
    unordered_map<string, list<pair<string, int>>> adjList;

public:
    // Add an edge to the graph
    void addEdge(string cityA, string cityB, int weight, bool bidirectional = true) {
        adjList[cityA].push_back(make_pair(cityB, weight));
        if (bidirectional) {
            adjList[cityB].push_back(make_pair(cityA, weight));
        }
    }

    // DFS Helper function
    void dfs(string city, unordered_map<string, bool>& visited) {
        visited[city] = true;
        for (auto neighbor : adjList[city]) {
            if (!visited[neighbor.first]) {
                dfs(neighbor.first, visited);
            }
        }
    }

    // Check if the graph is connected
    bool isConnected() {
        if (adjList.empty()) return true;

        unordered_map<string, bool> visited;
        for (auto city : adjList) {
            visited[city.first] = false;
        }

        // Start DFS from the first city
        string startCity = adjList.begin()->first;
        dfs(startCity, visited);

        // Check if all cities are visited
        for (auto city : visited) {
            if (!city.second) {
                return false;
            }
        }
        return true;
    }

    // Display the graph
    void printGraph() {
        for (auto city : adjList) {
            cout << city.first << " -> ";
            for (auto neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    int numFlights;

    cout << "Enter the number of flights (edges) between cities: ";
    cin >> numFlights;

    for (int i = 0; i < numFlights; i++) {
        string cityA, cityB;
        int weight;

        cout << "Enter the details for flight " << i + 1 << ": " << endl;
        cout << "From city: ";
        cin >> cityA;
        cout << "To city: ";
        cin >> cityB;
        cout << "Cost of the flight (weight): ";
        cin >> weight;

        g.addEdge(cityA, cityB, weight);
    }

    // Print the dynamically created graph (Adjacency List)
    cout << "\nGraph representation (Adjacency List):\n";
    g.printGraph();

    // Check if the graph is connected
    if (g.isConnected()) {
        cout << "\nThe graph is connected." << endl;
    } else {
        cout << "\nThe graph is not connected." << endl;
    }

    return 0;
}
