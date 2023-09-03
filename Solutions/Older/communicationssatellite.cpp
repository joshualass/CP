#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<int> dsu;

int find(int x) {
    if(x == dsu[x]) {
        return x;
    } else {
        dsu[x] = find(dsu[x]);
        return dsu[x];
    }
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    dsu[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> satellites(n,vector<int>(3));
    dsu.assign(n,-1);
    for(int i = 0; i < n; i++) {
        int a, b, c; cin >> a >> b >> c; //X, Y, R
        satellites[i] = {a,b,c};
        dsu[i] = i;
    }
    priority_queue<vector<ld>, vector<vector<ld>>, greater<vector<ld>>> pq;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            vector<int> first = satellites[i];
            vector<int> second = satellites[j];
            ld distance = sqrt(pow((ld)first[0] - second[0],2) + pow((ld)first[1] - second[1],2)) - first[2] - second[2];
            pq.push({distance, i, j});
        }
    }
    ld beam = 0;
    while(pq.size()) {
        vector<ld> p = pq.top();
        pq.pop();
        if(find((int)p[1]) != find((int)p[2])) {
            beam += p[0];
            merge((int)p[1],(int)p[2]);
        }
    }
    cout << fixed << setprecision(10) << beam << "\n";
    return 0;
}