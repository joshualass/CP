#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Point {
    ld x;
    ld y;
    int id;
};

bool operator<(const Point& point1, const Point& point2) {
    return point1.id < point2.id;
}

// bool operator<(const pair<ld,Point>& point1, )
ld distance(Point one, Point two) {
    return sqrt((two.x - one.x) * (two.x - one.x) + (two.y - one.y) * (two.y - one.y));
}

ld calcAngle(Point one, Point two) { // range from 0 to pi
    return acos((two.x-one.x)/distance(one,two));
}

void solve() {
    int n; cin >> n;
    vector<Point> v(n);
    Point rad = Point({LDBL_MAX,LDBL_MAX,-1});
    for(int i = 0; i < n; i++) {
        cin >> v[i].x;
        cin >> v[i].y;
        v[i].id = i;
        if(v[i].y < rad.y || v[i].y == rad.y && v[i].x < rad.x) {
            rad = v[i];
        }
    }
    // cout << "rad - " << rad.x << " " << rad.y << " " << rad.id << "\n";
    v.erase(v.begin() + rad.id);

    vector<pair<ld,Point>> angles(n-1);
    for(int i = 0; i < v.size(); i++) {
        angles[i] = {calcAngle(rad,v[i]),v[i]};
    }
    sort(angles.begin(),angles.end());
    // for(int i = 0; i < angles.size(); i++) {
    //     cout << "i : " << i << " angle: " << angles[i].first << " x: " << angles[i].second.x << " y: " << angles[i].second.y << "\n";
    // }
    vector<vector<pair<ld,int>>> poly(n-1);
    int idx = -1;
    ld prevangle = -1;
    for(int i = 0; i < angles.size(); i++) {
        if(abs(prevangle - angles[i].first) > 0.00000001) {
            idx++;
        }
        prevangle = angles[i].first;
        poly[idx].push_back({distance(rad,angles[i].second),angles[i].second.id});
    }
    cout << rad.id;
    for(int i = 0; i < poly.size(); i++) {
        sort(poly[i].begin(),poly[i].end());
        if(i == idx) {
            reverse(poly[i].begin(),poly[i].end());
        }
        for(int t = 0; t < poly[i].size(); t++) {
            cout << " " << poly[i][t].second;
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}