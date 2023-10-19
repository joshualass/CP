// https://vjudge.net/problem/UVA-588
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

bool poss(vector<pair<int,bool>> vals) {
    int least = INT_MAX;
    int most = INT_MIN;
    for(int i = 0; i < vals.size(); i++) {
        if(vals[i].second) {
            most = max(most,vals[i].first);
        } else {
            least = min(least,vals[i].first);
        }
    }
    
    // cout << "poss: " << least << " " << most << "\n";
    return least >= most;
}

bool poss2(vector<pair<int,bool>> vals) {
    int least = INT_MAX;
    int most = INT_MIN;
    for(int i = 0; i < vals.size(); i++) {
        if(vals[i].second) {
            least = min(least,vals[i].first);
        } else {
            most = max(most,vals[i].first);
        }
    }
    // cout << "poss2: " << least << " " << most << "\n";
    return least >= most;
}

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

void solve(int n) {
    vector<pair<int,int>> coords(n);
    for(auto &x : coords) cin >> x.first >> x.second;
    vector<pair<int,bool>> xvals(0);
    vector<pair<int,bool>> yvals(0);
    bool prev = true; //true if previous side is either north/east
    coords.push_back(coords[0]);
    coords.push_back(coords[1]);
    for(int i = 2; i <= n+1; i++) {
        bool north = coords[i-1].second - coords[i-2].second > 0;
        bool east = coords[i-1].first - coords[i-2].first > 0;
        if(coords[i].first > coords[i-1].first) { //eastbound
            if(north && prev || !north && !prev) {
                prev = false;
            } else {
                prev = true;
            }
            yvals.push_back({coords[i].second,prev});
        }
        if(coords[i].first < coords[i-1].first) { //westbound
            if(north && prev || !north && !prev) {
                prev = true;
            } else {
                prev = false;
            }
            yvals.push_back({coords[i].second,prev});
        }
        if(coords[i].second > coords[i-1].second) { //northbound
            if(prev && east || !prev && !east) {
                prev = false;
            } else {
                prev = true;
            }
            xvals.push_back({coords[i].first,prev});
        }
        if(coords[i].second < coords[i-1].second) {
            if(prev && east || !prev && !east) {
                prev = true;
            } else {
                prev = false;
            }
            xvals.push_back({coords[i].first,prev});
        }
    }
    // cout << "xvals: " << xvals << "\n";
    // cout << "yvals: " << yvals << "\n";
    // cout << "x: "; poss(xvals);
    // cout << "y: "; poss(yvals);
    // cout << "x: "; poss2(xvals);
    // cout << "y: "; poss2(yvals);
    bool isPoss = poss(xvals) && poss(yvals) || poss2(xvals) && poss2(yvals);
    if(isPoss) {
        cout << "Surveillance is possible.\n\n";
    } else {
        cout << "Surveillance is impossible.\n\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi = 1;
    int n; cin >> n;
    while(n != 0) {
        // if(casi != 1) cout << "\n";
        cout << "Floor #" << casi++ << "\n";
        solve(n);
        cin >> n;
    }
    return 0;
}