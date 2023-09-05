#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {

        int n, m, x1, y1, x2, y2; cin >> n >> m >> x1 >> y1 >> x2 >> y2;
        string direction; cin >> direction;
        pair<int,int> pos = {x1,y2};
        
        set<pair<int,int>> visited;
        int right = (direction[1] == 'R' ? 1 : 0);
        int down = (direction[0] == 'D' ? 1 : 0);
        int bounces = 0;
        while(visited.find({pos.first,pos.second}) == visited.end()) {
            
            bounces++;  
        }
    }

    return 0;
}