
//probabilitati dijkstra

#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <limits>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

ifstream fin ("retea.in");
ofstream fout ("retea.out");

const int nmax = 100000;
int n,m, tata[nmax+1]={0},s, u,v, nod, nnod, t;
double d[nmax+1]={0};
double probabilitate,p;
list<pair<double,int>>g[nmax+1];
set <pair< double, int >>q;
vector<int>drum;

void initializare(){
    fin>>n>>m;

    for (int i = 1; i<=m; i++)
    {
        int u,v,w;
        fin>>u>>v>>w;
        probabilitate = pow ( 2,-w);
        g[u].push_back(make_pair(probabilitate, v));

    }

    fin >> s;
    fin >> t;

}

void initializareDistante(){
    for (int i =1; i<=n; i++)
    {d[i]= 0.0;
        tata[i]=0;
    } d[s]=1.0;

}


void Dijkstra(){
    while(!q.empty())
    {
        u=q.begin()->second;
        q.erase(q.begin());
        for ( pair <double, int> it : g[u])
        {
            p=it.first; v=it.second; //p=pondere
            if(d[u]*p > d[v])
            {
                q.erase({d[v], v});
                d[v]=d[u]*p; tata[v]=u;
                q.insert({d[v], v});
            }
        }
    }


}

void afisare () {

    fout<<"drum: ";
    nod = t;
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
    q.insert({d[s],s}); //d[s] = distanta lui s, s = nodul
    Dijkstra();
    afisare();

    return 0;
}