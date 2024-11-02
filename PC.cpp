#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>

using namespace std;
long long minCostToReorder(const vector<int>& weights, const vector<int>& initial, const vector<int>& target) {
    int n = initial.size();
    vector<bool> visited(n, false);
    unordered_map<int, int> targetPos;

    for (int i = 0; i < n; i++) {
        targetPos[target[i]] = i;
    }
// finding the total cost
    long long totalCost = 0;
    int globalMinWeight = *min_element(weights.begin(), weights.end());

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        int cycleSize = 0;
        int cycleMinWeight = weights[initial[i] - 1];
        long long cycleCost = 0;
        int j = i;

 
        while (!visited[j]) {
            visited[j] = true;
            int marble = initial[j];
            int pos = targetPos[marble];
            cycleMinWeight = min(cycleMinWeight, weights[marble - 1]);
            cycleCost += weights[marble - 1];
            cycleSize++;
            j = pos;
        }
        if (cycleSize > 1) {
            long long directCost = cycleCost + (cycleSize - 2) * cycleMinWeight;
            long long withGlobalMin = cycleCost + cycleMinWeight + (cycleSize + 1) * globalMinWeight;
            totalCost += min(directCost, withGlobalMin);
        }
    }

    return totalCost;
}
// input the main problem number in the problem
int main(){
    freopen("input.txt","r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
            vector<int> weight(n),initial(n), target(n);

        for(int i = 0; i < n; i++) cin >> weight[n];
        for(int i = 0; i < n; i++) cin >> initial[n];
        for(int i = 0; i < n; i++) cin >> target[n];
            cout << minCostToReorder(weight, initial, target) << endl;
    return 0;

}

