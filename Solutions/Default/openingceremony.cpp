#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
    int index = 0;
    int least = INT32_MAX;

    for(int i = 0; i <= 1000000; i++) {
        while(index != v.size() && v[index] <= i) {
            index++;
        }
        least = min(least, i + n - index);
    }
    cout << least;
    return 0;
}