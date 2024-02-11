#include <iostream>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

void graf(int n, int m, list<pair<int, int>> E, vector<list<int>>& L, bool tip) {

    if (tip == true) //neorientat
    {
        L.resize(n + 1);
        for (auto p : E) {
            L[p.first].push_back(p.second);
            L[p.second].push_back(p.first);
        }
    }
    else {
        L.resize(n + 1);
        for (auto p : E) {
            L[p.first].push_back(p.second);
        }

    }
}


void afisare(const vector<list<int>>& L) {
    for (int i = 1; i < L.size(); i++) {
        cout << i << " :";
        for (int vecin : L[i]) {
            cout << vecin << " ";
        }
        cout << endl;

    }
}

int main() {
    int n, m,x,y;
    bool tip;

    list <pair<int, int> >E ;
    vector<list<int> >L;

    ifstream f("graf.in.txt");
    f>>n>>m;

   while (f>>x>>y){
        E.push_back(make_pair(x,y));
    }

   tip=false;
    graf(n, m, E, L, tip);
    afisare(L);


    return 0;
}
