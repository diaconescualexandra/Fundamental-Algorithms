//Conectarea cu cost minim a nodurilor la mai multe  surse

#include <bits/stdc++.h>
using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

struct punct {
    long long x, y;
};
punct c[2001], b[2001];
long long d[2001], vis[2001];

//distanta euclidiana
long long dist(punct a, punct b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n, m;
    f >> n >> m;
    for(int i = 1; i <= n; i++) {
        f >> c[i].x >> c[i].y;
    }
    for(int i = 1; i <= m; i++) {
        f >> b[i].x >> b[i].y;
        d[i] = 1e18; //costu min de la fiecare bloc la o sursa de curent
    }
    //dist initiale
    for(int i = 1; i <= m; i++) {
        long long mn = 1e18;
        for(int j = 1; j <= n; j++) {
            mn = min(mn, dist(b[i], c[j]));
        }
        d[i] = mn;
    }
    //cost min cu prim
    for(int i = 1; i <= m; i++) {
        long long mn = 1e18;
        int pos = 0;
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] < mn) {
                mn = d[j];
                pos = j;
            }
        }
        vis[pos] = 1;
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] > dist(b[pos], b[j])) {
                d[j] = dist(b[pos], b[j]);
            }
        }
    }
    double sol = 0;
    for(int i = 1; i <= m; i++) {
        sol += sqrt(d[i]);
    }
    g << fixed << setprecision(7) << sol;
    return 0;
}