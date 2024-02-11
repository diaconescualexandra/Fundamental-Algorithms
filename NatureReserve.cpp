//Conectarea cu cost minim a nodurilor la mai multe  surse

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
int d[NMAX + 1];
bool vis[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1];

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, m, L, k;
        cin >> n >> m >> L >> k;
        set<pair<int, int>> s;
        for(int i = 1; i <= n; i++) {
            d[i] = 1e9;
            vis[i] = 0;
        }
        for(int i = 1; i <= k; i++) {
            int x;
            cin >> x;
            d[x] = 0;
            s.insert({0, x});
        }
        for(int i = 1; i <= m; i++) {
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({y, c});
            G[y].push_back({x, c});
        }
        //prim
        long long sol = 0;
        while(!s.empty()) {
            auto it = s.begin();
            s.erase(it);
            int cost = (*it).first;
            int node = (*it).second;
            if(vis[node]) {
                continue;
            }
            //aflare cost
            vis[node] = 1;
            sol += 1LL * cost;
            for(auto next : G[node]) {
                if(d[next.first] > next.second) { //daca dist nod vecin > cost
                    d[next.first] = next.second;
                    s.insert({d[next.first], next.first}); // le adaug in s care retine nodurile cu dim minime
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }
        sol += 1LL * (n - k) * L;
        cout << sol << '\n';
    }
    return 0;
}