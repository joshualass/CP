#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
vector<int> t(0);

void printV(vector<int> x) {
    for(int y : x) {
        cout << y << ' ';
    }
    cout << '\n';
}

void printM(map<int,int> x) {
    for(pair<int,int> y : x) {
        cout << y.first << ' ' << y.second << '\n';
    }
}

void build() {
    for(int i = n - 1; i > 0; --i) {
        t[i] = t[i * 2] + t[i * 2 +1];
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = t[p] + t[p ^ 1];
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    while(l < r) {
        if(l % 2 == 1) {
            ans += t[l];
            l++;
        }
        if(r % 2 == 1) {
            r--;
            ans += t[r];
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc = 0;
    cin >> tc;
    while(tc-->0) {
        int m, r;
        cin >> m >> r;
        n = m + r;
        t.resize(n * 2);
        string out = "";
        map<int, int> indexes;
        for(int i = n; i < n + m; i++) {
            t[i] = 1;
        }
        for(int i = 0; i < m; i++) {
            indexes.insert({m - i, i});
        }
        // printM(indexes);
        build();
        int count = 0;
        for(int i = 0; i < r; i++) {
            int num; // # movie to move to end
            cin >> num;
            int index = indexes[num];
            out += to_string(query(index + 1, m + count)) + " ";
            // cout << "query: " << index + 1 << " " << m + count << " value: " << query(index, m + count) << '\n';
            modify(index, 0 );
            modify(m + count, 1);
            indexes[num] = m + count;
            count++;
        }
        // printV(t);
        cout << out << '\n';
    }
    

    return 0;
}