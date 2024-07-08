#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (int i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (int i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i + 1< vec.size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

struct Trie {
    const int depth = 31;
    struct Node {
        array<int,2> a;
        int cnt;
        set<int> s;
        Node() {
            a = {-1,-1};
        }
    };
    vector<Node> nodes;

    Trie () {
        nodes.push_back(Node());
    }

    void insert(int num, int idx) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] == -1) {
                nodes[curr].a[bit] = nodes.size();
                nodes.push_back(Node());
            }
            curr = nodes[curr].a[bit];
            nodes[curr].s.insert(idx);
        }
    }

    //querying the indicies such that the bitwise xor is < k
    array<int,2> query(int num, int idx, int k) {
        array<int,2> res = {INT_MIN, INT_MAX}; //nearest indices below and above such that num ^ x < k
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = (((num >> i) & 1) ^ 1); //go to this bit to add 1 << i

            if((k >> i) & 1) { //this bit is set for k
                if(nodes[curr].a[bit ^ 1] != -1) { //we have the option use numbers in bit ^ 1
                    set<int> &s = nodes[nodes[curr].a[bit ^ 1]].s;
                    if(s.upper_bound(idx) != s.end()) {
                        res[1] = min(res[1], *s.upper_bound(idx));
                    }
                    if(s.lower_bound(idx) != s.begin()) {
                        res[0] = max(res[0], (*--s.lower_bound(idx)));
                    }
                }
                if(nodes[curr].a[bit] != -1) { //always follow k
                    curr = nodes[curr].a[bit];
                } else {
                    return res;
                }
            } else {//can't check the numbers above us ever
                if(nodes[curr].a[bit ^ 1] != -1) { //always follow k
                    curr = nodes[curr].a[bit ^ 1];
                } else {
                    return res;
                }
            }
        }

        return res;
    }
};

vector<array<int,2>> rangesnocompileerrorplease(200000);

void solve() {
    ll n, k; cin >> n >> k;

    Trie t;
    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        t.insert(a[i],i);
    }

    auto count_smaller = [&](int m) {
        int p = 0;
        for(int i = 0; i < n; i++) {
            array<int,2> b = t.query(a[i], i, m);
            if(b[0] != INT_MIN) {
                // rangesnocompileerrorplease.push_back({b[0],i});
                rangesnocompileerrorplease[p++] = {b[0],i};
            }
            if(b[1] != INT_MAX) {
                // rangesnocompileerrorplease.push_back({i,b[1]});
                rangesnocompileerrorplease[p++] = {i,b[1]};
            }
        }

        sort(rangesnocompileerrorplease.begin(), rangesnocompileerrorplease.begin() + p, [](const auto &lhs, const auto &rhs) {
            return lhs[1] < rhs[1];
        });

        // cout << "rangesnocompileerrorplease : " << rangesnocompileerrorplease << '\n';

        int p2 = 0;
        ll smaller = 0;
        for(int i = 0; i < n; i++) {
            while(p2 != p && rangesnocompileerrorplease[p2][0] < i) p2++;
            if(p2 != p) {
                // cout << "sz : " << rangesnocompileerrorplease.size() << " p : " << p << endl;
                smaller += n - rangesnocompileerrorplease[p2][1];
            }
        }

        // cout << "m : " << m << " smaller : " << smaller << '\n';

        return smaller;

    };

    // for(int i = 0; i < 16; i++) {
    //     cout << "cs i : " << i << " " << count_smaller(i) << '\n';
    // }
    k--;
    ll l = 0, r = 1073741823;

    while(l != r) {
        ll m = (l + r + 1) / 2;
        // cout << "l : " << l << " r : " << r << " m : " << m << '\n';
        
        ll smaller = count_smaller(m);

        if(smaller > k) {
            r = m - 1;
        } else {
            l = m;
        }
    }

    cout << l << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}