#include<bits/stdc++.h>
using namespace std;
typedef int64_t LL;
typedef vector<int> vi;
typedef pair<LL,LL> pii;
#define mp make_pair
#define pb push_back
#define f first
#define s second
#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) "LAMELO > MJ"
#endif

typedef long double ld;

//var 
struct Line {
    mutable long double k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(long double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    long double inf = 1/.0;
    long double div(long double a, long double b) { // floored division
        return a / b; }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(long double k, long double m) {
        // add the line y = kx + m
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    long double query(long double x) {
        // get maximum y value at x out of all lines
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    LL n,m;
    cin >> n >> m;
    LineContainer b,c;
    LL mini = 1e18, maxi = -1e18;
    for(int i = 0; i < n; i++){
        LL x,y; cin >> x >> y;
        b.add(x, y);
        c.add(-x, -y);
        maxi = max(maxi, x);
        mini = min(mini, x);
    }
    for(int i = 0; i < m; i++){
        LL x,y,z; cin >> x >> y >> z;
        if(y == 0){
            cout << fixed << setprecision(10) << max(abs(maxi - ((ld)z)/x), abs(mini - ((ld)z)/x)) << "\n";
            continue;
        }
        long double maxi = b.query((long double) x/y);
        long double mini = -c.query((long double) x/y);
        mini *= y;
        maxi *= y;
        mini += z;
        maxi += z;
        long double ab = max(abs(mini), abs(maxi));
        ab /= sqrt(x * x + y * y);
        cout << fixed << setprecision(10) << ab << "\n";
    }

    cout.flush();
    return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
// typedef int64_t LL;
// typedef vector<int> vi;
// typedef pair<LL,LL> pii;
// #define mp make_pair
// #define pb push_back
// #define f first
// #define s second
// #ifdef LOCAL
// #include "debug.hpp"
// #else
// #define debug(...) "LAMELO > MJ"
// #endif
// typedef long double ld;


// //var 
// struct Line {
//     mutable long double k, m, p;
//     bool operator<(const Line& o) const { return k < o.k; }
//     bool operator<(long double x) const { return p < x; }
// };

// struct LineContainer : multiset<Line, less<>> {
//     // (for doubles, use inf = 1/.0, div(a,b) = a/b)
//     long double inf = 1/.0;
//     long double div(long double a, long double b) { // floored division
//         return a / b; }
//     bool isect(iterator x, iterator y) {
//         if (y == end()) return x->p = inf, 0;
//         if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
//         else x->p = div(y->m - x->m, x->k - y->k);
//         return x->p >= y->p;
//     }
//     void add(long double k, long double m) {
//         // add the line y = kx + m
//         auto z = insert({k, m, 0}), y = z++, x = y;
//         while (isect(y, z)) z = erase(z);
//         if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
//         while ((y = x) != begin() && (--x)->p >= y->p)
//             isect(x, erase(y));
//     }
//     long double query(long double x) {
//         // get maximum y value at x out of all lines
//         assert(!empty());
//         auto l = *lower_bound(x);
//         return l.k * x + l.m;
//     }
// };

// int main(){
//     ios_base::sync_with_stdio(0); 
//     cin.tie(0);

//     LL n,m;
//     cin >> n >> m;
//     LineContainer b,c;
//     LL mini = 1e18, maxi = -1e18;

//     for(int i = 0; i < n; i++){
//         LL x,y; cin >> x >> y;
//         b.add(x, y);
//         c.add(-x, -y);
//         maxi = max(maxi, x);
//         mini = min(mini, x);
//     }

//     for(int i = 0; i < m; i++){
//         LL x,y,z; cin >> x >> y >> z;
//         if(y == 0){
//             cout << max(abs(maxi - ((ld)z)/x), abs(mini - ((ld)z)/x)) << "\n";
//             continue;
//         }
//         long double maxi = b.query((long double) x/y);
//         long double mini = -c.query((long double) x/y);
//         mini *= y;
//         maxi *= y;
//         mini += z;
//         maxi += z;
//         long double ab = max(abs(mini), abs(maxi));
//         ab /= sqrt(x * x + y * y);
//         cout << fixed << setprecision(10) << ab << "\n";
//     }

//     cout.flush();
//     return 0;
// }