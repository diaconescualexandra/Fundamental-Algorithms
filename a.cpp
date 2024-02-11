//orientat, ponderat, poate avea ponderi negative, nu exista circuite cu cost negativ, drumuri minime intre toate perechile de varfuri
//O(n^3)

#include <iostream>
#include <fstream>
#include <set>


using namespace std;

ifstream fin("floyd.in");
ofstream fout("floyd.out");

int n,m,x,y,w,ok=0;
int d[100][100], p[100][100];
set <int> circuit;

void initializare()
{
    fin >> n >> m;
    for(int i = 1 ; i <= n ; i++ )
        for ( int j = 1 ; j <= n; j++) {
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = 1000;
        }

    for (int i = 1 ; i <= m ; i ++){
        fin >> x >> y >> w;
        d[x][y] = w;
    }

}

void FloydWarshall(){
    for ( int i =1 ; i<=n; i++)
        for ( int j =1; j <= n ; j ++) {
            if (d[i][j] == 1000)
                p[i][j] = 0;
            else
                p[i][j] = i;
        }

    for( int k = 1; k<= n ; k++)
        for ( int i =1; i<=n; i++)
            for ( int j =1; j <= n ; j ++)
                if ( d[i][j] > d[i][k] + d [k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }


}



void afisare() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ( d [i][j] < 0)
                ok =1;}}



    //circuit
    if (ok == 1)
    {
        fout << "circuit de cost negativ: " << endl;
        for (int i = 1; i <= n; i++)
            if (d[i][i] < 0)
                circuit.insert(i);

        for (auto element : circuit)
            fout << element << " ";
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                fout << d[i][j] << " ";
            }
            fout << endl;
        }
    }
}

int main() {
    initializare();
    FloydWarshall();
    afisare();


    return 0;
}
