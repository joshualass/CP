#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    vector<int> lightson(n);

    for(int i = 0; i < n; i++) {
        if(str[i] == '1') lightson[i] = 1;
    }

    vector<int> switches(n); //for all switches, which lights it's associated with
    vector<set<int>> lights(n); //for all lights, which switches it's associated with

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        switches[i] = num;
        lights[i].insert(i);
        lights[num].insert(i);
    }

    vector<bool> used(n);

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(lights[i].size() == 1) {
            q.push(i);
        }
    }
    vector<int> ans;
    while(q.size()) {
        int light = q.front();
        q.pop();
        int assoc_switch = *lights[light].begin();
        if(lightson[light]) {
            // ops++;
            ans.push_back(assoc_switch);
            lightson[assoc_switch] ^= 1;
            lightson[switches[assoc_switch]] ^= 1;
        }
        used[assoc_switch] = 1;
        lights[assoc_switch].erase(assoc_switch);
        lights[switches[assoc_switch]].erase(assoc_switch);
        if(lights[switches[assoc_switch]].size() == 1) {
            q.push(switches[assoc_switch]);
        }
    }

    // cout << "upd lights : ";
    // for(auto x : lightson) cout << x;
    // cout << '\n';

    vector<int> visited(n);
    bool poss = 1;
    for(int j = 0; j < n; j++) {
        if(lightson[j]) {
            vector<int> trylights;
            q.push(j); //switch j
            while(q.size()) {
                int assoc_switch = q.front(); 
                q.pop(); 
                if(used[assoc_switch]) continue;
                used[assoc_switch] = 1;
                trylights.push_back(assoc_switch);
                q.push(switches[assoc_switch]);
            }
            // cout << "trylights : " << trylights << '\n';
            // cout << "lights on 1 : ";
            // for(auto x : lightson) cout << x;
            // cout << '\n';
            vector<int> try1;
            for(int i = 1; i < trylights.size(); i++) {
                if(lightson[trylights[i]]) {
                    try1.push_back(trylights[i]);
                    // cout << "i : " << i << " t1 : " << trylights[i] << " t2 : " << switches[trylights[i]] << '\n';
                    lightson[trylights[i]] ^= 1;
                    lightson[switches[trylights[i]]] ^= 1;
                }
            }
            bool valid1 = 1;
            for(int i = 0; i < trylights.size(); i++) {
                if(lightson[trylights[i]]) valid1 = 0;
            }
            //undo switches
            // cout << "undoing\n";
            for(int i = 0; i < try1.size(); i++) {
                // cout << "i : " << i << " t1 : " << try1[i] << " t2 : " << switches[try1[i]] << '\n';
                lightson[try1[i]] ^= 1;
                lightson[switches[try1[i]]] ^= 1;
            }
            // cout << "lights on 2 : ";
            // for(auto x : lightson) cout << x;
            // cout << '\n';
            vector<int> try2;
            try2.push_back(trylights[0]);
            lightson[trylights[0]] ^= 1;
            lightson[switches[trylights[0]]] ^= 1;    
            for(int i = 1; i < trylights.size(); i++) {
                if(lightson[trylights[i]]) {
                    try2.push_back(trylights[i]);
                    lightson[trylights[i]] ^= 1;
                    lightson[switches[trylights[i]]] ^= 1;
                } 
            }    
            // cout << "lights on 3 : ";
            // for(auto x : lightson) cout << x;
            // cout << '\n';
            bool valid2 = 1;
            for(int i = 0; i < trylights.size(); i++) {
                if(lightson[trylights[i]]) valid2 = 0;
            }
            //undo switches
            // cout << "undoing\n";
            for(int i = 0; i < try2.size(); i++) {
                lightson[try2[i]] ^= 1;
                lightson[switches[try2[i]]] ^= 1;
            }
            // cout << "lights on 4 : ";
            // for(auto x : lightson) cout << x;
            // cout << '\n';
            if(valid1 && valid2) {
                if(try1.size() < try2.size()) {
                    for(auto x : try1) {
                        ans.push_back(x);
                        lightson[x] ^= 1;
                        lightson[switches[x]] ^= 1;
                    }
                } else {
                    for(auto x : try2) {
                        ans.push_back(x);
                        lightson[x] ^= 1;
                        lightson[switches[x]] ^= 1;
                    }
                }
            } else if(valid1) {
                for(auto x : try1) {
                    ans.push_back(x);
                    lightson[x] ^= 1;
                    lightson[switches[x]] ^= 1;
                }
            } else if(valid2) {
                for(auto x : try2) {
                    ans.push_back(x);
                    lightson[x] ^= 1;
                    lightson[switches[x]] ^= 1;
                }
            } else {
                poss = 0;
                break;
            }
            // cout << "lights on 5 : ";
            // for(auto x : lightson) cout << x;
            // cout << '\n';
        }
    }
    if(poss) {
        cout << ans.size() << '\n';
        for(auto x : ans) cout << x + 1 << " ";
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}