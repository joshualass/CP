#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int SIZE = 2e6 + 1;

vector<int> pointers(SIZE);
vector<int> sizes(SIZE,1);

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
    if(sizes[x] == sizes[y]) {
        pointers[y] = x;
        sizes[x]++;
    } else if(sizes[x] < sizes[y]) {
        pointers[x] = y;
    } else {
        pointers[y] = x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < SIZE; i++) {
        pointers[i] = i;
    }

    for(int i = 0; i < m; i++) {

        int l, r;
        cin >> l >> r;
        unify(l,r);
    }
    string out = "";
    bool flag = true;
    for(int i = 1; i <= n; i++) {
        if(find(i) != find(1)) {
            out += to_string(i) + "\n";
            flag = false;
        }    
    }
    cout << out;
    if(flag) {
        cout << "Connected";
    }
    return 0;
}