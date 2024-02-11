//KOSARAJU
//graf orientat
//O(n+m)
//intrare: n, m, m linii
//iesire: nr de componente tare conexe
//idee : se parcurge cu dfs1 pt a afla ordinea topologica, si cu dfs2 pt a afla toate nodurile unei componente tare conexe (se foloseste ordinea inversa)
#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;
const int nmax = 100000;

bool viz[nmax];
int n, m, rt[nmax]; //rt retine radacina fiecarei comp tare conexe
vector<int> top, comp, g[nmax], gr[nmax];
//in top se retine ordinea  topologica
//comp -> pt stocare temporara
//g -> list de adiacenta
//gr -> inversul lui g (daca in g am 1->2 in gr am 2->1)

void dfs1(int u){ //dfs1 folosit pentru ordinea topologica
    viz[u] = true;
    for(int v : g[u])
        if(!viz[v])
            dfs1(v);
    top.push_back(u);
}

void dfs2(int u){ // dfs2 folosit pentru a gasi toate nodurile
    // unei componentele tare conexe care contine u
    viz[u] = true;
    comp.push_back(u);
    for(int v : gr[u])
        if(!viz[v])
            dfs2(v);
}

int main() {

    cin>>n>>m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        gr[y].push_back(x); //inversul grafului

    }


    for (int i = 1; i <= n; i++)
        if (!viz[i])
            dfs1(i); // se calculeaza ordinea topologica

    int K = 0; // nr de componente tare conexe

    //toate nodurile sunt setate la nevizitat
    for (int i = 1; i <= n; i++) {
        viz[i] = false;
    }

    reverse(top.begin(), top.end());
    for (int u: top) { // parcurgere in ordinea inversata
        if (!viz[u]) { //daca n a fost vizita => componenta tare conexa noua
            dfs2(u);
            K++; //am gasit o noua comp tare conexa
            for (int v: comp) //parcurge nodurile din comp care retine nodurile din
                //componenta tare conexa curenta ( cea gasita de dfs2)
                rt[v] = K; //se pune radacina fiecarui nod
            comp.clear();
        }
    }

    cout << K << endl;
    for (int i = 1; i <= n; i++) {
        cout << rt[i]; // afisez radacina
        if (i == n) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }
return 0;
}