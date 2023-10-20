//https://acm.timus.ru/problem.aspx?space=1&num=1671
#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e5;
int dsu[N];
int depths[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    int n, m; cin >> n >> m;
    vector<pair<int,int>> v(m);
    for(int i = 0;i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        v[i] = {a,b};
    }

    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }

    int q; cin >> q;
    vector<int> nagasaki(q);
    vector<bool> hiroshima(m);
    for(int i = 0; i < q; i++) {
        int num; cin >> num;
        num--;
        hiroshima[num] = true;
        nagasaki[i] = num;
    }
    int comps = n;
    for(int i = 0; i < m; i++) {
        if(!hiroshima[i]) {
            if(find(v[i].first) != find(v[i].second)) comps--;

            merge(v[i].first, v[i].second);
        }
    }
    vector<int> ans(0);
    while(nagasaki.size()) {
        ans.push_back(comps);
        int i = nagasaki.back();
        nagasaki.pop_back();

        if(find(v[i].first) != find(v[i].second)) {
            comps--;
        }
        merge(v[i].first,v[i].second);
    }
    reverse(ans.begin(),ans.end());
    for(auto x : ans) cout << x << " ";

    return 0;
}