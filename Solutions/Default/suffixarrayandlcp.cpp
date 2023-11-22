#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

//this version runs in n log n
const int MAX_N = 4e5 + 1; //update this value as length of string varies, add 1 for the $
const int MAX_K = 32 - __builtin_clz(1 << (32 - __builtin_clz(MAX_N)));

string str;
int n, K;
int classes[MAX_N][MAX_K];
array<int,3> sorter[MAX_N]; //used for general sorting
array<int,3> sorter_new[MAX_N]; //used for general sorting
int suff[MAX_N];
int lcp[MAX_N];

void radix_sort(int n) {
    {
        vector<int> cnts(n);
        for(int i = 0; i < n; i++) {
            cnts[sorter[i][1]]++;
        }
        vector<int> pos(n);
        for(int i = 1; i < n; i++) {
            pos[i] = pos[i-1] + cnts[i-1];
        }
        for(int i = 0; i < n; i++) {
            auto x = sorter[i];
            sorter_new[pos[x[1]]] = x;
            pos[x[1]]++;
        }
        swap(sorter, sorter_new);
    }
    {
        vector<int> cnts(n);
        for(int i = 0; i < n; i++) {
            cnts[sorter[i][0]]++;
        }
        vector<int> pos(n);
        for(int i = 1; i < n; i++) {
            pos[i] = pos[i-1] + cnts[i-1];
        }
        for(int i = 0; i < n; i++) {
            auto x = sorter[i];
            sorter_new[pos[x[0]]] = x;
            pos[x[0]]++;
        }
        swap(sorter, sorter_new);
    }
}

void buildLCP() {
    memset(lcp, -1, sizeof(lcp));
    for(int i = 0; i < str.size() - 1; i++) {//do lcp of everyrthing except '31' substring
        
    }   
}

void build() {
    n = str.size() + 1;
    K = 32 - __builtin_clz(1 << (32 - __builtin_clz(n)));
    str.push_back(31);

    //sort the base characters
    for(int i = 0; i < n; i++) {
        sorter[i] = {str[i],str[i],i};
    }

    sort(sorter, sorter + n);

    int prev_char = '\0';
    int curr = -1;
    for(int i = 0; i < n; i++) {
        if(sorter[i][0] != prev_char) {
            curr++;
        }
        classes[sorter[i][2]][0] = curr;
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
        radix_sort(n);
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

    for(int i = 0; i < str.size(); i++) {
        suff[classes[i][K-1]] = i;
    }

    buildLCP();
}

void printSuffixArray() {
    for(int i = 0; i < n; i++) {
        cout << suff[i] << " ";
    }
    cout << '\n';
}

//given a substring, returns the indexes of all the substrings within str. Complexity - O(log n * |p|)
vector<int> calcSubstrings(string sub) {
    int lo = 0, hi = str.size();
    while(lo != hi) {
        int m = (hi + lo) / 2;
        if(sub.compare(str.substr(suff[m],sub.size())) > 0) {
            lo = m + 1;
        } else {
            hi = m;
        }
    }
    int lb = lo;
    lo = 0, hi = str.size() - 1;
    while(lo != hi) {
        int m = (hi + lo + 1) / 2;
        if(sub.compare(str.substr(suff[m],sub.size())) < 0) {
            hi = m - 1;
        } else {
            lo = m;
        }
    }
    vector<int> ans;
    // cout << "lo : " << lb << " hi : " << hi << '\n';
    for(int i = lb; i <= lo; i++) {
        ans.push_back(suff[i]);
    }
    sort(ans.begin(),ans.end());
    return ans;   
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    while(cin >> tc) {
        vector<string> queries(tc);
        cin.ignore();
        for(auto &x: queries) getline(cin,x);
        getline(cin,str);
        build();
        for(auto q : queries) cout << calcSubstrings(q) << '\n';
    }
    

    return 0;
}