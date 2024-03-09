#include <bits/stdc++.h> //AC solution at 9:39 AM 9/12/2023
typedef long long ll;
typedef long double ld;
using namespace std;

int get_shift(int num, int shift) {
    while(shift-- != 0) {
        num /= 10;
    }
    return num;
}

int get_mult(int shift) {
    int num = 1;
    while(shift-- != 0) {
        num *= 10;
    }
    return num;
}

void swapper(int num, int l, int r, int step, queue<pair<int,int>> &q) {
    // cout << "num: " << num << " " << l << " " << r << " " << step << "\n";
    int numL = get_shift(num, l) % 10;
    int numR = get_shift(num, r) % 10;
    // cout << "digits: " << numL << " " << numR << "\n";
    num -= numL * get_mult(l);
    num -= numR * get_mult(r);
    // cout << "between: " << num << "\n";
    num += numL * get_mult(r);
    num += numR * get_mult(l);
    // cout << "after: " << num << "\n";
    q.push({num,step+1});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unordered_map<int,int> m;
    queue<pair<int,int>> q;
    q.push({123456789,0});
    while(q.size()) {
        pair<int,int> p = q.front();
        // cout << p.first << "\n";
        q.pop();
        if(m.find(p.first) != m.end()) {
            continue;
        }
        m[p.first] = p.second;
        swapper(p.first,0,3,p.second,q);
        swapper(p.first,1,4,p.second,q);
        swapper(p.first,2,5,p.second,q);
        swapper(p.first,3,6,p.second,q); 
        swapper(p.first,4,7,p.second,q);
        swapper(p.first,5,8,p.second,q);  
        swapper(p.first,0,1,p.second,q);
        swapper(p.first,1,2,p.second,q);
        swapper(p.first,3,4,p.second,q);
        swapper(p.first,4,5,p.second,q); 
        swapper(p.first,6,7,p.second,q);
        swapper(p.first,7,8,p.second,q);   
        // break;
    }

    int num = 0;
    for(int i = 8; i >= 0; i--) {
        int n; cin >> n;
        num += get_mult(i) * n;
    }
    // cout << num << "\n";
    cout << m[num] << "\n";
    return 0;
}