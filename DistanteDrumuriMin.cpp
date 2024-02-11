//idee algoritm: se aplica bfs de 2 ori pt a calcula distanta de la control 1 si control2 la restul nodurilor
//se afiseaza distanta minima

//distanta minima cu bfs

// intrare: n , m , m linii, o linie cu noduri reprezentand pct de control
//Să se determine pentru fiecare nod din rețea distanța până la cel mai apropiat punct de control de acesta.
//iesire: În fișierul graf.out se vor afișa pentru fiecare nod de la 1 la n aceste distanțe separate prin

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
ifstream fin("drum.in");
ofstream gout("drum.out");

const int nmax = 100000;
vector<int> g[nmax + 1];

int n;

void bfs(int start, vector<int>& distante) {
    vector<int> viz(n + 1, 0);  //vector pt nodurile vizitate
    queue<int> q;
    q.push(start);
    distante[start] = 0; //distanta de la un nod la el insusi e 0
    viz[start] = 1; //nodul de start devine vizitat

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (auto next : g[x]) {
            if (!viz[next]) { //daca nu a fost vizitat inca
                q.push(next);
                viz[next] = 1;
                distante[next] = distante[x] + 1; //se actualizeaza distanta
            }
        }
    }
}

int main() {
    int m, control1, control2;
    fin >> n >> m;

    while (m--) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    fin >> control1 >> control2;

    vector<int> d1(n + 1, -1); //distanta min de la control1 la restul nodurilor
    vector<int> d2(n + 1, -1); //distanta min de la control2 la restul nodurilor

    //bfs pt control 1
    bfs(control1, d1);

    //bfs pt control 2
    bfs(control2, d2);

    //minimul dintre control 1 si un nod si control 2 si un nod
    for (int j = 1; j <= n; j++) {
        int min_dist_control1 = d1[j];
        int min_dist_control2 = d2[j];
        gout << min(min_dist_control1, min_dist_control2) << " ";
    }

    gout << endl;

    return 0;
}
