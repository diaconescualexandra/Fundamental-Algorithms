#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

const int nmax = 10000;

vector<pair<int, int> > adaugate;
pair<int, pair<int, int> > muchii[nmax+1];
int tata[nmax + 1];
int rank[nmax + 1];
int r[nmax + 1], r1, r2, n, m,q, costMax[1000] ;

void initializare(int n) {
    for (int i = 1; i <= n; ++i) {
        tata[i] = i;
        rank[i] = 0;
    }
}
void sortareMuchii()
{
    // Sortarea muchiilor în ordine crescătoare după cost
    sort(muchii, muchii + m);
}


int reprezentant(int x) {
    if (tata[x] != x) {
        tata[x] = reprezentant(tata[x]); // Path compression
    }
    return tata[x];
}

void unite(int x, int y) {
    int rootX = repreze(x);
    int rootY = find(y);

    if (rootX != rootY) {
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            tata[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            tata[rootY] = rootX;
        } else {
            tata[rootX] = rootY;
            rank[rootY]++;
        }
    }
}


void kruskal()
{

    for(int i = 0; i < m; i++)
    {
        int nod1, nod2, cost;

        nod1 = muchii[i].second.first;
        nod2 = muchii[i].second.second;
        cost = muchii[i].first;

        if (reprezentant(nod1) != reprezentant(nod2))
        {
            //  sunt aceeași componentă conexa => le unim
            reuneste(nod1, nod2, cost);

            // Actualizarea valorilor maxime pentru nodurile adăugate ulterior
            for(int j = 0; j < q; j++)
                if(reprezentant(adaugate[j].first) == reprezentant(adaugate[j].second) && costMax[j] == 1e9)
                {
                    costMax[j] = cost - 1; //
                }
        }
    }
}

void afisareSolutie()
{
    // Afișarea soluției pentru fiecare query
    for(int i = 0; i < q; i++)
        fout << costMax[i] << endl;
}


int main() {
    fin >> n >> m >> q;

    for(int i = 0; i < m; i++)
    {
        int x, y, t;

        fin >> x >> y >> t;

        muchii[i] = make_pair(t, make_pair(x, y));
    }

    for(int i = 0; i < q; i++)
    {
        int d, f;

        fin >> d >> f;
        adaugate.push_back(make_pair(d, f));
    }

    for(int i = 0; i < q; i++)
        costMax[i] = 1e9;

    sortareMuchii();

    kruskal();

    afisareSolutie();

    fin.close();
    fout.close();

    return 0;
}
