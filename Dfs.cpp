//neorientat cu n noduri si m muchii
//O(n+m)
//Sa se determine numarul componentelor conexe ale grafului.
//iesire: nr de comp conexe

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ifstream fin("dfs.in");
ofstream gout("dfs.out");

const int nmax=100000;
vector < int > g[nmax+1];
int viz[nmax+1];


void dfs(int x) {
    viz[x]=1;

    for (auto next : g[x]) {
        if (! viz[next] ){
            dfs(next);

        }
    }

}

int main() {
    int n,m;
    fin>>n>>m;

    while(m--){
        int x, y;
        fin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int NrCompConexe =0;
    for(int i = 1; i <=n; i++){
        if ( !viz[i] ) {
            NrCompConexe ++ ;
            dfs(i);

        }
    }

    gout<<NrCompConexe;


    return 0;
}
