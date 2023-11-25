// https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int MAX_N = 5e5 + 1; //update this value as length of string varies, add 1 for the $
const int MAX_K = 32 - __builtin_clz(1 << (32 - __builtin_clz(MAX_N)));

int classes[MAX_N][MAX_K];
array<int,3> sorter[MAX_N];

template<typename T>
std::ostream& operator<<(std::ostream& os, const array<T, 3> &arr) {
    for(int i = 0; i < 3; i++) {
        os << arr[i] << " ";
    }
    return os;
}

void build(string &str, int &K) {
    int n = str.size() + 1;
    K = 32 - __builtin_clz(1 << (32 - __builtin_clz(n)));

    //add letters until it fits criterion
    str.push_back('$');

    //sort the base characters
    for(int i = 0; i < n; i++) {
        sorter[i] = {str[i],i,-1};
    }

    sort(sorter, sorter + n);

    int prev_char = '\0';
    int curr = -1;
    for(int i = 0; i < n; i++) {
        // cout << "sorter : " << sorter[i] << '\n';
        if(sorter[i][0] != prev_char) {
            curr++;
        }
        classes[sorter[i][1]][0] = curr;
        prev_char = sorter[i][0];
    }

    for(int k = 1; k < K; k++) {
        for(int i = 0; i < n; i++) {
            sorter[i][0] = classes[i][k-1];
            int next = (i + (1 << (k - 1)));
            if(next >= n) next -= n;
            sorter[i][1] = classes[next][k-1];
            sorter[i][2] = i;
        }
        sort(sorter, sorter + n);
        pair<int,int> prev = {-1,-1};
        curr = -1;
        for(int i = 0; i < n; i++) {
            if(sorter[i][0] != prev.first || sorter[i][1] != prev.second) {
                curr++;
            }
            classes[sorter[i][2]][k] = curr;
            prev = {sorter[i][0], sorter[i][1]};
        }
    }

    for(int j = 0; j < n; j++) {
        for(int i = 0; i < K; i++) {
            cout << classes[j][i] << " ";
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // clock_t tStart = clock();

    // freopen("suffixarray2.in","r",stdin);
    // freopen("suffixarray2.out","w",stdout);
    
    string str; cin >> str;
    int k = -1;
    build(str, k);
    vector<int> v(str.size());
    for(int i = 0; i < str.size(); i++) {
        v[classes[i][k-1]] = i;
    }

    for(auto x : v) cout << x << " ";

    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    return 0;
}