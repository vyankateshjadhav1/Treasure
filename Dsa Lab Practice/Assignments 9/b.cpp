#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a job
struct Job {
    char id;      // Job ID
    int deadline; // Deadline of the job
    int profit;   // Profit associated with the job
};

// Comparison function to sort jobs by profit in descending order
bool compareJobs(const Job& a, const Job& b) {
    return a.profit > b.profit;
}

// Function to schedule jobs and maximize profit
void jobScheduling(vector<Job>& jobs) {
    // Sort jobs in descending order of profit
    sort(jobs.begin(), jobs.end(), compareJobs);

    int n = jobs.size();

    // Find the maximum deadline to create a schedule
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    // Create a schedule array to keep track of jobs
    vector<int> schedule(maxDeadline, -1); // -1 means slot is empty
    vector<char> selectedJobs;            // To store selected job IDs
    int totalProfit = 0;

    // Assign jobs to slots
    for (const auto& job : jobs) {
        for (int i = job.deadline - 1; i >= 0; --i) {
            if (schedule[i] == -1) { // If the slot is free
                schedule[i] = job.id;
                selectedJobs.push_back(job.id);
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Display the selected jobs and total profit
    cout << "Selected Jobs with Deadlines:" << endl;
    for (const auto& job : selectedJobs) {
        cout << "Job " << job << endl;
    }
    cout << "Total Profit: " << totalProfit << endl;
}

int main() {
    // Initialize job list
    vector<Job> jobs = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    // Call the job scheduling function
    jobScheduling(jobs);

    return 0;
}
