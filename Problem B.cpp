int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q;
    cin >> n >> q;
    
    for (int i = 1; i <= n; i++) {
        cin >> significance[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1, 0); 
  
    while (q--) {
        int w, x, y, z;
        cin >> w >> x >> y >> z;
        
        int lca_wx = lca(w, x);
        int lca_yz = lca(y, z);

        unordered_map<int, int> countSignificance;
        
        for (int node : {w, x, lca_wx, y, z, lca_yz}) {
            if (node != 0) { 
                countSignificance[significance[node]]++;
            }
        }
        
        int result = 0;
        for (auto& [sig, count] : countSignificance) {
            if (count >= 2) result += (count * (count - 1)) / 2;
        }

        cout << result << endl;
    }
    
    return 0;
}
