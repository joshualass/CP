#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

struct Node {
    ull len;
    vector<int> ch;
    Node(): len(0) {}
    Node(ull len, vector<int> ch): len(len), ch(ch) {}
};

vector<Node> nodes;

Node get_node(vector<int> ch) {
    ull len = 0;
    for(int c : ch) len += nodes[c].len;
    return Node(len, ch);
}

vector<int> idxs;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    nodes.push_back(Node(1, {0}));
    idxs.push_back(0);
    nodes.push_back(Node(1, {1}));
    idxs.push_back(1);
    int q; cin >> q;

    auto create = [&](vector<int> ch) -> int {
        if(ch.size() == 1) return ch[0];
        nodes.push_back(get_node(ch));
        return nodes.size() - 1;
    };

    auto add = [&](int l, int r) -> void {
        vector<int> chs;
        vector<ull> lens;
        ull tl = 0;

        for(int ch : nodes[idxs[l]].ch) {
            if(tl >= 1e18) break;
            chs.push_back(ch);
            lens.push_back(nodes[ch].len);
            tl += nodes[ch].len;
        }

        for(int ch : nodes[idxs[r]].ch) {
            if(tl >= 1e18) break;
            chs.push_back(ch);
            lens.push_back(nodes[ch].len);
            tl += nodes[ch].len;
        }

        vector<int> resch;

        if(chs.size() <= 3) {
            resch = chs;
        } else {
            int bi = -1, bj = -1, bk = -1;
            ull ml = ULLONG_MAX;

            for(int i = 1; i < chs.size(); i++) {
                for(int j = i + 1; j < chs.size(); j++) {
                    for(int k = j + 1; k < chs.size(); k++) {
                        ull tl = max({accumulate(lens.begin(), lens.begin() + i, 0LL), accumulate(lens.begin() + i, lens.begin() + j, 0LL), accumulate(lens.begin() + j, lens.begin() + k, 0LL), accumulate(lens.begin() + k, lens.end(), 0LL)});
                        if(tl < ml) {
                            ml = tl;
                            bi = i, bj = j, bk = k;
                        }
                    }
                }
            }

            resch.push_back(create(vector<int>(chs.begin(), chs.begin() + bi)));
            resch.push_back(create(vector<int>(chs.begin() + bi, chs.begin() + bj)));
            resch.push_back(create(vector<int>(chs.begin() + bj, chs.begin() + bk)));
            resch.push_back(create(vector<int>(chs.begin() + bk, chs.end())));
        }

        // cout << "l : " << l << " r : " << r << " chs : " << chs << " lens : " << lens << " resch : " << resch << '\n';

        idxs.push_back(create(resch));

    };

    auto query = [&](auto self, int idx, ll x) -> int {
        // cout << "idx : " << idx << " x : " << x << " len here : " << nodes[idx].len << '\n';
        if(idx <= 1) return idx;
        for(int ch : nodes[idx].ch) {
            if(x < nodes[ch].len) {
                return self(self, ch, x);
            }
            x -= nodes[ch].len;
        }
        assert(0);
    };

    for(int i = 0; i < q; i++) {
        ll l, r, x; cin >> l >> r >> x;
        add(l, r);
        cout << query(query, idxs.back(), x - 1) << '\n';
    }

    return 0;
}
