//orientat, ponderat, ponderile pot fi negative, fara cicluri negative, drumul min de la o sursa unica
//pt ponderi negative
//O(nm)

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("bellman.in");
ofstream fout("bellman.out");

const int nmax = 1000;
struct edge { int x, y, c; };

vector<edge> v;
int d[nmax], tata[nmax], s, n, m, ok = 0, nod, a;

void initializare() {
    fin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int x, y, c;
        fin >> x >> y >> c;
        v.push_back({x, y, c});
    }

    for (int i = 1; i <= n; i++) {
        d[i] = 1e9;
        tata[i] = 0;
    }
    fin >> s;
    d[s] = 0;
}


void setPath(int r, int q) {
    vector<int> drum;
    drum.push_back(q);
    while (true) {
        q = tata[q];
        drum.push_back(q);
        if (q == r)
            break;
    }
    for (int i = drum.size() - 1; i >= 0; i--) {
        fout << drum[i] << " ";
    }
}


void BellmanFord() {
    for (int i = 1; i <= n - 1; i++) {
        for (auto it : v) {
            if (d[it.y] > d[it.x] + it.c) {
                d[it.y] = d[it.x] + it.c;
                tata[it.y] = it.x;
            }
        }
    }

    //daca are circuite negative
    for (auto it : v) {
        if (d[it.y] > d[it.x] + it.c) {
            d[it.y] = d[it.x] + it.c;
            tata[it.y] = it.x;
            ok = 1;
            break;
        }
    }
}




void afisare() {
    if (ok == 1) {
        fout << "circuit de cost negativ: ";
        setPath(s,n);
    } else {

        for (int i = 1; i <= n; i++) {
            if (d[i] != 0) {
                fout << "Drum: " ;
                setPath(s, i);
                fout << "Cost: " << d[i] << endl;
            }
        }

    }
}

int main() {
    initializare();
    BellmanFord();
    afisare();

    return 0;
}
