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

// i like this problem :)

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);

    vector<vector<int>> in(26);
    vector<int> par_id(26), type(26); //start everything as type 0

    for(int i = 0; i < 26; i++) {
        par_id[i] = adj.size();
        adj.push_back({});
    }

    // cout << "par_id : " << par_id << '\n';
    // cout << "type : " << type << '\n';

    for(int i = 0; i < m; i++) {
        int id; cin >> id;
        char c; cin >> c;
        char action; cin >> action;
        id--;
        int wh = c - 'A';
        int t = action == 'D';

        if(t != type[wh]) {
            int nx = adj.size();
            adj.push_back({});
            for(int x : in[wh]) {
                if(x != id) {
                    // cout << "add edge in x : " << x << " to nx : " << nx << '\n';
                    adj[x].push_back(nx);
                }
            }
            in[wh].clear();
            type[wh] = t;
            par_id[wh] = nx;
        }
        adj[par_id[wh]].push_back(id);
        // cout << "add edge par : " << par_id[wh] << " to : " << id << '\n';
        in[wh].push_back(id);
    }

    vector<int> order;

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ind(adj.size());
    for(int i = 0; i < adj.size(); i++) {
        for(int to : adj[i]) ind[to]++;
    }
    for(int i = 0; i < adj.size(); i++) {
        if(ind[i] == 0) {
            if(i >= n) {
                pq.push(-i);
            } else {
                pq.push(i);
            }
        }
    }

    while(pq.size()) {
        int x = pq.top();
        pq.pop();
        // cout << "x : " << x << '\n';
        if(x < 0) x *= -1;
        if(x < n) order.push_back(x);
        for(int to : adj[x]) {
            ind[to]--;
            if(ind[to] == 0) {
                if(to >= n) {
                    pq.push(-to);
                } else {
                    pq.push(to);
                }
            }
        }
    }

    // cout << "order : " << order << '\n';

    if(order.size() == n) {
        for(int i = 0; i < order.size(); i++) cout << order[i] + 1 << " \n"[i == order.size() - 1];
    } else {
        cout << "-1\n";
    }

    return 0;
}
