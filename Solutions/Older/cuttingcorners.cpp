#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Point {
    ld x;
    ld y;

    string print() {
        return to_string(x) + " " + to_string(y);
    }
};

ld calcAngle(Point a, Point b, Point c) {
    ld v1x = a.x - b.x;
    ld v1y = a.y - b.y;
    ld v2x = c.x - b.x;
    ld v2y = c.y - b.y;
    ld magv1 = sqrt(v1x*v1x+v1y*v1y);
    ld magv2 = sqrt(v2x*v2x+v2y*v2y);
    ld theta = acosl((v1x*v2x+v1y*v2y)/(magv1*magv2));
    // cout << "theta: " << theta << "\n";
    return theta;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    while(n != 0) {
        vector<Point> v(n);
        for(Point& x: v) {
            cin >> x.x;
            cin >> x.y;
        }
        while(v.size() > 3) {
            ld leastangle = 628727729;
            int mostindex = -1;
            for(int i = 0; i < v.size(); i++) {
                int previndex = (i - 1 + v.size()) % v.size();
                int afterindex = (i + 1) % v.size();
                ld angle = calcAngle(v[previndex],v[i],v[afterindex]);
                if(angle < leastangle) {
                    leastangle = angle;
                    mostindex = i;
                }
            }
            int previndex2 = (mostindex - 2 + v.size()) % v.size();
            int previndex = (mostindex - 1 + v.size()) % v.size();
            int afterindex = (mostindex + 1) % v.size();
            int afterindex2 = (mostindex + 2) % v.size();
            if(calcAngle(v[previndex2],v[previndex],v[afterindex]) < leastangle || calcAngle(v[previndex],v[afterindex],v[afterindex2]) < leastangle) {
                break;
            }
            // cout << "removing: " << v[mostindex].print() << "\n";
            v.erase(v.begin() + mostindex);
        }
        cout << v.size();
        for(int i = 0; i < v.size(); i++) {
            cout << " " << v[i].x << " " << v[i].y;
        }
        cout << "\n";
        cin >> n;
    }

    return 0;
}