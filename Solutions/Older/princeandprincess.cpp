#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    cout << " --- vector --- \n";
    for(int y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int b = 1; b <= casi; b++) {
        int n, p, q; cin >> n >> p >> q; 
        vector<int> prince(++p);
        vector<int> pea(++q);
        for(int &x: prince) cin >> x;
        for(int &x : pea) cin >> x;
        unordered_map<int,int> prince_hash;
        for(int i = 0; i < p; i++) {
            prince_hash.insert({prince[i], i+1});
        }
        vector<int> arr(1);
        for(int i = 0; i < q; i++) {
            int num = pea[i];
            if(prince_hash.find(num) == prince_hash.end()) {
                continue;
            }
            num = prince_hash[num];
            int l = 0;
            int r = arr.size();
            while(l != r) { // binary search for index of lowest element greater than num
                if(r - 1 == l) {
                    if(num > arr[l]) {
                        l = r;
                    } else {
                        r = l;
                    }
                } else {
                    int m = l + (r - l) / 2;
                    if(num > arr[m]) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
            }
            if(l == arr.size()) {
                arr.push_back(num);
            } else {
                arr[l] = num;
            }
            // printV(arr);
        }
        cout << "Case " << b << ": " << arr.size()-1 << "\n";
    }

    return 0;
}