#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
using namespace std;

// Define the size of the hash table
const int TABLE_SIZE = 10;

// Hash function
int hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash + c) % TABLE_SIZE;
    }
    return hash;
}

// Separate Chaining Hash Table
class SeparateChainingHashTable {
    vector<list<pair<string, string>>> table;

public:
    SeparateChainingHashTable() : table(TABLE_SIZE) {}

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        table[index].push_back({name, phone});
    }

    string search(const string& name, int& comparisons) {
        int index = hashFunction(name);
        for (const auto& entry : table[index]) {
            comparisons++;
            if (entry.first == name) {
                return entry.second;
            }
        }
        return "Not Found";
    }
};

// Open Addressing (Linear Probing) Hash Table
class LinearProbingHashTable {
    vector<pair<string, string>> table;
    vector<bool> occupied;

public:
    LinearProbingHashTable() : table(TABLE_SIZE, {"", ""}), occupied(TABLE_SIZE, false) {}

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        while (occupied[index]) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index] = {name, phone};
        occupied[index] = true;
    }

    string search(const string& name, int& comparisons) {
        int index = hashFunction(name);
        while (occupied[index]) {
            comparisons++;
            if (table[index].first == name) {
                return table[index].second;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        return "Not Found";
    }
};

int main() {
    SeparateChainingHashTable chainingTable;
    LinearProbingHashTable probingTable;

    // Sample telephone book data
    vector<pair<string, string>> clients = {
        {"Alice", "1234567890"},
        {"Bob", "2345678901"},
        {"Charlie", "3456789012"},
        {"Diana", "4567890123"},
        {"Eve", "5678901234"}
    };

    // Insert data into hash tables
    for (const auto& client : clients) {
        chainingTable.insert(client.first, client.second);
        probingTable.insert(client.first, client.second);
    }

    // Search keys and compare performance
    vector<string> searchKeys = {"Alice", "Charlie", "Eve", "Frank"};
    cout << "Comparisons required for Separate Chaining and Linear Probing:\n";
    cout << left << setw(10) << "Name" << setw(20) << "Separate Chaining" << "Linear Probing\n";

    for (const string& key : searchKeys) {
        int comparisonsChaining = 0;
        int comparisonsProbing = 0;

        chainingTable.search(key, comparisonsChaining);
        probingTable.search(key, comparisonsProbing);

        cout << left << setw(10) << key << setw(20) << comparisonsChaining << comparisonsProbing << "\n";
    }

    return 0;
}
