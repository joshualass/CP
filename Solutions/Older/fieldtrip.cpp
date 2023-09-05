#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> v(n);
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = num;
        sum += num;
    }

    if(sum % 3 != 0) {
        cout << "-1";
        return 0;
    }

    vector<ll> buses(3);
    vector<ll> loads(3);
    ll cap = sum / 3;
    int index = 0;
    for(int i = 0; i < n; i++) {
        if(buses[index] + v[i] > cap) {
            if(index == 2) {
                cout << "-1";
                return 0;
            }
            
            loads[index] = i;
            index++;
        }
        if(v[i] > cap) {
            cout << "-1";
            return 0;            
        }
        buses[index] += v[i];
    }
    cout << loads[0] << " " << loads[1]; 
    return 0;
}