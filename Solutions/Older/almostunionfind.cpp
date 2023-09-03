#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    cout << " --- vector --- \n";
    for(int i = 0; i < 5; i++) {
        cout << x[i] << " ";
    }
    cout << "\n";
}

const int SIZE = 200000;

vector<int> pointers(SIZE);
vector<int> sizes(SIZE,1);
vector<int> counts(SIZE,1);
vector<int> sums(SIZE,1);

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
        counts[x] += counts[y];
        sums[x] += sums[y];
    } else if(sizes[x] < sizes[y]) {
        pointers[x] = y;
        counts[y] += counts[x];
        sums[y] += sums[x];
    } else {
        pointers[y] = x;
        counts[x] += counts[y];
        sums[x] += sums[y];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < SIZE; i++) {
        pointers[i] = i;
        sums[i] = i + 1;
    }

    int n, m; cin >> n >> m;
    map<int,int> index;
    int next = 100000;
    for(int i = 0; i < n; i++) {
        index[i] = i;
    }
    for(int i = 0; i < m; i++) {
        int op; cin >> op;
        if(op == 1) {
            int a, b; cin >> a >> b;
            unify(index[--a],index[--b]);
        } else if(op == 2) {
            int a, b; cin >> a >> b;
            if(find(index[--a]) == find(index[--b])) {
                continue;
            }
            sums[find(index[a])] -= a+1;
            counts[find(index[a])]--;
            sums[next] = a + 1;
            index[a] = next++;
            unify(index[a],index[b]);

        } else {
            int a; cin >> a;
            cout << counts[find(index[--a])] << " " << sums[find(index[a])] << "\n";
        }
        // cout << "new operation:\n";
        // cout << "pointers:";
        // printV(pointers);
        // cout << "sizes:";
        // printV(sizes);
        // cout << "counts:";
        // printV(counts);
        // cout << "sums:";
        // printV(sums);
    }


    return 0;
}