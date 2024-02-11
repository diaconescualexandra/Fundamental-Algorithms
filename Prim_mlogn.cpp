#include <bits/stdc++.h>
using namespace std;

void spanningTree(int n, int m, vector<pair<int, int>> adj[], int &sum, int &NrMuchii, set<pair<int, int>> &mst) {
    priority_queue<tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>> pq;

    vector<int> vis(n + 1, 0);
    pq.push({0, 0, 1});
    sum = 0;
    NrMuchii = 0;

    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        int tata = get<1>(it);
        int copil = get<2>(it);
        int wt = get<0>(it);

        if (vis[copil] == 1)
            continue;

        vis[copil] = 1;
        sum += wt;

        if (tata != 0) {
            mst.insert({min(tata, copil), max(tata, copil)});
            NrMuchii++;
        }

        for (auto vecin : adj[copil]) {
            int adjNode = vecin.first;
            int edW = vecin.second;
            if (!vis[adjNode]) {
                pq.push({edW, copil, adjNode});
            }
        }
    }
}

int main() {
    ifstream fin("apm.in");
    ofstream gout("apm.out");

    int n, m;
    fin >> n >> m;

    vector<pair<int, int>> adj[n + 1];
    int u, v, w;
    while (m--) {
        fin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    fin.close();

    int sum, NrMuchii;
    set<pair<int, int>> mst;
    spanningTree(n, m, adj, sum, NrMuchii, mst);

    gout << sum << endl;
    gout << NrMuchii << endl;
    for (auto muchii : mst) {
        gout << muchii.first << " " << muchii.second << endl;
    }

    gout.close();

    return 0;
}
