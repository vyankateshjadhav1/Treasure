#include<iostream>
#include<queue>
#include<vector>
using namespace std;

void findMinMax(const vector<int>& marks)
{
    if(marks.empty()){
        cout << "No marks to process.\n";
        return;
    }

    //max heap to find maximum marks
    priority_queue<int> maxHeap(marks.begin(),marks.end());

    //min heap to find minimum marks
   priority_queue<int, vector<int>, greater<int>> minHeap(marks.begin(),marks.end());

   // The top of maxHeap is maximum element
   int maxMarks = maxHeap.top();

   // The top of minHeap is minimum element
    int minMarks = minHeap.top();

    cout<<"Maximum marks: "<<maxMarks<<endl;
    cout<<"Minimum marks: "<<minMarks<<endl;
}

int main()
{
    vector<int> marks;

    cout<<"Enter number of students: ";
    int n;
    cin>>n;

    cout<<"Enter marks of the students: ";
    for(int i=0; i<n ;i++)
    {
        int mark;
        cin>>mark;
        marks.push_back(mark);
    }

    findMinMax(marks);
}