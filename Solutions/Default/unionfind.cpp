#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> pointers(1000000);
vector<int> sizes(1000000,1);

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
    } else if(sizes[x] < sizes[y]) {
        pointers[x] = y;
    } else {
        pointers[y] = x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;

    for(int i = 0; i < 1000000; i++) {
        pointers[i] = i;
    }
    string out = "";
    for(int i = 0; i < q; i++) {
        char type;
        int first, second;
        cin >> type >> first >> second;
        if(type == '?') {
//            cout << (find(first)== find(second) ? "yes" : "no") << endl;
            out.append(find(first) == find(second) ? "yes" : "no");
            out.append("\n");
        } else {
            unify(first,second);
        }
    }
    cout << out;
    return 0;
}