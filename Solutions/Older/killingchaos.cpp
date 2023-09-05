#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

/*
     _         _     _                                                  _   _    _             _                            _                  _ _                           ___      _             _    _      _       _ _   
  _ | |_  _ __| |_  | |__  ___ __ __ _ _  _ ___ ___   ___ ___ _ __  ___| |_| |_ (_)_ _  __ _  (_)___  ___ __ _ ____  _   __| |___  ___ ____ _ ( ) |_   _ __  ___ __ _ _ _   |_ _|  __| |_  ___ _  _| |__| |  __| |___  (_) |_ 
 | || | || (_-<  _| | '_ \/ -_) _/ _` | || (_-</ -_) (_-</ _ \ '  \/ -_)  _| ' \| | ' \/ _` | | (_-< / -_) _` (_-< || | / _` / _ \/ -_|_-< ' \|/|  _| | '  \/ -_) _` | ' \   | |  (_-< ' \/ _ \ || | / _` | / _` / _ \ | |  _|
  \__/ \_,_/__/\__| |_.__/\___\__\__,_|\_,_/__/\___| /__/\___/_|_|_\___|\__|_||_|_|_||_\__, | |_/__/ \___\__,_/__/\_, | \__,_\___/\___/__/_||_|  \__| |_|_|_\___\__,_|_||_| |___| /__/_||_\___/\_,_|_\__,_| \__,_\___/ |_|\__|
                                                                                       |___/                      |__/                                                                                                        
*/

ll roundup(ll num) {
    return num + (10 - num % 10) % 10;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> prefix(n+1);
    map<ll, ll> m;
    set<ll> s;
    vector<bool> boom(n+2, false);
    ll count = 0;
    ll coaches = 1;
    for(int i = 1; i < n + 1; i++) {
        ll num;
        cin >> num;
        prefix[i] = prefix[i-1] + num;
        count += num;
    }
    m[1] = count;
    m[n+1] = 0;
    count = roundup(count);
    boom[0] = true;
    boom[n+1] = true;
    prefix.push_back(prefix[prefix.size()-1]);
    ll best = 0;
//    cout << "starting count: " << count << '\n';
    for(int q = 0; q < n; q++) {
        ll p;
        cin >> p;
        best = max(best, count * coaches);
        if(boom[p-1]) {
            if(boom[p+1]) { //left and right coaches are blown up!
                coaches--;
                count -= roundup(prefix[p] - prefix[p-1]);
            } else { //left cart is blown up, but right cart is intact. 
                count += roundup(m[p] - (prefix[p] - prefix[p-1])) - roundup(m[p]);
                m[p+1] = m[p] - prefix[p] - prefix[p-1];
            }
        } else if(boom[p+1]) { // right car is blown up, but left cart is intact
            ll lowest = (*(--m.lower_bound(p))).second;
            ll lowest = 
            count += roundup(lowest - (prefix[p] - prefix[p-1])) - roundup(lowest);
            m[(*(--m.lower_bound(p))).first] = lowest - (prefix[p] - prefix[p-1]); 
        } else { //both cars left and right are intact
            count += roundup(prefix[p-1] - prefix[(*(--m.lower_bound(p))).first - 1]) + roundup(prefix[(*(m.lower_bound(p))).first - 1] - prefix[p]) - roundup(prefix[(*(m.lower_bound(p))).first - 1] - prefix[(*(--m.lower_bound(p))).first - 1]);
            // cout << "change: " << roundup(prefix[p-1] - prefix[(*(--m.lower_bound(p))).first - 1]) + roundup(prefix[(*(m.lower_bound(p))).first - 1] - prefix[p]) - roundup(prefix[(*(m.lower_bound(p))).first - 1] - prefix[(*(--m.lower_bound(p))).first - 1]) << '\n';
            // cout << "change add 1: " << roundup(prefix[p-1] - prefix[(*(--m.lower_bound(p))).first - 1]) << '\n';
            // cout << "index of change add 1: " << (*(--m.lower_bound(p))).first << '\n';
            // cout << "change add 2: " << roundup(prefix[(*(m.lower_bound(p))).first] - prefix[p - 1]) << '\n';
            // cout << "change remove 3: " << roundup(prefix[(*(m.lower_bound(p))).first - 1] - prefix[(*(--m.lower_bound(p))).first - 1]) << '\n';
            m[(*(--m.lower_bound(p))).first] = prefix[p-1] - prefix[(*(--m.lower_bound(p))).first - 1];
            m[p+1] = prefix[(*(m.lower_bound(p))).first - 1] - prefix[p];
            coaches++;
        }
        // cout << "iteration: " << q << '\n';
        // cout << "count: " << count << " coaches: " << coaches << "\n";
//        print out map K V
        // for(pair<ll, ll> it: m) {
        //     cout << "first: " << it.first << " second: " << it.second << "\n";
        // }
        boom[p] = true;
        m[p] = -1;
    }
    // cout << "ending count: " << count << '\n';
    cout << best;

    return 0;
}