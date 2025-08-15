#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
nice computer-science (not math) problem. 
the first attempt was to try to maintain 3 pointers, such that each of them point to nodes that reduce the length of the string by half. However, this was adding too many intermediate nodes and wasn't compressing anything. 
The solution idea came when we thought about merging a smaller and a larger piece. For the smaller piece, we are able to have a pointer as it will always be less than or equal to half. For the larger piece, there could be a lot. 
Then, we drew inspiration from the HLD algorithm, where we do binary lifting on the large pieces and the depth is at most Q. 
Then, for the queries, we see how far up in the large pieces using BLG and then go to the small piece otherwise and repeat. 
Have heavy parent which is longer in size and then have light children. 

TODO - read up on Weighted Balanced Leafy Tree ????

*/

const int LN = 20;
const ll inf = 1e18;

int blg_pt[500002][LN], small_pt[500002];
ll blg[500002][LN][2], lens[500002];

void init() {
    for(int k = 0; k < 2; k++) {
        lens[k] = 1;
        for(int i = 0; i < LN; i++) {
            blg_pt[k][i] = k;
            blg[k][i][1] = 1;
        }
    }
}

void add(int idx, int lidx, int ridx) {
    ll l_len = lens[lidx], r_len = lens[ridx];
    lens[idx] = min(l_len + r_len, inf);
    ll curl, curr;
    int curp;
    if(l_len < r_len) {
        small_pt[idx] = lidx;
        curl = l_len, curr = l_len + r_len;
        curp = ridx;
    } else {
        small_pt[idx] = ridx;
        curl = 0, curr = l_len;
        curp = lidx;
    }
    for(int i = 0; i < LN; i++) {
        if(i) {
            ll nl = blg[curp][i-1][0], nr = blg[curp][i-1][1];
            curl = min(curl + nl, inf);
            curr = min(curl + (nr - nl), inf);
            curp = blg_pt[curp][i-1];
        }
        blg_pt[idx][i] = curp;
        blg[idx][i][0] = curl;
        blg[idx][i][1] = curr;
    }
}

int query(int idx, ll x) {
    if(idx <= 1) return idx;
    for(int i = LN - 1; i >= 0; i--) {
        if(blg[idx][i][0] <= x && x < blg[idx][i][1]) {
            return query(blg_pt[idx][i], x - blg[idx][i][0]);
        }
    }
    if(blg[idx][0][0]) {
        return query(small_pt[idx], x);
    } else {
        return query(small_pt[idx], x - blg[idx][0][1]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll l, r, x; cin >> l >> r >> x;
        x--;
        add(i + 2, l, r);
        cout << query(i + 2, x) << '\n';
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef unsigned long long ull;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// struct Node {
//     ull len;
//     vector<int> ch;
//     Node(): len(0) {}
//     Node(ull len, vector<int> ch): len(len), ch(ch) {}
// };

// vector<Node> nodes;

// Node get_node(vector<int> ch) {
//     ull len = 0;
//     for(int c : ch) len += nodes[c].len;
//     return Node(len, ch);
// }

// vector<int> idxs;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     nodes.push_back(Node(1, {0}));
//     idxs.push_back(0);
//     nodes.push_back(Node(1, {1}));
//     idxs.push_back(1);
//     int q; cin >> q;

//     auto create = [&](vector<int> ch) -> int {
//         if(ch.size() == 1) return ch[0];
//         nodes.push_back(get_node(ch));
//         return nodes.size() - 1;
//     };

//     auto add = [&](int l, int r) -> void {
//         vector<int> chs;
//         vector<ull> lens;
//         ull tl = 0;

//         for(int ch : nodes[idxs[l]].ch) {
//             if(tl >= 1e18) break;
//             chs.push_back(ch);
//             lens.push_back(nodes[ch].len);
//             tl += nodes[ch].len;
//         }

//         for(int ch : nodes[idxs[r]].ch) {
//             if(tl >= 1e18) break;
//             chs.push_back(ch);
//             lens.push_back(nodes[ch].len);
//             tl += nodes[ch].len;
//         }

//         vector<int> resch;

//         if(chs.size() <= 3) {
//             resch = chs;
//         } else {
//             int bi = -1, bj = -1, bk = -1;
//             ull ml = ULLONG_MAX;

//             for(int i = 1; i < chs.size(); i++) {
//                 for(int j = i + 1; j < chs.size(); j++) {
//                     for(int k = j + 1; k < chs.size(); k++) {
//                         ull tl = max({accumulate(lens.begin(), lens.begin() + i, 0LL), accumulate(lens.begin() + i, lens.begin() + j, 0LL), accumulate(lens.begin() + j, lens.begin() + k, 0LL), accumulate(lens.begin() + k, lens.end(), 0LL)});
//                         if(tl < ml) {
//                             ml = tl;
//                             bi = i, bj = j, bk = k;
//                         }
//                     }
//                 }
//             }

//             resch.push_back(create(vector<int>(chs.begin(), chs.begin() + bi)));
//             resch.push_back(create(vector<int>(chs.begin() + bi, chs.begin() + bj)));
//             resch.push_back(create(vector<int>(chs.begin() + bj, chs.begin() + bk)));
//             resch.push_back(create(vector<int>(chs.begin() + bk, chs.end())));
//         }

//         // cout << "l : " << l << " r : " << r << " chs : " << chs << " lens : " << lens << " resch : " << resch << '\n';

//         idxs.push_back(create(resch));

//     };

//     auto query = [&](auto self, int idx, ll x) -> int {
//         // cout << "idx : " << idx << " x : " << x << " len here : " << nodes[idx].len << '\n';
//         if(idx <= 1) return idx;
//         for(int ch : nodes[idx].ch) {
//             if(x < nodes[ch].len) {
//                 return self(self, ch, x);
//             }
//             x -= nodes[ch].len;
//         }
//         assert(0);
//     };

//     for(int i = 0; i < q; i++) {
//         ll l, r, x; cin >> l >> r >> x;
//         add(l, r);
//         cout << query(query, idxs.back(), x - 1) << '\n';
//     }

//     return 0;
// }
