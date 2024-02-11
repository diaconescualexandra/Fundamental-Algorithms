//idee algoritm: se executa bfs pornind de la primul nod gasit care are gradul intern 0,
//pe parcurs se scade nodul intern al vecinilor, si se adauga in coada cand au gradul 0
//cand un nod are grad 0 si a fost nevizitat se adauga in ordinea topologica
//daca la final nu sunt toate nodurile in top, => impossible

//orientat O(m+n)
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
ifstream fin("top.in");
ofstream gout("top.out");

const int nmax = 100000;
vector<int> g[nmax + 1];
vector<int> top; // se retine ordinea topologica
int interior[nmax + 1]={0}; // retine gradul intern al nodurilor
int viz[nmax+1]={0};
queue<int> q;

void bfs(int x) {

    while (!q.empty()) {
        x = q.front();
        q.pop();
        top.push_back(x); // adaug nodul in ordinea topologica

        for (auto next : g[x]) {
            interior[next]--;
            if (interior[next] == 0 && !viz[next]) {//Dacă nodul nu mai are muchii care intră în el și nu a fost vizitat anterior
                viz[next]=1; // marchez nodul ca vizitat
                q.push(next); //il adaug in coada
            }
        }
    }
}

int main() {
    int n, m;
    fin >> n >> m;

    //construiesc graful
    while (m--) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        interior[y]++; // aflu gradul interior al fiecarui nod
    }

//    apelam bfs pentru primul nod cu grad intern 0
    for (int i = 1; i <= n; i++) {
        if (!interior[i] && !viz[i]) {
            viz[i]=1;
            q.push(i);
            bfs(i);
        }
    }

    //daca ordinea topologica nu a fost gasita => impossible
    if (top.size() != n) {
        gout << "IMPOSSIBLE" << endl;
    } else {
        for (int nod : top) {
            gout << nod << ' ';
        }
    }


    return 0;
}