#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    set<ll> r, c, dr, ur;

    for(int i = 0; i < m; i++) {
        ll ro, co; cin >> ro >> co;
        r.insert(ro);
        c.insert(co);
        ur.insert(ro+co);
        dr.insert(ro-co);
    }

    ll ok = n * n;

    ok -= n * r.size();
    ok -= (n - r.size()) * c.size();

    // cout << "start ok : " << ok << '\n';
    // cout << "start dr\n";

    for(ll d : dr) {
        ok -= n - abs(d);
        set<array<ll,2>> revis;
        for(ll ro : r) {
            ll co = ro - d;
            if(co >= 1 && co <= n) {
                // cout << "add roco1 ro : " << ro << " co : " << co << '\n';
                revis.insert({ro,co});
            } 
        }
        for(ll co : c) {
            ll ro = co + d;
            if(ro >= 1 && ro <= n) {
                // cout << "add roco2 ro : " << ro << " co : " << co << '\n';
                revis.insert({ro,co});
            }
        }
        // cout << "d : " << d << " net : " << ((ll)revis.size()) - (n - abs(d)) << '\n';
        ok += revis.size();
    }

    // cout << "start ur\n";
    for(ll d : ur) {
        ok -= n - abs(n + 1 - d);
        set<array<ll,2>> revis;
        for(ll ro : r) {
            ll co = d - ro;
            if(co >= 1 && co <= n) {
                // cout << "add roco1 ro : " << ro << " co : " << co << '\n';
                revis.insert({ro,co});
            }
        }
        for(ll co : c) {
            ll ro = d - co;
            if(ro >= 1 && ro <= n) {
                // cout << "add roco2 ro : " << ro << " co : " << co << '\n';
                revis.insert({ro,co});
            }
        }
        for(ll d2 : dr) {
            if((d-d2) % 2 == 0) {
                ll co = (d - d2) / 2;
                ll ro = d - co;
                if(ro >= 1 && ro <= n && co >= 1 && co <= n) {
                    // cout << "add roco3 ro : " << ro << " co : " << co << '\n';
                    revis.insert({ro,co});
                }
            }
        }
        ok += revis.size();
        // cout << "d : " << d << " net : " << ((ll)revis.size()) - (n - abs(n - (d - 1))) << '\n';
    }

    cout << ok << '\n';

    return 0;
}