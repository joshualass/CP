// https://szkopul.edu.pl/problemset/problem/ROXsaseQWYR11jbNvCgM19Er/site/?key=statement

#include <bits/stdc++.h>
using namespace std;

const int N = 5e4;
int v[N];
int visited[N];
bool visited2[N];

int fast_mod(const int input, const int &ceil) {
    return input >= ceil ? input % ceil : input;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int mod = v[0];

    // vector<int> visited(mod,-1);
    memset(visited, -1, sizeof(visited));
    // vector<bool> visited2(mod);
    memset(visited2, 0, sizeof(visited2));
    visited[0] = 0;
    
    queue<pair<int,int>> q;
    q.push({0,0});

    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();

        int num = p.first;

        if(num > 1e9) continue;

        int idx = fast_mod(num, mod);

        if(visited2[idx] == false && num == visited[idx]) {
            visited2[idx] = true;
            for(int i = p.second; i < n; i++) {
                int x = v[i];
                idx = fast_mod((x + num), mod);
                if(visited[idx] == -1 || visited[idx] != -1 && x + num < visited[idx]) {
                    visited[idx] = x + num;
                    visited2[idx] = false;
                    q.push({x + num, i});

                }
            }

        }

    }

    int k; cin >> k;

    for(int i = 0; i < k; i++) {

        int num; cin >> num;
        if(visited[num % mod] != -1 && num >= visited[num % mod]) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }

    }

    // cout << visited << '\n';

    return 0;
}