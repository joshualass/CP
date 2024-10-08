#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const ll MOD = 1e9 + 7;
const ll inv = 285700002;

void solve() {
    int n; cin >> n;
    vector<pi> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].second;
    }

    // for (auto& p : a) {
    //     cin >> p.first >> p.second;
    // }

    vector<ll> ps(12);

    vector<vector<vector<ll>>> joints(12, vector<vector<ll>>(12, vector<ll>(4)));

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            joints[i][j][0] = 1;
        }
    }

     vector<ll> twos = {1};
    for (int i = 0; i < 23; ++i) {
        twos.push_back(twos.back() * (ll)2);
    }

    for (int i = 0; i < n; ++i) {
        ll p = a[i].second;
        vector<vector<vector<ll>>> new_joints = joints;
        for (int j = 0; j < 10; ++j) {
            if (!(a[i].first & twos[j]))
                continue;
            ll take = (p * inv) % MOD;
            ll dont_take = (((10000) - p) * inv) % MOD;

            ll p_there = ps[j];
            ll p_not_there = (1 - ps[j] + MOD) % MOD;

            // cerr << "p_there : " << p_there << " not : " << p_not_there << endl;
            // cerr << "take : " << take << " not : " << dont_take << endl;

            ps[j] = (p_there * dont_take) % MOD + (p_not_there * take) % MOD;
            ps[j] %= MOD;
        }

        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                if (k == j)
                    continue;
                
                bool one = (a[i].first & twos[j]);
                bool two = (a[i].first & twos[k]);

                ll take = (p * inv) % MOD;
                ll dont_take = (((10000) - p) * inv) % MOD;

                if (!one && !two)
                    continue;
                
                if (one && two) {
                    // have to swap both
                    new_joints[j][k][0] = (joints[j][k][3] * take) % MOD + (joints[j][k][0] * dont_take) % MOD;
                    new_joints[j][k][1] = (joints[j][k][2] * take) % MOD + (joints[j][k][1] * dont_take) % MOD;
                    new_joints[j][k][2] = (joints[j][k][1] * take) % MOD + (joints[j][k][2] * dont_take) % MOD;
                    new_joints[j][k][3] = (joints[j][k][0] * take) % MOD + (joints[j][k][3] * dont_take) % MOD;
                } else if (one) {
                    new_joints[j][k][0] = (joints[j][k][2] * take) % MOD + (joints[j][k][0] * dont_take) % MOD;
                    new_joints[j][k][1] = (joints[j][k][3] * take) % MOD + (joints[j][k][1] * dont_take) % MOD;
                    new_joints[j][k][2] = (joints[j][k][0] * take) % MOD + (joints[j][k][2] * dont_take) % MOD;
                    new_joints[j][k][3] = (joints[j][k][1] * take) % MOD + (joints[j][k][3] * dont_take) % MOD;

                } else {

                    new_joints[j][k][0] = (joints[j][k][1] * take) % MOD + (joints[j][k][0] * dont_take) % MOD;
                    new_joints[j][k][1] = (joints[j][k][0] * take) % MOD + (joints[j][k][1] * dont_take) % MOD;
                    new_joints[j][k][2] = (joints[j][k][3] * take) % MOD + (joints[j][k][2] * dont_take) % MOD;
                    new_joints[j][k][3] = (joints[j][k][2] * take) % MOD + (joints[j][k][3] * dont_take) % MOD;
                    
                }
                
            }
        }
        swap(joints, new_joints);
    }

    // cerr << "ps[0] : " << ps[0] << endl;

    ll exp = 0;

   
    
    for (int i = 0; i < 10; ++i) {
        ll payout = twos[2*i];
        // cerr << "payout : " << payout << endl;
        // cerr << "ps[i] : " << ps[i] << endl;
        ll to_add = (payout * ps[i]) % MOD;
        // cerr << "to_add : " << to_add << endl;
        (exp += to_add) %= MOD;
    }

    for (ll i = 0; i < 10; ++i) {
        for (ll j = 0; j < 10; ++j) {
            if (i == j)
                continue;
            ll payout = twos[i + j];
            // cerr << "payout : " << payout << endl;
            ll prob = (joints[i][j][3]) % MOD;
            ll to_add = (payout * prob) % MOD;
            // assert(to_add < MOD);
            (exp += to_add) %= MOD;
        }
    }
    
    cout << exp % MOD << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int tc; cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}


//  vector<ll> probs(12);

//     for (int i = 0; i < n; ++i) {
//         ll val = a[i].first;
//         ll p = a[i].second;

//         for (int j = 0; j < 10; ++j) {
//             if (val & (1 << j)) {
//                 ll prob_there = probs[j] % MOD;
//                 ll prob_not_there = (1 - probs[j] + MOD) % MOD;

//                 // pick this one
//                 ll pick = (p * inv) % MOD;
//                 ll dont_pick = (1 - pick + MOD) % MOD;

//                 pick = (pick * prob_not_there) % MOD;

//                 // dont pick this one
//                 dont_pick = (dont_pick * prob_there) % MOD;

//                 probs[j] = (pick + dont_pick + MOD) % MOD;
//             }
//         }
//         // cerr << "prob : " << probs[0] << endl;
//     }

//     ll exp = 0;

//     for (ll i = 0; i < 10; ++i) {
//         ll two = pow(2, i);
//         probs[i] %= MOD;
//         // cerr << "i : " << i << " probs : " << probs[i] << endl;
//         ll payout = (two * two) % MOD;
//         exp += (payout * probs[i]) % MOD;
//         exp %= MOD;
//     }

//     for (ll i = 0; i < 10; ++i) {
//         for (ll j = 0; j < 10; ++j) {
//             if (i == j)
//                 continue;
//             ll one = pow(2, i), two = pow(2, j);
//             ll payout = (one * two) % MOD;
//             ll prob = (probs[i] * probs[j]) % MOD;
//             ll to_add = (payout * prob) % MOD;
//             if (!to_add)
//                 continue;
//             // cerr << "i : " << i << " one : " << one << " two : " << two << " j : " << j << " to_add : " << to_add << endl;
//             exp += (to_add % MOD);
//             exp %= MOD;
//         }
//     }