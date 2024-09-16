#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<ll> correct = {8, 8, 24, 24};
vector<array<int,3>> chandler(8,{-1,-1,-1});

void iscube(vector<array<int,3>> &coords) {
    vector<pair<ll,int>> dists;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            ll dist = 1LL * (coords[i][0] - coords[j][0]) * (coords[i][0] - coords[j][0]) + 1LL * (coords[i][1] - coords[j][1]) * (coords[i][1] - coords[j][1]) + 1LL * (coords[i][2] - coords[j][2]) * (coords[i][2] - coords[j][2]);
            int found = 0;
            for(auto &p : dists) {
                if(p.first == dist) {
                    p.second++;
                    found = 1;
                }
            }
            if(!found) {
                if(dists.size() == 4) {
                    return;
                } else {
                    dists.push_back({dist,1});
                }
            }
        }
    }

    if(dists.size() != 4) return;
    sort(dists.begin(), dists.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second < rhs.second;
    });

    for(int i = 0; i < 4; i++) {
        if(correct[i] != dists[i].second) return;
    }

    chandler = coords;

}

void recur(vector<array<int,3>> &coords, vector<array<int,3>> &curr, int d) {
    if(d == 8) {
        iscube(curr);
        return;
    }

    auto [a,b,c] = coords[d];
    curr[d] = {a,b,c};
    recur(coords,curr,d+1);
    curr[d] = {a,c,b};
    recur(coords,curr,d+1);
    curr[d] = {b,a,c};
    recur(coords,curr,d+1);
    curr[d] = {b,c,a};
    recur(coords,curr,d+1);
    curr[d] = {c,a,b};
    recur(coords,curr,d+1);
    curr[d] = {c,b,a};
    recur(coords,curr,d+1);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<array<int,3>> coords(8);
    for(auto &a : coords) for(auto &x : a) cin >> x;
    vector<array<int,3>> dummy(8);
    recur(coords,dummy,0);

    if(chandler[0][0] != -1) {
        cout << "YES\n";
        for(auto x : chandler) {
            for(auto y : x) {
                cout << y << " ";
            }
            cout << '\n';
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}