// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;
// const int MAXN = 18;

// int pc[(1 << MAXN) + 1];
// int p[(1 << MAXN) + 1];



// int ask(int L, int R) { //querying range [l,r)
//     int l = min(L,R);
//     int r = max(L,R);
//     cout << "l : " << l << " r : " << r << endl;
//     int i = 0;
//     int cnt = 1;
//     while(cnt != r - l) {
//         i++;
//         cnt *= 2;
//     }
//     int j = l / cnt;
//     cout << "? " << i << " " << j << endl;
//     int res; cin >> res;
//     return res;
// }

// int solve(int length, int offset, int mult, int include) {
//     // cout << "length : " << length << " offset : " << offset << " mult : " << mult << " include : " << include << endl;
//     if(length == 0) return 0;
//     int D = p[length];
//     int d = 1 << D;
//     int l = offset;
//     int r = offset + d * mult;
//     int res = ask(l,r);
//     if(!include) res = 100 - res;
//     if(d > length) {
//         return res + solve(d - length, offset + d * mult, mult * -1, include ^ 1);
//     } else {
//         return res + solve(length - d, offset + d * mult, mult, include);
//     }
// }

// int solvecnt(int length, int offset, int mult, int include) {
//     // cout << "length : " << length << " offset : " << offset << " mult : " << mult << " include : " << include << endl;
//     if(length == 0) return 0;
//     int D = p[length];
//     int d = 1 << D;
//     if(d > length) {
//         return 1 + solvecnt(d - length, offset + d * mult, mult * -1, include ^ 1);
//     } else {
//         return 1 + solvecnt(length - d, offset + d * mult, mult, include);
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     fill(begin(pc),end(pc),-1);
//     fill(begin(p), end(p), -1);

//     pc[0] = 0;

//     for(int i = 1; i <= 1 << MAXN; i++) {
//         for(int d = MAXN; d >= 0; d--) {
//             int to = abs(i - (1 << d));
//             if(pc[to] != -1 && (pc[i] == -1 || pc[to] + 1 < pc[i])) {
//                 pc[i] = pc[to] + 1;
//                 p[i] = d;
//             }
//         }
//     }

//     int n, l, r; cin >> n >> l >> r;
//     int try1 = 0, try2 = 0;
//     {
//         int pivot = -1, d = -1;
//         for(int i = l; i <= r; i++) {
//             int currd = 1;
//             int curri = i;
//             for(int i = 0; i < 3; i++) {
//                 if(curri % 2 == 0) {
//                     curri /= 2;
//                     currd *= 2;
//                 }
//             }
//             if(currd > d) {
//                 pivot = i;
//                 d = currd;
//             }
//         }
//         int lhs = solvecnt(pivot - l, pivot, -1, 1);
//         int rhs = solvecnt(r - pivot + 1, pivot, 1, 1);
//         try1 = lhs + rhs;
//     }

//     {
//         int D = r - l + 1;
//         int d = 1;
//         while(d * 2 <= D) d *= 2;
//         d *= 2;
//         int lopiv = l / d * d;
//         // cout << "d : " << d << " lopiv : " << lopiv << endl;
//         int res = 1;
//         int lhslength = l - lopiv;
//         int rhslength = (lopiv + d) - r - 1;
//         int lhs = solvecnt(lhslength, l, 1, 0);
//         int rhs = solvecnt(rhslength, lopiv + d - 1, -1, 0);
//         // cout << "lhs length : " << lhslength << " rhs length : " << rhslength << endl;
//         // cout << "res : " << res << " lhs : " << lhs << " rhs : " << rhs << endl;
//         try2 = res + lhs + rhs;
//     }

//     // cout << "try1 : " << try1 << " try2 : " << try2 << endl;

//     if(try1 < try2) {
//         int pivot = -1, d = -1;
//         for(int i = l; i <= r; i++) {
//             int currd = 1;
//             int curri = i;
//             for(int i = 0; i < 3; i++) {
//                 if(curri % 2 == 0) {
//                     curri /= 2;
//                     currd *= 2;
//                 }
//             }
//             if(currd > d) {
//                 pivot = i;
//                 d = currd;
//             }
//         }
//         // cout << "d : " << d << " pivot : " << pivot << endl;

//         // cout << "solving lhs" << endl;

//         int lhs = solve(pivot - l, pivot, -1, 1);
//         // cout << "lhs is : " << lhs << endl;
//         // cout << "solving rhs" << endl;
//         int rhs = solve(r - pivot + 1, pivot, 1, 1);
//         // cout << "rhs is : " << rhs << endl;
//         int res = lhs + rhs;
//         cout << "! " << res % 100 << endl;
//     } else {
//         int D = r - l + 1;
//         int d = 1;
//         while(d * 2 <= D) d *= 2;
//         d *= 2;
//         int lopiv = l / d * d;

//         int res = ask(lopiv, lopiv + d);
//         int lhslength = l - lopiv;
//         int rhslength = (lopiv + d) - r - 1;
//         int lhs = solve(lhslength, lopiv, 1, 0);
//         int rhs = solve(rhslength, lopiv + d, -1, 0);
//         cout << "! " << (res + lhs + rhs) % 100 << endl;
//     }

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int ask(int L, int R) { //querying range [l,r)
    int l = min(L,R);
    int r = max(L,R);
    // cout << "l : " << l << " r : " << r << endl;
    int i = 0;
    int cnt = 1;
    while(cnt != r - l) {
        i++;
        cnt *= 2;
    }
    int j = l / cnt;
    cout << "? " << i << " " << j << endl;
    int res; cin >> res;
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, l, r; cin >> n >> l >> r;
    // cout << "test" << endl;
    int nn = 1 << n;
    //build adj list
    vector<vector<int>> adj(nn + 1);
    for(int d = 1; d <= nn; d *= 2) {
        for(int j = 0; j < nn; j += d) {
            int l = j, r = j + d;
            adj[l].push_back(r);
            adj[r].push_back(l);
        }
    }
    
    //BFS from l to assign p
    vector<int> p(nn+1,-1);
    queue<int> q;
    
    q.push(l);
    while(q.size()) {
        int i = q.front();
        q.pop();
        for(int to : adj[i]) {
            if(p[to] == -1 && to != l) {
                p[to] = i;
                q.push(to);
            }
        }
    }
    
    // cout << "p : " << p << endl;
    int curr = r+1;
    int ans = 0;
    while(p[curr] != -1) {
        int l = curr, r = p[curr];
        int res = ask(l,r);
        if(l > r) {
            ans += 100 - res;
        } else {
            ans += res;
        }
        curr = p[curr];
    }
    
    cout << "! " << (200 - (ans % 100)) % 100 << '\n';

    return 0;
}