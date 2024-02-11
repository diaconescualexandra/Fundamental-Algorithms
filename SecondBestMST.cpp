//


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;



// pentru algoritmul union-find
int parent[10005];
// pentru a salva muchiile din MST
vector<int> presentInMST;
// numarul de muchii in afara MST
int nrEdges;

// struct pentru a reprezenta o muchie
struct edge {
    int src, dest, weight;
} edges[10005];

// comparator custom pentru a compara muchiile
// dupa cost
bool cmp(edge x, edge y) {
    return x.weight < y.weight;
}

// initializez vectorul parinte pentru union-find
void InitializareParinte(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

// union pentru a determina primul APM
int union1(int i, int MSTcost) {

    int x = find(edges[i].src);
    int y = find(edges[i].dest);

    //nu fac parte din aceeasi componenta
    if (x != y) {
        parent[x] = y;
        presentInMST.push_back(i);
        MSTcost += edges[i].weight;
    }
    return MSTcost;
}


// union pentru a determina al doilea APM
int union2(int i, int MSTcost) {
    // cautam parintele nodului sursa
    // si parintele nodului destinatie
    int x = find(edges[i].src);
    int y = find(edges[i].dest);

    // daca nu au acelasi parinte (nu fac parte din
    // aceeasi componenta)
    if (x != y) {
        parent[x] = y;
        MSTcost += edges[i].weight;
        nrEdges++;
    }
    return MSTcost;
}

int main() {
    int n, m;

    cin >> n >> m;
    vector<int> a(m);
    vector<int> b(m);
    vector<int> c(m);

    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
        edges[i].src = a[i];
        edges[i].dest = b[i];
        edges[i].weight = c[i];
    }

    // initializare parinte
    InitializareParinte(n);

    // fac sortarea in functie de cost
    sort(edges, edges + m, cmp);

    int MSTcost = 0;
    for (int i = 0; i < m; i++) {
        MSTcost = union1(i, MSTcost);
    }

    cout << MSTcost << " ";

    // pentru a salva al doilea cel mai scurt arbore partial
    int secondBestMST = INT_MAX;
    MSTcost = 0;
    int j;

    // parcurgem toate muchiile din primul APM
    for (j = 0; j < presentInMST.size(); j++) {
        InitializareParinte(n);
        nrEdges = 0;
        for (int i = 0; i < m; i++) {
            // excludem pe rand cate o muchie din APM
            // si formam APM cu muchiile ramase
            if (i == presentInMST[j]) {
                continue;
            }
            MSTcost = union2(i, MSTcost);

        }
        // verific daca numarul de muchii este (n - 1)
        if (nrEdges != n - 1) {
            MSTcost = 0;
            continue;
        }

        // salvez second best MST
        if (secondBestMST > MSTcost) {
            secondBestMST = MSTcost;
        }
        MSTcost = 0;
    }

    cout << secondBestMST << endl;

    return 0;
}

//input :
// 4 4
//1 2 2
//1 4 5
//1 3 4
//2 3 3

//output : 10 11