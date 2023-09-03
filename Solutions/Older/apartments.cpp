#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<int> apartments(n);
    vector<int> people(m);
    for(int &x: apartments) cin >> x;
    for(int &x: people) cin >> x;
    sort(apartments.begin(),apartments.end());
    sort(people.begin(),people.end());
    int index = 0;
    int cool = 0;
    for(int i = 0; i < people.size() && index < n; i++) {
        int person = people[i];
        int apartment = apartments[index];
        while(index < n && person > apartment + k) {
            apartment = apartments[++index];
        }
        if(person >= apartment - k && person <= apartment + k) {
            cool++;
            index++;
        }
    }
    cout << cool << "\n";
    return 0;
}