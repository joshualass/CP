#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> pointers(10000);
vector<int> sizes(10000,1);
vector<int> debts(10000);

int find(int x) {
    if(pointers[x] == x) {
        return x;
    } else {
        pointers[x] = find(pointers[x]);
        return pointers[x];
    }
}

void unify(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        pointers[y] = x;
        sizes[x]++;
        debts[x] += debts[y];
    } else if(sizes[x] < sizes[y]) {
        pointers[x] = y;
        debts[y] += debts[x];
    } else {
        pointers[y] = x;
        debts[x] += debts[y];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        debts[i] = a;
    }
    for(int i = 0; i < 10000; i++) {
        pointers[i] = i;
    }
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        unify(a,b);
    }
    bool poss = true;
    for(int i = 0; i < n; i++) {
        if(debts[find(i)] != 0) {
            poss = false;
        }
    }
    cout << (poss ? "POSSIBLE" : "IMPOSSIBLE");
    return 0;
}