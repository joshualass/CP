#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

struct pent {
    array<int,5> nodes, edges;

    pent(array<int,5> n, array<int,5> e) {
        nodes = n;
        edges = e;
    }

    vector<array<int,2>> get_type_edges(int type) {
        auto start_idx = [&](int os) -> vector<array<int,2>> {
            vector<array<int,2>> res;
            for(int i = 0; i < 5; i++) {
                if(edges[(i + os) % 5] == type) {
                    res.push_back({nodes[(i+os)%5], nodes[(i+os+1)%5]});
                    i++;
                }
            }
            return res;
        };
        vector<array<int,2>> res = start_idx(0);
        for(int i = 0; i < 5; i++) {
            if(start_idx(i).size() > res.size()) res = start_idx(i);
        }
        return res;
    }

    int type_cnt(int type) {
        return get_type_edges(type).size();
    }
};

void solve() {
    
    int n; cin >> n;
    int p = n / 5;
    int left = n - p * 5;
    int bars = left / 2;

    int k = max(p + p / 2 + (bars + 1) / 2, p + (p + 1) / 2 + bars / 2);
    cout << k << '\n';

    auto query = [&](int i, int j) -> int {
        cout << "? " << i + 1 << " " << j + 1 << endl;
        int t; cin >> t;
        return t;
    };

    array<vector<array<int,2>>,2> pairings = {};
    for(int i = 0; i < p * 2 + bars; i++) {
        pairings[query(i * 2, i * 2 + 1)].push_back({i*2,i*2+1});
    }

    vector<pent> pents;
    array<int,2> type_cnts = {0,0};

    int i = (p * 2 + bars) * 2;
    while(pairings[0].size() && pairings[1].size()) {
        array<int,5> b = {pairings[0].back()[0], pairings[0].back()[1], pairings[1].back()[0], pairings[1].back()[1], i};
        // cout << "b : " << b << '\n';
        int c = query(b[1],b[2]);
        int d = query(b[3], b[4]);
        int e = query(b[4], b[0]);
        pents.push_back(pent(b, {0,c,1,d,e}));
        for(int j = 0; j < 2; j++) type_cnts[j] += pents.back().type_cnt(j);
        pairings[0].pop_back();
        pairings[1].pop_back();
        i++;
    }

    for(int j = 0; j < 2; j++) {
        type_cnts[j] += pairings[j].size();
        if(type_cnts[j] >= k) {
            cout << "! ";
            vector<array<int,2>> res;
            for(pent p : pents) {
                vector<array<int,2>> toadd = p.get_type_edges(j);
                for(auto edge : toadd) res.push_back(edge);
            }
            for(auto edge : pairings[j]) res.push_back(edge);
            for(int l = 0; l < k; l++) {
                cout << res[l][0] + 1 << " " << res[l][1] + 1 << " ";
            }
            cout << endl;
            return;
        }    
    }
    assert(0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}