//orientat, O(n+m)
// Fiind dat un nod S, sa se determine, pentru fiecare nod X, numarul minim de arce ce trebuie parcurse pentru a ajunge din nodul sursa S la nodul X.
// intrare: n,m,s, m linii
//iesire: N numere, cu semnificatia ca al i-lea numar reprezinta numarul minim de arce ce trebuie parcurse de la nodul S la nodul i.
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
ifstream fin("bfs.in");
ofstream gout("bfs.out");

const int nmax = 100000;
vector<int> g[nmax + 1];
int viz[nmax + 1], d[nmax + 1];

void bfs(int x) {
    queue<int> q;
    q.push(x);
    d[x] = 0; //distanta nodului de start x fata de el insusi e 0
    viz[x] = 1;

    while (!q.empty()) {
        x = q.front();
        q.pop();

        for (auto next : g[x]) {
            if (!viz[next]) {
                q.push(next);
                viz[next] = 1;
                d[next] = d[x] + 1;
            }
        }
    }
}

int main() {
    //nod = nodul de la care se incepe parcurgerea
    int n, m, nod;
    fin >> n >> m >> nod;

    //parcurge fisierul si creeaza un vector de liste cu listele de adiacenta
    while (m--) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
    }

    // Inițializează toate distanțele cu -1 pentru cazurile inaccesibile
    for (int i = 1; i <= n; i++) {
        d[i] = -1;
    }

    bfs(nod);

    // Afișează distanțele pentru fiecare nod.
    for (int i = 1; i <= n; i++) {
        gout << d[i] << ' ';
    }

    return 0;
}
