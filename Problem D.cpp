#include<iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;
int main() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
  
    set<pair<int, int>> obstacles;
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        obstacles.emplace(x, y);
    }

    int xs, ys;
    cin >> xs >> ys;
    pair<int, int> start = {xs, ys};
    
    vector<int> results;
    for (int i = 0; i < q; ++i) {
        int xt, yt;
        cin >> xt >> yt;
        pair<int, int> target = {xt, yt};
        
        int result = bfs(n, m, obstacles, start, target);
        results.push_back(result);
    }
    
    // Output results 
    for (int res : results) {
        cout << res << endl;
    }
    
    return 0;
}
// Directions: (dx, dy) 
const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
enum Direction { UP = 0, DOWN, LEFT, RIGHT };

int bfs(int n, int m, const set<pair<int, int>>& obstacles, pair<int, int> start, pair<int, int> target) {
    int xs = start.first, ys = start.second;
    int xt = target.first, yt = target.second;
    
    // Queue elements: (x, y, direction, direction_changes)
    queue<tuple<int, int, int, int>> q;
    set<tuple<int, int, int>> visited;
    
    // Initialize the queue with the start position and all directions
    for (int d = 0; d < 4; d++) {
        q.emplace(xs, ys, d, 0);
        visited.emplace(xs, ys, d);
    }
    
    while (!q.empty()) {
        auto [x, y, direction, changes] = q.front();
        q.pop();
        
        // Check if reached the target
        if (x == xt && y == yt) {
            return changes;
        }
        
        // Move forward in the current direction
        int nx = x + DIRECTIONS[direction].first;
        int ny = y + DIRECTIONS[direction].second;
        if (nx > 0 && nx <= n && ny > 0 && ny <= m && obstacles.find({nx, ny}) == obstacles.end() &&
            visited.find({nx, ny, direction}) == visited.end()) {
            q.emplace(nx, ny, direction, changes);
            visited.emplace(nx, ny, direction);
        }
        
        // Turn to other directions (left, right, 180-degree turn)
        for (int new_direction = 0; new_direction < 4; new_direction++) {
            if (new_direction != direction) {  // Only change directions if it's different
                if (visited.find({x, y, new_direction}) == visited.end()) {
                    q.emplace(x, y, new_direction, changes + 1);
                    visited.emplace(x, y, new_direction);
                }
            }
        }
    }
    
    return -1;  // Target is unreachable
}
// HCMUTE - PoseTona
