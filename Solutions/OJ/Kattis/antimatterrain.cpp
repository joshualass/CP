#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Tree {
    static constexpr array<int,2> base = {INT_MAX, INT_MAX};
    vector<vector<array<int,2>>> v;
    int n, size;
    array<int,2> f(array<int,2> a, array<int,2> b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    array<int,2> get(int idx) {
        if(v[idx].empty()) return base;
        return v[idx].back();
    }
    Tree(int n, array<int,2> def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {base});
    }
    void update(int pos, array<int,2> val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        if(val == base) {
            assert(v[curr].size());
            v[curr].pop_back();
        } else {
            v[curr].push_back(val);
        }

        while(curr != 1) {
            v[curr / 2][0] = f(get(curr ^ 1), get(curr));
            curr /= 2;
        }
    }
    array<int,2> query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    array<int,2> _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return get(idx);
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d, s; cin >> d >> s;
    set<int> xs;
    vector<array<int,2>> a(d); // {x, y}
    for(int i = 0; i < d; i++) {
        cin >> a[i][0] >> a[i][1];
        xs.insert(a[i][0]);
    }

    vector<array<int,3>> sensors(s);
    for(int i = 0; i < s; i++) {
        int x1, x2, y; cin >> x1 >> x2 >> y;
        sensors[i] = {x1, x2 + 1, y};
        xs.insert(x1);
        xs.insert(x2 + 1);
    }

    map<int,int> cm;
    int p = 0;
    for(int x : xs) cm[x] = p++;
    map<int, vector<array<int,3>>> m;
    for(int i = 0; i < d; i++) {
        auto x = a[i];
        m[-x[1]].push_back({0, i, cm[x[0]]});
    }
    for(int i = 0; i < s; i++) {
        auto x = sensors[i];
        m[-x[2]].push_back({1, cm[x[0]], cm[x[1]]});
    }

    vector<int> res(d);
    Tree tree(p);
    for(auto [ny, infos] : m) {
        int y = -ny;
        // cout << "visit y : " << y << endl;
        for(auto event : infos) {
            if(event[0] == 0) {
                int id = event[1], x = event[2];
                tree.update(x, {y, id});
                // cout << "update x : " << x << " y : " << y << " id : " << id << endl;
            } else {
                int x1 = event[1], x2 = event[2];
                // cout << "sensor x1 : " << x1 << " x2 : " << x2 << endl;
                int lo_y = tree.query(x1, x2)[0];
                if(lo_y != INT_MAX) {
                    while(1) {
                        auto [height, id] = tree.query(x1, x2);
                        // cout << "drop found h : " << height << " id : " << id << endl;
                        if(height == lo_y) {
                            res[id] = y;
                            int x = cm[a[id][0]];
                            // cout << "x : " << x << endl;
                            tree.update(x, tree.base);
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < d; i++) cout << res[i] << '\n';

    return 0;
}


// #include <algorithm>
// #include <bitset>
// #include <complex>
// #include <deque>
// #include <exception>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <iterator>
// #include <limits>
// #include <list>
// #include <locale>
// #include <map>
// #include <memory>
// #include <new>
// #include <numeric>
// #include <ostream>
// #include <queue>
// #include <set>
// #include <sstream>
// #include <stack>
// #include <stdexcept>
// #include <streambuf>
// #include <string>
// #include <typeinfo>
// #include <utility>
// #include <valarray>
// #include <vector>
// #include <array>
// #include <atomic>
// #include <chrono>
// #include <condition_variable>
// #include <forward_list>
// #include <future>
// #include <initializer_list>
// #include <mutex>
// #include <random>
// #include <ratio>
// #include <regex>
// #include <scoped_allocator>
// #include <system_error>
// #include <thread>
// #include <tuple>
// #include <typeindex>
// #include <type_traits>
// #include <unordered_map>
// #include <unordered_set>
// #include <cassert>
// #include <cstring>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int d, s;
//     cin >> d >> s;
//     vector<int> dx(d), dy(d), sl(s), sr(s), sy(s);
//     for(int i = 0; i < d; i++) cin >> dx[i] >> dy[i];
//     for(int i = 0; i < s; i++) cin >> sl[i] >> sr[i] >> sy[i];
//     for(int i = 0; i < s; i++) sr[i] ++;
//     int n;
//     {
//         set<int> st;
//         for(int i = 0; i < d; i++) st.insert(dx[i]);
//         for(int i = 0; i < s; i++) {
//             st.insert(sl[i]);
//             st.insert(sr[i]);
//         }
//         map<int, int> mp;
//         n = 0;
//         for(auto i = st.begin(); i != st.end(); i++) {
//             mp[*i] = n ++;
//         }
//         for(int i = 0; i < d; i++) dx[i] = mp[dx[i]];
//         for(int i = 0; i < s; i++) {
//             sl[i] = mp[sl[i]];
//             sr[i] = mp[sr[i]];
//         }
//     }
//     // int B = sqrt(100000);
//     int B = 1;
//     int N = (n + B - 1) / B;
//     vector<stack<int>> a(n), A(N);
//     vector<array<int, 3>> ev(0);   //{y, ind, type}
//     for(int i = 0; i < d; i++) ev.push_back({dy[i], i, 0});
//     for(int i = 0; i < s; i++) ev.push_back({sy[i], i, 1});
//     sort(ev.begin(), ev.end());
//     vector<int> dtime(s, 1e9 + 100);
//     vector<int> ans(d, -1);
//     for(int i = 0; i < ev.size(); i++) {
//         int y = ev[i][0];
//         int ind = ev[i][1];
//         int type = ev[i][2];
//         // cout << "I : " << y << " " << ind << " " << type << endl;
//         if(type == 0) { //droplet
//             int x = dx[ind];
//             int X = x / B;
//             // cout << "X : " << x << endl;
//             while(a[x].size() != 0) {
//                 int sind = a[x].top();
//                 int cdtime = y - sy[sind];
//                 // cout << "SIND : " << sind << " " << cdtime << " " << dtime[sind] << "\n";
//                 assert(cdtime > 0);
//                 if(dtime[sind] < cdtime) {
//                     a[x].pop();
//                     continue;
//                 }
//                 cout << "SIND : " << dtime[sind] << " " << sind << " " << cdtime << endl;
//                 assert(dtime[sind] == (1e9 + 100) || dtime[sind] == cdtime);
//                 dtime[sind] = min(dtime[sind], cdtime);
//                 ans[ind] = max(ans[ind], sy[sind]);
//                 // cout << "UPD ANS : " << ans[ind] << "\n";
//                 break;
//             }
//             // cout << "SIUZE : " << A[X].size() << endl;
//             while(A[X].size() != 0) {
//                 // cout << "HERE" << endl;
//                 int sind = A[X].top();
//                 int cdtime = y - sy[sind];
//                 assert(cdtime > 0);
//                 if(dtime[sind] < cdtime) {
//                     A[X].pop();
//                     continue;
//                 }
//                 assert(dtime[sind] == (1e9 + 100) || dtime[sind] == cdtime);
//                 dtime[sind] = min(dtime[sind], cdtime);
//                 // ans[ind] = min(ans[ind], cdtime);
//                 ans[ind] = max(ans[ind], sy[sind]);
//                 break;
//             }
//             if(ans[ind] == -1) ans[ind] = 0;
//             // cout << "ANS : " << ans[ind] << " " << ind << "\n";
//         }
//         else {  //segment
//             int l = sl[ind], r = sr[ind];
//             int L = ((l + B - 1) / B) * B;
//             int R = (r / B) * B;
//             // cout << "LR : " << l << " " << r << " " << L << " " << R << " " << B << endl;
//             if(L <= R) {
//                 for(int i = l; i < L; i++) {
//                     a[i].push(ind);
//                 }
//                 for(int i = r - 1; i >= R; i--) {
//                     a[i].push(ind);
//                 }
//                 L /= B, R /= B;
//                 // cout << "LR : " << L << " " << R << endl;
//                 for(int i = L; i < R; i++) {
//                     // cout << "I : " << i << endl;
//                     A[i].push(ind);
//                 }
//             }
//             else {
//                 for(int i = l; i < r; i++) {
//                     a[i].push(ind);
//                 }
//             }
//         }
//     }
//     for(int i = 0; i < d; i++) cout << ans[i] << "\n";
//     // cout << "\n";

//     return 0;
// }
