#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

ifstream fin("top.in");
ofstream gout("top.out");

const int nmax = 100000;
vector<int> g[nmax + 1];
vector<int> top;
vector<int> inStack(nmax + 1, 0);  // daca nodul este in stack ul dfs curent
vector<int> visited(nmax + 1, 0);
stack<int> stk;
vector<int> circuit;

bool dfs(int node) {
    visited[node] = 1;
    inStack[node] = 1;
    stk.push(node);

    for (int next : g[node]) {
        if (!visited[next]) {
            if (dfs(next)) {
                return true;
            }
        } else if (inStack[next]) {
            // Cycle detected
            while (!stk.empty()) {
                circuit.push_back(stk.top());
                if (stk.top() == next) {
                    break;
                }
                stk.pop();
            }

            reverse(circuit.begin(), circuit.end());

            return true;
        }
    }

    inStack[node] = 0;
    stk.pop();
    top.push_back(node);

    return false;
}

int main() {
    int n, m;
    fin >> n >> m;

    while (m--) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (dfs(i)) {
                for (int i : circuit) {
                    gout << i << ' ';
                }
                return 0;
            }
        }
    }

    // daca nu exista ciclu, printeaza ordinea topologica
    for (int i = top.size() - 1; i >= 0; i--) {
        gout << top[i] << ' ';
    }

    return 0;
}
