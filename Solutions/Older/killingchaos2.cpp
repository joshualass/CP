#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll roundup(ll n) {
    return n + (10 - n % 10) % 10;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    set<ll> indexes;
    vector<ll> prefixes(n+1);
    vector<bool> boom(n+2);
    ll count = 0;
    ll coaches = 1;
    boom[0] = true;
    boom[n+1] = true;
    indexes.insert(0);
    indexes.insert(n);
    for(int i = 1; i <= n; i++) {
        ll num;
        cin >> num;
        prefixes[i] = prefixes[i-1] + num;
        count += num;
    }
    count = roundup(count);
    ll best = roundup(count) * coaches;
    for(int i = 0; i < n; i++) {
        ll index;
        cin >> index;
        ll indexValue = prefixes[index]-prefixes[index-1];

        if(boom[index - 1]) {
            if(boom[index + 1]) { // both gone
                count -= roundup(indexValue);
                coaches--;
            } else { // left gone
                count += roundup(prefixes[*(indexes.upper_bound(index))] - prefixes[index]);
                count -= roundup(prefixes[*(indexes.upper_bound(index))] - prefixes[index - 1]);
                indexes.insert(index);
            }
        } else if(boom[index + 1]) { // right gone
            count += roundup(prefixes[index - 1] - prefixes[*(--indexes.lower_bound(index))]);
            count -= roundup(prefixes[index] - prefixes[*(--indexes.lower_bound(index))]);
            indexes.insert(index-1);
        } else { // both here
            count += roundup(prefixes[index - 1] - prefixes[*(--indexes.upper_bound(index))]); // lower half
            count += roundup(prefixes[*(indexes.upper_bound(index))] - prefixes[index]); // upper half
            count -= roundup(prefixes[*(indexes.upper_bound(index))] - prefixes[*(--indexes.upper_bound(index))]); // original segment
            coaches++;
            indexes.insert(index);
            indexes.insert(index-1);
        }

        boom[index] = true;
        best = max(best, count * coaches);
//        cout << "count: " << count << " coaches: " << coaches << "\n";
    }
    cout << best;
    return 0;
}