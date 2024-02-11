//orientat, poate fi ciclic, ponderat pozitiv, drum minim de la o sursa unica, O(m logn)

#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <limits>
#include <vector>
#include <set>

using namespace std;

ifstream fin ("retea.in");
ofstream fout ("retea.out");

const int nmax = 100000;
int n,m,k,d[nmax+1]={0}, tata[nmax+1]={0},s,u, p,v, control, cel_mai_ap_pct, nod, nnod;
list<pair<int,int>>g[nmax+1];
set <pair< int, int >>q;
int minDistance = numeric_limits<int>::max();
int puncteControl[nmax+1];
vector<int>drum;

void initializare(){
    fin>>n>>m;

    for (int i = 1; i<=m; i++)
    {
        int u,v,w;
        fin>>u>>v>>w;
        g[u].push_back(make_pair(w, v));
        g[v].push_back(make_pair(w, u));

    }

    fin >> k;
    for(int i=1; i<=k;i++)
    {
        fin>>control;
        puncteControl[i]=control;
    }

}

void initializareDistante(){
    for (int i =1; i<=n; i++)
    {d[i]= numeric_limits<int>::max();
        tata[i]=0;}

}


void Dijkstra(){
    while(!q.empty())
    {
        u=q.begin()->second;
        q.erase(q.begin());
        for ( pair <int, int> it : g[u])
        {
            v=it.second; p=it.first; //p=pondere
            if(d[v]>d[u]+p)    //relaxarea arcelor
            {
                q.erase({d[v], v});
                d[v]=d[u]+p; tata[v]=u;
                q.insert({d[v], v});
            }
        }
    }


}

void afisare () {

    for(int i=1; i<=k; i++ )
    {
        minDistance = min (minDistance, d[puncteControl[i]]);

    }
    for(int i=1; i<=n; i++ )
    {
        if(d[i] == minDistance)

            cel_mai_ap_pct=i;
    }
    fout<<"cel mai ap pct: "<<cel_mai_ap_pct<<endl;


    nod = cel_mai_ap_pct;
    nnod=nod;
    while ( tata[nod] != 0 )
    {
        drum.push_back(tata[nod]);
        nod=tata[nod];
    }

    for ( auto it : vector<int>(drum.rbegin(), drum.rend()))
    {
        fout<<it<<" ";
    }
    fout<<nnod;
    fout<<"\n";


}
int main(){

    initializare ();
    initializareDistante();
    fin>>s;
    d[s]=0;
    q.insert({d[s],s}); //d[s] = distanta lui s, s = nodul
    Dijkstra();
    afisare();

    return 0;
}