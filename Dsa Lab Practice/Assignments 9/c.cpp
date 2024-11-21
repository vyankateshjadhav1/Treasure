#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

// Function to find the minimum TSP cost using DP and bitmasking
int tsp(int mask, int pos, const vector<vector<int>>& dist, vector<vector<int>>& dp) {
    int n = dist.size();

    // Base case: If all cities are visited, return cost to return to the start
    if (mask == (1 << n) - 1) {
        return dist[pos][0] == -1 ? INF : dist[pos][0];
    }

    // If already computed, return the cached result
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int minCost = INF;

    // Try visiting all other cities
    for (int city = 0; city < n; ++city) {
        if (city != pos && !(mask & (1 << city)) && dist[pos][city] != -1) {
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp);
            minCost = min(minCost, newCost);
        }
    }

    return dp[mask][pos] = minCost;
}

int main() {
    // Input TSP matrix
    vector<vector<int>> dist = {
        {-1, 10, 15, 20},
        {10, -1, 35, 25},
        {15, 35, -1, 30},
        {20, 25, 30, -1}
    };

    int n = dist.size();

    // DP table to store results of subproblems
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    // Start TSP from city 0
    int minCost = tsp(1, 0, dist, dp);

    // Output result
    if (minCost == INF) {
        cout << "No TSP cycle exists!" << endl;
    } else {
        cout << "The minimum cost of the TSP cycle is: " << minCost << endl;
    }

    return 0;
}
