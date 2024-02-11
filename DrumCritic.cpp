//graf orientat, aciclic, ponderat si poate avea ponderi negative, drumul min de la o sursa unica, O(m+n)

//aici e drumul maxim!!!
//Se citesc din fișierul activitati.in următoarele
//informații despre activitățile care trebuie să se desfășoare în cadrul unui proiect:
//- n – numărul de activități (activitățile sunt numerotate 1,..., n)
//- d1, d2, ...., dn durata fiecărei activități
//- m – număr natural
//- m perechi (i, j) cu semnificația: activitatea i trebuie să se încheie înainte să înceapă j
//Activitățile se pot desfășura și în paralel.
//Să se determine timpul minim de finalizare a proiectului, știind că acesta începe la ora 0
//(echivalent – să se determine durata proiectului) și o succesiune (critică) de activități care
//determină durata proiectului (un drum critic – v. curs) O(m + n).
//Să se afișeze pentru fiecare activitate un interval posibil de desfășurare (!știind că
//activitățile se pot desfășura în paralel)

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

const int nmax = 100000;
vector<int> g[nmax + 1];
vector<int> top; // se retine ordinea topologica
vector<int> drumReconstruire;
vector<pair<int,int>> intervale;
int interior[nmax + 1]; // retine gradul intern al nodurilor
int n, m, du, durata[nmax + 1]={0}, d[nmax + 1]={0}, tata[nmax + 1]={0}, s, viz[nmax+1]={0}, final, nod;
queue<int> q;

void initializare() {
    fin >> n;

    durata[0]=0;
    // initializare vector durata
    for (int k = 1; k <= n; k++) {
        fin>>du;
        durata[k] = du;
    }
    durata[n+1]=0;

    fin >> m;

    // construiesc graful
    for (int t = 1; t <= m; t++) {
        int i, j;
        fin >> i >> j;
        interior[j]++;
        g[i].push_back(j);
    }

    //s si vecinii lui
    for ( int a=1; a <= n; a++)
    {
        if(interior[a] == 0)
        {
            g[0].push_back(a); //s = 0

        }

        if (g[a] . empty())
        {
            g[a].push_back(n+1); // t = n+1
        }
    }

}


void initializareDistante(int s) {
    for (int u = 0; u <= n+1; u++) {
        {if ( u == 0 )
            d[u]=0;
        else d[u] = numeric_limits<int>::min();

        tata[u] = 0;}
    }
}

void sortTop(int x) {
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

void DrumCriticMaxim() {
    for (auto u: top) {
        for (auto next : g[u]) {
            if (d[u] + durata[u] > d[next]) {  //relaxarea arcelor
                d[next] = d[u] + durata[u];
                tata[next] = u;
            }
        }
    }
}

void afisare() {

    //timp
    for (int c = 0; c <= n+1; c++) {
        final=d[n+1];
    }

    fout<<"timpul minim de finalizare: " <<final<< endl;

//drum
    fout<<"drum: ";
    nod =n+1;
    while( tata[nod] != 0 )
    {
        drumReconstruire.push_back(tata[nod]);
        nod=tata[nod];
    }

    for ( auto it : vector<int>(drumReconstruire.rbegin(), drumReconstruire.rend()))
    {
        fout<<it<<" ";
    }
    fout<<"\n";

    //intervale
    fout<<"intervale";
    fout<<"\n";

    for (int h = 1; h<=n; h++)
    {   int start = d[h];
        int end = d[h]+durata[h];
        intervale.push_back(make_pair(start, end));
    }

    for (int i = 1; i <= n; i++) {
        fout <<  i << ": ";
        fout << intervale[i-1].first <<" "<< intervale[i-1].second << "\n";
    }

}

int main() {

    initializare();
    //nodul de start s e primul in coada
    s=0;
    top.push_back(s);
    //se incepe sort top pt nodurile cu grad intern=0
    for (int i = 1; i <= n; i++) {
        if (!interior[i] && !viz[i]) {
            viz[i]=1;
            q.push(i);
            sortTop(i);
        }
    }

    initializareDistante(s);
    DrumCriticMaxim();
    afisare();

    fin.close();
    fout.close();
    return 0;
}
