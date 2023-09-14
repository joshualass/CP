#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int SIZE = 1e6;

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
    
    

    return 0;
}