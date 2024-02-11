

//drumuri minime din surse multiple
//O(mlogn)

#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;
ifstream fin("catun.in");
ofstream fout("catun.out");

const int NMAX = 36000;

vector<pair<int,int>> lista[NMAX + 1];
int d[NMAX + 1], p[NMAX + 1], vis[NMAX + 1];

int main()
{
    int n, m, k;
    fin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        d[i] = 1e9;
        p[i] = i;
    }

    set<pair<int,int>> s;
    for (int i = 1; i <= k; i++)
    {
        int x;
        fin >> x;
        d[x] = 0;
        s.insert(make_pair(0,x));
    }

    for (int i = 1; i <= m; i++)
    {
        int x, y, c;
        fin >> x >> y >> c;
        lista[x].push_back(make_pair(y, c));
        lista[y].push_back(make_pair(x, c));
    }

    while (!s.empty())
    {
        auto it = s.begin();
        int x = (*it).second;
        s.erase(it);

        if (vis[x] == 1)
            continue;

        vis[x] = 1;

        for (auto next:lista[x])
        {
            if (d[next.first] > d[x] + next.second)
            {
                d[next.first] = d[x] + next.second;
                p[next.first] = p[x];
                s.insert(make_pair(d[next.first], next.first));
            }
            else
            {
                if (d[next.first] == d[x] + next.second)
                    p[next.first] = min(p[next.first], p[x]);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (d[i] == 1e9 || d[i] == 0)
            fout << 0 << " ";
        else fout << p[i] << " ";
    }

    return 0;
}