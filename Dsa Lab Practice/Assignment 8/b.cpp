#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Structure to store student data
struct Student {
    string name;
    int credits;
};

// Partition function for Quick Sort
int partition(vector<Student>& students, int low, int high) {
    int pivot = students[high].credits;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (students[j].credits > pivot) { // Sorting in descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);

        // Recursively sort elements before and after partition
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

// Display the top 3 students
void displayTopStudents(const vector<Student>& students) {
    cout << "Top 3 Students:" << endl;
    int count = min(3, static_cast<int>(students.size()));
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << students[i].name << " - " << students[i].credits << " credits" << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<Student> students(n);

    // Input student data
    cout << "Enter student names and their credits received in the last 2 years:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Name: ";
        cin >> students[i].name;
        cout << "Credits: ";
        cin >> students[i].credits;
    }

    // Sort students by credits using Quick Sort
    quickSort(students, 0, n - 1);

    // Display top 3 students
    displayTopStudents(students);

    return 0;
}
