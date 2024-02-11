// Fişierul cuvinte.in conţine cuvinte separate prin spaţiu. Se citeşte de la tastatură un număr natural k
//Să se împartă cuvintele din fişier în k clase (categorii) nevide  astfel încât
// gradul de separare al claselor să fie maxim ( = distanţa minimă între două cuvinte din clase diferite);
// se vor afişa pe câte o linie cuvintele din fiecare clasă și pe o altă linie gradul de separare al claselor.

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

ifstream fin("clustering.in");

int min(int a, int b, int c) {
    return min(min(a, b), c);
}

int levenshteinDistance(const string& word1, const string& word2) {
    // lungimile cuvintelor
    int m = word1.length();
    int n = word2.length();

    // Creez matricea pentru a stoca distantele
    vector<vector<int>> distances(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Initializez primul rand
            if (i == 0) {
                distances[i][j] = j;
            // Initializez prima coloana
            } else if (j == 0) {
                distances[i][j] = i;
            } else if (word1[i - 1] == word2[j - 1]) { // Daca sunt egale
                distances[i][j] = distances[i - 1][j - 1];
            } else {
                distances[i][j] = 1 + min(distances[i - 1][j],      // Stergere
                                        distances[i][j - 1],        // Inserare
                                        distances[i - 1][j - 1]);   // Modificare
            }
        }
    }

    // Returnez valoarea din coltul dreapta-jos al matricei
    // Reprezinta distanta Levenshtein dintre word1 si word2
    return distances[m][n];
}

int find(vector<int>& parent, int i) {
    if(parent[i] != i)
        // cautam parintele pana ajungem la radacina
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

//determina daca avem ciclu
void Union(vector<int>& parent, vector<int>& rank, int x, int y) {
    // cautam parintii lui x si y
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    // componenta mai mica se alatura componentei mai mari
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    // daca au aceeasi adancime nu este relevant felul in care
    // se alatura, iar adancimea va creste
    else if (xroot != yroot) {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void Clustering(vector<string> words, int k) {

    int n = words.size();

    // Calculez distantele pentru fiecare pereche de cuvinte folosind levenshtein
    vector<vector<int>> distances(n, vector<int>(n));
    vector<vector<int>> edgeList;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            distances[i][j] = levenshteinDistance(words[i], words[j]);
            distances[j][i] = distances[i][j];
            edgeList.push_back({distances[i][j], i, j});
        }
    }

    sort(edgeList.begin(), edgeList.end());

    vector<int> rank(n, 0);
    // cost MST
    int total_cost = 0;
    // numar total muchii
    int no_edges = 0;

    vector<vector<int>> resulted_mst;
    // la inceput fiecare cuvant e o clasa
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int m = edgeList.size();

    for (int i = 0; i < m; i++) {
        // gasim parintele primului varf
        int x = find(parent, edgeList[i][1]);
        // gasim parintele celui de-al doilea varf
        int y = find(parent, edgeList[i][2]);

        // daca parintii sunt diferiti
        // (adica nu fac parte din aceeasi componenta conexa/acelasi grup)
        if (x != y) {
            // se adauga muchia in MST
            resulted_mst.push_back({edgeList[i][1], edgeList[i][2], edgeList[i][0]});
            total_cost += edgeList[i][0];
            Union(parent, rank, x, y);
            no_edges += 1;
            // o singura componenta conexa
            if (no_edges == (n - k)) {
                break;
            }
        }
    }



    vector<vector<int>> clusterList(n);

//afisarea claselor cu cuvinte
    for (int i = 0; i < n; i++) {
        if (parent[i] != - 1) {
            cout<< words[i] << " ";
            clusterList[parent[i]].push_back(i);
            for (int j = i + 1; j < n; j++) {
                if (parent[i] == parent[j]) {
                    cout << words[j] << " ";
                    clusterList[parent[i]].push_back(j);
                    parent[j] = -1;
                }
            }
            cout << endl;
            parent[i] = -1;
        }
    }

    int minFinalDistance = numeric_limits<int>::max();

    //distanta minima de separare
    for (int i = 0; i < clusterList.size(); ++i) {
        for (int j = i + 1; j < clusterList.size(); ++j) {
            int distance = numeric_limits<int>::max();

            for (int word1 : clusterList[i]) {
                for (int word2 : clusterList[j]) {
                    if (distances[word1][word2] < distance) {
                        distance = distances[word1][word2];
                    }
                }
            }

            if (distance < minFinalDistance) {
                minFinalDistance = distance;
            }
        }
    }

    cout << minFinalDistance;

}

int main() {
    vector<string> words;
    string newWord;

    while (fin >> newWord) {
        words.push_back(newWord);
    }

    int k ;
    cin>>k;

    Clustering(words, k);
    return 0;
}