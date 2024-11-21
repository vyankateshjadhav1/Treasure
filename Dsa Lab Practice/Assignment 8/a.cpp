#include <iostream>
#include <vector>
using namespace std;

// Function to merge two subarrays
void merge(vector<int>& credits, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Create temporary arrays
    vector<int> leftArray(n1), rightArray(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = credits[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = credits[mid + 1 + i];

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            credits[k++] = leftArray[i++];
        } else {
            credits[k++] = rightArray[j++];
        }
    }

    // Copy remaining elements of leftArray (if any)
    while (i < n1) {
        credits[k++] = leftArray[i++];
    }

    // Copy remaining elements of rightArray (if any)
    while (j < n2) {
        credits[k++] = rightArray[j++];
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& credits, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first half
        mergeSort(credits, left, mid);

        // Sort the second half
        mergeSort(credits, mid + 1, right);

        // Merge the two halves
        merge(credits, left, mid, right);
    }
}

int main() {
    // Read the credits
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<int> credits(n);
    cout << "Enter the credits obtained by the students: ";
    for (int i = 0; i < n; i++) {
        cin >> credits[i];
    }

    // Sort the credits using merge sort
    mergeSort(credits, 0, n - 1);

    // Display the sorted credits
    cout << "Sorted credits: ";
    for (int credit : credits) {
        cout << credit << " ";
    }
    cout << endl;

    return 0;
}
