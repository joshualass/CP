#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    int cnt = 0;

    vector<bool> visited(n+1);
    vector<int> values(n+1); //stores the valeus of the elements at index i
    vector<int> pos(n+1); //stores the position of value i
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(!visited[num-1]) {
            cnt++;
        }
        visited[num] = true;
        values[i+1] = num;
        pos[num] = i + 1;
    }
    values.push_back(n+1);
    pos.push_back(n+1);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if(a == b) {
            cout << cnt << "\n";
            continue;
        }
        int loidx = min(a,b);
        int hiidx = max(a,b);
        int loval = values[loidx];
        int hival = values[hiidx];

        int change = 0;

        if(pos[loval-1] > loidx && pos[loval-1] < hiidx) {
            change--;
        }
        if(pos[loval+1] > loidx && pos[loval+1] < hiidx) {
            change++;
        }

        if(pos[hival-1] < hiidx && pos[hival-1] > loidx) {
            change++;
        }
        if(pos[hival+1] < hiidx && pos[hival+1] > loidx) {
            change--;
        }
        if(abs(hival-loval) == 1) {
            if(hival > loval) {
                change++;
            } else {
                change--;
            }
        }
        cnt += change;
        cout << cnt << "\n";
        values[loidx] = hival;
        values[hiidx] = loval;
        pos[loval] = hiidx;
        pos[hival] = loidx;
    }

    return 0;
}
