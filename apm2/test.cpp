
//graf dinamic
//graf neorientat

// pentru fiecare nou drum propus, care este cea mai mare taxă posibila pe care o pot asocia drumului respectiv astfel încât
// acesta să apară sigur în arborele parţial de cost minim al Republicii.

//intrare: Fisierul de intrare apm2.in va conţine pe prima sa linie cele trei numere N, M, şi Q.
// Fiecare dintre următoarele M linii va descrie câte un drum prin trei numere întregi: X, Y şi T, taxa asociată acestuia.
// Fiecare dintre următoarele Q linii va descrie câte un drum adăugat de Marele Lider, prin două numere, A şi B

//iesire: Fişierul de ieşire apm2.out va conţine Q linii. Pe a i-a linie se va afla răspunsul întrebarea
//Care este cea mai mare taxă pe care o putem asocia celei de a i-a muchii ipotetice astfel încât aceasta să se afle sigur
// în arborele parţial de cost minim al reţelei?.


#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

const int nmax = 10000;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

int n, m,q,h[nmax + 1],costMax[1000], parinte[nmax + 1];

vector<pair<int, int> > adaugate;

pair<int, pair<int, int> > muchii[100001];


int reprezentant(int u)
{
    if(parinte[u] != 0)
        u = reprezentant(parinte[u]);

    return u;
}

void uneste(int u, int v, int cost)
{
    // Uneste două componente conexe într-o singură componentă conexă
    int repu, repv;

    // Găsește reprezentanții (liderii) ai componentelor conexe
    repu = reprezentant(u);
    repv = reprezentant(v);

    if(h[repu] > h[repv])
    {
        parinte[repv] = repu;
    }
    else
    {
        parinte[repu] = repv;

        if(h[repu] == h[repv])
            h[repv] += 1;
    }
}

void kruskal()
{       sort(muchii, muchii + m);

    for(int i = 0; i < m; i++)
    {


        if (reprezentant(muchii[i].second.first) != reprezentant(muchii[i].second.second))
        {
           //nu sunt in aceeasi comp conexa => le unim
            uneste(muchii[i].second.first, muchii[i].second.second,muchii[i].first);

            // costul max pt drumurile liderului
            for(int j = 0; j < q; j++)
                if(reprezentant(adaugate[j].first) == reprezentant(adaugate[j].second) && costMax[j] == 1e9)
                {
                    costMax[j] = muchii[i].first - 1;
                }
        }
    }
}



int main()
{
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

    for(int i = 1; i <= n; i++)
        parinte[i] = h[i] = 0;

    for(int i = 0; i < q; i++)
        costMax[i] = 1e9;

    kruskal();

    for(int i = 0; i < q; i++)
        fout << costMax[i] << endl;

    fin.close();
    fout.close();

    return 0;
}