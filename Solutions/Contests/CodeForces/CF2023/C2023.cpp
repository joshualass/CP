#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> kmp(vector<int> s) {
    int n = s.size();
    vector<int> b(n+1,-1);
    int i = 0, j = -1;
    while(i != n) {
        while(j != -1 && s[i] != s[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
    return b;
}

//finds all occurences of m in n with kmp array of a. 
vector<int> find_matches(vector<int> &n, vector<int> &m, vector<int> &a) {
    vector<int> matches;
    int i = 0;
    int j = 0;
    while(i < n.size()) {
        while(j == m.size() || (j != -1 && n[i] != m[j])) {
            j = a[j];
        }
        i++;
        j++;
        if(j == m.size()) {
            matches.push_back(i - m.size() + 1);
        }
    }
    return matches;
}


void solve() {

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> aadj(n);
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        aadj[a-1].push_back(b-1);
    }
    vector<int> b(n);
    for(int &x : b) cin >> x;
    vector<vector<int>> badj(n);
    cin >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        badj[a-1].push_back(b-1);
    }

    auto dfsneed = [&](auto self, int i, int d, vector<vector<int>> &adj, vector<int> &vis, vector<int> &enterneeds, vector<int> &exitneeds, vector<int> &stat) -> void {
        if(vis[i]) return;
        vis[i] = 1;
        if(stat[i]) { //require an exit at node i - 1
            exitneeds[d]++;
        } else {
            enterneeds[d]++;
        }
        for(int c : adj[i]) {
            self(self, c, (d + 1) % k, adj, vis, enterneeds, exitneeds, stat);
        }
    };

    vector<int> aenterneeds(k), aexitneeds(k), benterneeds(k), bexitneeds(k), avis(n), bvis(n);
    dfsneed(dfsneed, 0, 0, aadj, avis, aenterneeds, aexitneeds, a);
    dfsneed(dfsneed, 0, 0, badj, bvis, benterneeds, bexitneeds, b);

    // cout << "a enterneeds : " << aenterneeds << '\n';
    // cout << "a exitneeds : " << aexitneeds << '\n';

    // cout << "b enterneeds : " << benterneeds << '\n';
    // cout << "b exitneeds : " << bexitneeds << '\n';

    for(int i = 0; i < k; i++) {
        aenterneeds.push_back(aenterneeds[i]);
        aexitneeds.push_back(aexitneeds[i]);
    }

    vector<int> aenterkmp = kmp(bexitneeds);
    vector<int> aexitkmp = kmp(benterneeds);

    vector<int> aentermatches = find_matches(aenterneeds, bexitneeds, aenterkmp);
    vector<int> aexitmatches = find_matches(aexitneeds, benterneeds, aexitkmp);

    for(int &x : aentermatches) x %= k;
    for(int &x : aexitmatches) x %= k;

    // cout << "amatches : " << aentermatches << '\n';
    // cout << "amatches2 : " << aexitmatches << '\n';

    set<int> as(aentermatches.begin(), aentermatches.end());
    set<int> bs(aexitmatches.begin(), aexitmatches.end());

    int ok = 0;

    for(int x : as) {
        if(bs.count((x-2+k)%k)) {
            ok = 1;
        }
    }

    if(reduce(a.begin(),a.end()) == n && reduce(b.begin(), b.end()) == 0 || reduce(a.begin(), a.end()) == 0 && reduce(b.begin(), b.end()) == n) {
        ok = 1;
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// vector<int> kmp(vector<int> s) {
//     int n = s.size();
//     vector<int> b(n+1,-1);
//     int i = 0, j = -1;
//     while(i != n) {
//         while(j != -1 && s[i] != s[j]) {
//             j = b[j];
//         }
//         i++;
//         j++;
//         b[i] = j;
//     }
//     return b;
// }

// //finds all occurences of m in n with kmp array of a. 
// vector<int> find_matches(vector<int> &n, vector<int> &m, vector<int> &a) {
//     vector<int> matches;
//     int i = 0;
//     int j = 0;
//     while(i < n.size()) {
//         while(j == m.size() || (j != -1 && n[i] != m[j])) {
//             j = a[j];
//         }
//         i++;
//         j++;
//         if(j == m.size()) {
//             matches.push_back(i - m.size() + 1);
//         }
//     }
//     return matches;
// }


// void solve() {

//     int n, k; cin >> n >> k;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<vector<int>> aadj(n);
//     int m; cin >> m;
//     for(int i = 0; i < m; i++) {
//         int a, b; cin >> a >> b;
//         aadj[a-1].push_back(b-1);
//     }
//     vector<int> b(n);
//     for(int &x : b) cin >> x;
//     vector<vector<int>> badj(n);
//     cin >> m;
//     for(int i = 0; i < m; i++) {
//         int a, b; cin >> a >> b;
//         badj[a-1].push_back(b-1);
//     }



//     auto colorer = [&](auto self, int i, int d, vector<vector<int>> &adj, vector<int> &vis, vector<int> &enterneeds, vector<int> &exitneeds, vector<int> &stat) -> void {
//         if(vis[i]) return;
//         vis[i] = 1;
//         if(stat[i]) { //require an exit at node i - 1
//             exitneeds[d]++;
//         } else {
//             enterneeds[d%k]++;
//         }
//         for(int c : adj[i]) {
//             self(self, c, (d + 1) % k, adj, vis, enterneeds, exitneeds, stat);
//         }
//     };

//     // auto dfsnorm = [&](auto self, int i, int d, vector<vector<int>> &adj, vector<int> &vis, vector<int> &entercnts, vector<int> &exitcnts, vector<int> &stat) -> void {
//     //     if(vis[i]) return;
//     //     vis[i] = 1;
//     //     if(stat[i]) { //require an exit at node i - 1
//     //         entercnts[d]++;
//     //     } else {
//     //         exitcnts[d]++;
//     //     }
//     //     for(int c : adj[i]) {
//     //         self(self, c, (d + 1) % k, adj, vis, entercnts, exitcnts, stat);
//     //     }
//     // };

//     vector<int> aenterneeds(k), aexitneeds(k), entercnts(k), exitcnts(k), avis(n), bvis(n);
//     colorer(colorer, 0, 0, aadj, avis, aenterneeds, aexitneeds, a);
//     colorer(colorer, 0, 0, badj, bvis, entercnts, exitcnts, b);

//     // cout << "a enterneeds : " << aenterneeds << '\n';
//     // cout << "a exitneeds : " << aexitneeds << '\n';

//     // cout << "b enterneeds : " << benterneeds << '\n';
//     // cout << "b exitneeds : " << bexitneeds << '\n';

//     for(int i = 0; i < k; i++) {
//         aenterneeds.push_back(aenterneeds[i]);
//         aexitneeds.push_back(aexitneeds[i]);
//     }

//     vector<int> aenterkmp = kmp(entercnts);
//     vector<int> aexitkmp = kmp(exitcnts);

//     vector<int> aentermatches = find_matches(aenterneeds, entercnts, aenterkmp);
//     vector<int> aexitmatches = find_matches(aexitneeds, exitcnts, aexitkmp);

//     // cout << "amatches : " << aentermatches << '\n';
//     // cout << "amatches2 : " << aexitmatches << '\n';

//     for(int &x : aentermatches) x %= k;
//     for(int &x : aexitmatches) x %= k;

//     set<int> as(aentermatches.begin(), aentermatches.end());
//     set<int> bs(aexitmatches.begin(), aexitmatches.end());

//     int ok = 0;

//     for(int x : as) {
//         if(bs.count((x+2)%k)) {
//             ok = 1;
//         }
//     }

//     if(reduce(a.begin(),a.end()) == n && reduce(b.begin(), b.end()) == 0 || reduce(a.begin(), a.end()) == 0 && reduce(b.begin(), b.end()) == n) {
//         ok = 1;
//     }

//     cout << (ok ? "Yes" : "No") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }