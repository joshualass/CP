#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    freopen("traffic.in","r",stdin);
    freopen("traffic.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<tuple<string,int,int>> v {};
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        string ramp; int low, high;
        cin >> ramp >> low >> high;
        v.push_back(make_tuple(ramp,low,high));
    }
    reverse(v.begin(),v.end());
    int low {};
    int high {};
    bool flag = true;
    for(int i = 0; i < N; i++) {
        if(flag) {
            if(get<0>(v[i]) == "none") {
                flag = false;
                low = get<1>(v[i]);
                high = get<2>(v[i]);
            }
        } else {
            if(get<0>(v[i]) == "none") {
                if(get<1>(v[i]) > low) {
                    low = get<1>(v[i]);
                }
                if(get<2>(v[i]) < high) {
                    high = get<2>(v[i]);
                }
            }
            if(get<0>(v[i]) == "off") {
                low += get<1>(v[i]);
                high += get<2>(v[i]);
            }
            if(get<0>(v[i]) == "on") {
                low -= get<2>(v[i]);
                high -= get<1>(v[i]);
                if(low < 0) {
                    low = 0;
                }
                if(high < 0) {
                    high = 0;
                }
            }
        }
//        cout << i << " " << low << " " << high << "\n";
    }
    cout << low << " " << high << "\n";
    reverse(v.begin(),v.end());
    flag = true;
    for(int i = 0; i < N; i++) {
        if(flag) {
            if(get<0>(v[i]) == "none") {
                flag = false;
                low = get<1>(v[i]);
                high = get<2>(v[i]);
            }
        } else {
            if(get<0>(v[i]) == "none") {
                if(get<1>(v[i]) > low) {
                    low = get<1>(v[i]);
                }
                if(get<2>(v[i]) < high) {
                    high = get<2>(v[i]);
                }
            }
            if(get<0>(v[i]) == "on") {
                low += get<1>(v[i]);
                high += get<2>(v[i]);
            }
            if(get<0>(v[i]) == "off") {
                low -= get<2>(v[i]);
                high -= get<1>(v[i]);
                if(low < 0) {
                    low = 0;
                }
                if(high < 0) {
                    high = 0;
                }
            }
        }
//        cout << i << " " << low << " " << high << "\n";
    }
    cout << low << " " << high << "\n";
    return 0;
}