#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int nmax = 100000;
vector<pair<pair<int, int>, int>> g;

ifstream fin("apm.in");
ofstream gout("apm.out");
int tata[nmax + 1],h[nmax+1], n, m;

void initializare(int u) {
    tata[u] = h[u]=0;
}

//cu compresie de cale
int reprezentant(int u) {
    if (tata[u] == 0)
        return u;
    tata[u] = reprezentant((tata[u]));
    return tata[u];

}

void reuneste(int u, int v) {
    int ru, rv;
    ru = reprezentant(u);
    rv = reprezentant(v);
    if(h[ru] > h[rv])
        tata[rv]=ru;
    else{
        tata[ru] = rv;
        if ( h[ru] == h[rv] )
            h[rv] = h[rv] + 1;
    }
}

void Kruskal() {
    for (int v = 1; v <= n; v++)
        initializare(v);

    int nrmsel = 0;
    int costTotal = 0;
    vector<pair<int, int>> arbore;

    for (auto edge : g) {
        int u = edge.first.first;
        int v = edge.first.second;
        if (reprezentant(u) != reprezentant(v)) {
            reuneste(u, v);
            nrmsel = nrmsel + 1;
            costTotal += edge.second;
            arbore.push_back({u, v});
            if (nrmsel == n - 1)
                break;
        }
    }

    gout << costTotal << "\n";
    gout << nrmsel << "\n";
    for (auto edge : arbore) {
        gout << edge.first << " " << edge.second << "\n";
    }
}

int main() {
    fin >> n >> m;
    while (m--) {
        int x, y, cost;
        fin >> x >> y >> cost;
        g.push_back({{x, y}, cost});
    }

    sort(g.begin(), g.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    Kruskal();

    fin.close();
    gout.close();

    return 0;
}
