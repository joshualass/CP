#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = INT_MAX;
    T f(T a, T b) {
        return min(a,b); //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;


    vector<int> v(n);
    Tree<int> lotree(n);
    
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        lotree.update(i,num);
        v[i] = num;
    }

    map<int,vector<pair<int,int>>> m;

    for(int i = 0; i < n; i++) {

        int num; cin >> num;
        v.push_back(num);
        m[v[i]].push_back({i,num}); //push back lower nums index as well as value of second num

    }

    vector<int> indexes(n); //for each lower num, stores the index it has in the seg tree

    map<int, pair<Tree<int>, int>> segtrees;

    for(auto x : m) {
        // cout << "x: " << x.first << " " << x.second << '\n';
        Tree<int> tree(x.second.size());
        
        for(int i = 0; i < x.second.size(); i++) {
            tree.update(i,x.second[i].second);
            indexes[x.second[i].first] = i;
        }
        segtrees[x.first] = {tree, x.second.size()};
    }

    int loval = INT_MAX;

    vector<int> anslo;
    vector<int> anshi;

    for(int i = 0; i < n; i++) {
        //check if lowest value
        // cout << "i: " << i << " conditions: " << (v[i] <= lotree.query(i,n)) << " " << (v[i] < loval) << '\n';
        if(v[i] <= lotree.query(i,n) && v[i] < loval) { //first num is lowest in this subarray
            //leq
            // cout << "make here? " << '\n';
            if(segtrees[v[i]].first.query(indexes[i], segtrees[v[i]].second) <= v[i]) { //second number that is less exist
                if(segtrees[v[i]].first.query(indexes[i], segtrees[v[i]].second) != v[i+n]) { //there exists a better lower number
                    continue;
                }
                anslo.push_back(v[i]);
                anshi.push_back(v[i+n]);
                // cout << "make here1? " << '\n';
                break;
            } else { //all second numbers are greater
                //if all numbers are greater, will it be better or just longer (worse)
                // cout << "make here2? " << '\n';
                anslo.push_back(v[i]);
                anshi.push_back(v[i+n]);
                if(loval == INT_MAX) {
                    loval = anshi.back();
                }
            }
        }

    }

    for(auto x : anslo) cout << x << " ";
    for(auto x : anshi) cout << x << " ";

    return 0;
}