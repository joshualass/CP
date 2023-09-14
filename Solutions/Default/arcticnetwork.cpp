#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int find(vector<int> &pointers, int x) {
    if(pointers[x] == x) {
        return x;
    }
    pointers[x] = find(pointers,pointers[x]);
    return pointers[x];
}

void unify(vector<int> &pointers, vector<int> &sizes, int x, int y) {
    x = find(pointers,x);
    y = find(pointers,y);
    if(sizes[x] == sizes[y]) {
        pointers[y] = x;
        sizes[x]++;
    } else if(sizes[x] < sizes[y]) {
        pointers[y] = pointers[x];
    } else {
        pointers[x] = pointers[y];
    }
}

ld dist(int x1, int y1, int x2, int y2) {
    return sqrt((ld)(x2-x1)*(x2-x1) + (ld)(y2-y1)*(y2-y1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while(T-->0) {
        int S, P; cin >> S >> P;
        vector<pair<int,int>> coords(P,{0,0});
        for(pair<int,int> &x: coords) {
            cin >> x.first; 
            cin >> x.second;
        } 
        vector<pair<ld,pair<int,int>>> distances(0);
        for(int r = 0; r < P; r++) {
            for(int c = r + 1; c < P; c++) {
                distances.push_back({dist(coords[r].first,coords[r].second,coords[c].first,coords[c].second),{r,c}});
            }
        }
        sort(distances.begin(),distances.end());
        vector<int> pointers(P);
        vector<int> sizes(P);
        for(int i = 0; i < P; i++) {
            pointers[i] = i;
            sizes[i] = 1;
        }
        ld least = LDBL_MAX;
        int components = P;
        for(int i = 0; i < distances.size(); i++) {
            if(components - max(0,S-1) <= 1) {
                break;
            } 
            if(find(pointers, distances[i].second.first) != find(pointers, distances[i].second.second)) {
                unify(pointers,sizes,distances[i].second.first,distances[i].second.second);
                least = distances[i].first;
                components--;
            }
        }
        cout << fixed << setprecision(2) << least << '\n';
    }

    return 0;
}