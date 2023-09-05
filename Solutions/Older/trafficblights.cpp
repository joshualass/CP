#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll X = 2520; 

void printV(const vector<pair<ld,ld>> &x) {
    cout << " --- vector --- ";
    for(auto y : x) {
        cout << y.first << " " << y.second << " ";
    }
    cout << "\n";
}

bool isPrime(ll n) {
    if(n == 1) { //1 is prime for this problem :)))
        return false;
    }
    if(n == 2 || n == 3) {
        return true;
    }
    if(n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for(ll i = 5; i <= sqrt(n); i+= 6) {
        if(n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void combine(vector<pair<ld,ld>> &v) {
    vector<pair<ld,int>> order(0);
    for(int i = 0; i < v.size(); i++) {
        order.push_back({v[i].first,1});
        order.push_back({v[i].second,-1});
    }
    sort(order.begin(), order.end());
    vector<pair<ld,ld>> updated(0);
    int cnt = 0;
    ld start = -1;
    for(int i = 0; i < order.size(); i++) {
        if(cnt == 0) {
            start = order[i].first;
        }
        cnt += order[i].second;
        if(cnt == 0) {
            updated.push_back({start, order[i].first});
        }
    }
    v = updated;
}

ld totalD(vector<pair<ld,ld>> &v) {
    ld distance = 0;
    for(int i = 0; i < v.size(); i++) {
        distance += v[i].second - v[i].first;
    }
    return distance;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(10);
    map<int,int> m;
    vector<vector<pair<ld,ld>>> ranges(0);
    for(ll i = 1; i <= 100; i++) {
        if(isPrime(i)) {
            m[i] = ranges.size();
            ranges.push_back({});
        }
    }
    
    ld prob = 1;

    ll n; cin >> n;
    
    for(ll i = 0; i < n; i++) {
        ll x, r, g; cin >> x >> r >> g;
        ll p = r + g;
        int idx = m[p / __gcd(p,X)];
        x %= p;
        ld lb = ((ld) x) / p;
        ld ub = ((ld) x + r) / p;
        vector<pair<ld,ld>> segments(0);
        if(ub > 1) {
            segments.push_back({lb,1});
            segments.push_back({0, ub -1});
        } else {
            segments.push_back({lb,ub});
        }
        
        // ld distance = totalD(ranges[idx]) + totalD(segments);
        ld distance = totalD(ranges[idx]);
        for(pair<ld,ld> x : segments) {
            ranges[idx].push_back(x);
        }
        combine(ranges[idx]);
        
        // cout << "segments\n";
        // printV(segments);
        // cout << "ranges\n";
        // printV(ranges[idx]);
        
        ld newdistance = totalD(ranges[idx]);
        ld curr = 0;
        if(distance != 1) {
            curr = prob * (newdistance - distance) / (1 - distance);
            // cout << "prob: " << prob << " newdistance: " << newdistance << " distance: " << distance << " expr: " << prob * (newdistance - distance) / (1 - distance) << "\n";
        }
        prob -= curr;
        cout << curr << "\n";
    }
    cout << prob << "\n";
    return 0;
}

//OTHER VERSION

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const int X = 2520; 

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     vector<vector<int>> v(n,vector<int>(3)); // x, r, g
//     for(auto &x : v) 
//         for(auto &y : x) cin >> y;
        
//     vector<ld> probs(n+1);
    
//     for(int i = 0; i < X; i++) {
//         vector<vector<bool>> ok(100,vector<bool>(100,false));
//         vector<int> lights(100);
//         iota(lights.begin(),lights.end(),0); 
//         ld curr = 1;
        
//         for(int j = 0; j < n; j++) {
//             int p = v[j][1] + v[j][2];
//             int cycle = p / __gcd(X,p);
            
            
//         }
//     }

//     return 0;
// }