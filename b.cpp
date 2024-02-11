#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

using namespace std;

ifstream fin("b.in");
ofstream fout("b.out");

int n,m,x,y,w,ok=0, e[100]={0}, raza=1000, diametru=0, centru =0, s, t;
int d[100][100], p[100][100];
set <int> lant;

void initializare()
{
    fin >> n >> m;
    for(int i = 1 ; i <= n ; i++ )
        for ( int j = 1 ; j <= n; j++) {
            if (i == j)
            {d[i][j] = 0;
                d[j][i] = 0;}
            else
            {d[i][j] = 1000;
                d[j][i]=1000;}
        }

    for (int i = 1 ; i <= m ; i ++){
        fin >> x >> y >> w;
        d[x][y] = w;
        d[y][x] = w;
    }

}

void FloydWarshall(){
    for ( int i =1 ; i<=n; i++)
        for ( int j =1; j <= n ; j ++) {
            if (d[i][j] == 1000 || d[j][i] ==1000)
            { p[i][j] = 0;
                p[j][i] =0 ; }

            else
            {p[i][j] = i;
                p[j][i] = i ; }
        }

    for( int k = 1; k<= n ; k++)
        for ( int i =1; i<=n; i++)
            for ( int j =1; j <= n ; j ++)
                if ( (d[i][j] > d[i][k] + d [k][j]) || (d[j][i] > d[j][k] + d [k][i] )){
                    d[i][j] = d[i][k] + d[k][j];
                    d[j][i] = d[j][k] + d[k][i];
                    p[j][i] = p[k][i];
                    p[i][j] = p[k][j];
                }


}

void RazaCentruDiametruLant (){

    //excentricitatea
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        { e[i] = max(e[i],d[i][j]);} }

    //raza
    for ( int i =1; i<=n; i++)
    {
        raza = min ( raza, e [i]);
    }

    //diametru
    for ( int i =1; i<=n; i++)
    {
        diametru = max ( diametru, e [i]);
    }

    //centrul
    for ( int i =1; i<=n; i++)
    {
        if ( e [i] == raza)
            centru =i;
    }

    //lant diametral
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ( d [i][j] == diametru )
            {
                s=i;
                t=j;
                break;
            }
            }
        }
}

void drum(int s, int t){
    if(s!=t)
        drum(s, p[s][t]);
    fout << t << " ";

}

void afisare() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ( d [i][j] < 0 || d[j][i] < 0)
                ok =1;}}



    //circuit
//    if (ok == 1)
//    {
//        fout << "circuit de cost negativ: " << endl;
//        for (int i = 1; i <= n; i++)
//            if (d[i][i] < 0)
//                circuit.insert(i);
//
//        for (auto element : circuit)
//            fout << element << " ";
//    }
//    else
//    {
//        for (int i = 1; i <= n; i++)
//        {
//            for (int j = 1; j <= n; j++)
//            {
//                fout << d[i][j] << " ";
//            }
//            fout << endl;
//        }
//    }

    fout<<"p"<<endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fout << p[i][j]<<" ";}
        fout<<endl; }

    fout<<endl;
    fout<<"Raza: "<<raza<<endl;
    fout<<"Diametrul: "<<diametru<< endl;
    fout<<"Centrul: "<<centru<<endl;
    fout<<"Lant diametral: ";

}

int main() {
    initializare();
    FloydWarshall();
    RazaCentruDiametruLant();
    afisare();
    drum(s,t);


    return 0;
}
