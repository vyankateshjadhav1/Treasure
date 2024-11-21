#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//struture to represent an item
struct Item{
    int value;
    int weight;
};

bool compare(Item a, Item b){

    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight; 
    return ratioA > ratioB;

}

//function to calculate th maximum value usinf Fractional Knapsack
double fractionalKnapsack(vector<Item>& items, int capacity){

    //sort the items based on value/weight ratio
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    for(const auto& item : items){
        if(capacity >= item.weight){

            totalValue += item.value;
            capacity -= item.weight;

        }
        else{

            totalValue += item.value * ((double)capacity / item.weight);
            break;  //Knapsack is full
        }
    }

    return totalValue;

}

int main(){
    int n,capacity;
    cout<<"Enter the number of items: ";
    cin>>n;

    vector<Item> items(n);
    cout<<"Enter the value and weight of the items(value weight): "<<endl;
    for(int i = 0; i<n; i++){
        cin>>items[i].value >> items[i].weight;
    }

    cout<<"Enter the capacity of the knapsack: ";
    cin>>capacity;

    double maxValue = fractionalKnapsack(items, capacity);
    cout<<"Maximum value in the knapsack: "<<maxValue<<endl;

    return 0;
}

