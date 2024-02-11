//idee: d[x] va stoca timpul de descoperire al nodului x
//low[x] va stoca cel mai mic timp de descoperire al unui nod accesibil din nodul x
//low[x] > d[x] => x pct de articulatie

#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100000;
vector<int> g[NMAX + 1]; // vectorul pt graf
int d[NMAX + 1], low[NMAX + 1], cnt, sol;
int art[NMAX + 1], h, vis[NMAX + 1], r;

void dfs(int x, int p) //p este parintele lui x
{
    vis[x] = 1;
    h++; //crestem adancimea
    d[x] = low[x] = h; // initializeaza timpul de descoperire si low ale nodului
    for(auto next : g[x]) {
        if(!vis[next]) { //daca vecinul nu a fost vizitat
            dfs(next, x); //continui dfs de la next
            low[x] = min(low[x], low[next]); // actualizez valoarea low a lui x
            if(x == r) { //daca x e rad arborelui dfs
                cnt++; //numar copiii radacinii
            } else {
                if(low[next] >= d[x]) {
                    art[x] = 1; // x e pct de articulatie
                }
            }
        } else { // e deja vizitat
            if(next != p) { //next nu e parintele lui x
                low[x] = min(low[x], d[next]); //se actualizeaza low pt x
            }
        }
    }
}

int main() {
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) { // daca n si m sunt 0 => ies din loop
            break;
        }
        //adaug muchiile in graf
        while(m--) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        r = 1; //initial radacina e 1
        sol = 0; //initial solutia e 0, nr de pct de articulatie gasite
        cnt = 0; //initial contorul pt copiii radacinii e 0
        h = 0; //initial adancimea e 0
        dfs(r, 0); //apelez dfs
        if(cnt >= 2) {  // Dacă rădăcina are cel puțin 2 copii în arborele DFS, atunci este punct de articulatie.
            art[1] = 1; // Marchez nodul 1 (rădăcina) ca punct de articulatie
        }
        for(int i = 1; i <= n; i++) { //parcurg  nodurile pt a numara pct de articulatie
            if(art[i] == 1) {
                sol++;
            }
        }
        for(int i = 1; i <= n; i++) { //eliberez memoria si resetez variabilele pt urm iteratie
            g[i].clear();
            art[i] = vis[i] = d[i] = low[i] = 0;
        }
        cout << sol << '\n';
    }
    return 0;
}