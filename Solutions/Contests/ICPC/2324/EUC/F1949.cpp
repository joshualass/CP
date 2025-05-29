#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
thoughts - form a subset tree of sorts. 
we can sort the people by # of activities so that every person we insert will be in a subset of the people that 
we have already inserted. 

maintain the following to help with things

* for each type of activity, we should store the lowest node in the subset tree that this actiivty is present in
this is not too tricky to maintain. 

for inserting each person, we should do 2 things
1) from *, we should see if all the activities of the next person all belong to the same subset node. if they do, 
then this is a proper subset and we update all of the actitivities to this node
2) if there exists some activities that are in 2 different nodes, then we choose the activity with the lowest node id. 

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<pair<vector<int>, int>> a(n);

    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        a[i].second = i;
        for(int j = 0; j < k; j++) {
            int x; cin >> x;
            x--;
            a[i].first.push_back(x);
        }
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) {
        return lhs.first.size() > rhs.first.size();
    });

    vector<int> d(n);
    for(int i = 0; i < n; i++) d[a[i].second] = i;

    vector<int> b(m, -1);

    for(auto [c, idx] : a) {
        if(c.empty()) continue;

        int lo = INT_MAX, hi = INT_MIN;
        for(int x : c) {
            lo = min(lo, b[x]);
            hi = max(hi, b[x]);
        }

        if(lo != hi) {
            cout << "YES\n";
            int lo_d = (lo == -1 ? -1 : d[lo]), hi_d = (hi == -1 ? -1 : d[hi]);
            cout << (lo_d > hi_d ? lo : hi) + 1 << " " << idx + 1 << '\n';
            return 0;
        }

        for(int x : c) b[x] = idx;

    }

    cout << "NO\n";

    return 0;
}

//failing BPE :(
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     vector<vector<pair<int,int>>> in_activity(m);
//     vector<vector<int>> people(n);

//     for(int i = 0; i < n; i++) {
//         int k; cin >> k;
//         people[i].resize(k);
//         for(int &x : people[i]) {
//             cin >> x;
//             x--;
//             in_activity[x].push_back({k,i});
//         }
//     }

    

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// pair<int,int> ans = {-1,-1};

// struct TrieNode {
//     int idx;
//     unordered_map<int,TrieNode*> children;

//     TrieNode() {
//         idx = -1;
//     }

// };

// void insertNode(TrieNode* root, vector<int> activities, int m) {
//     sort(activities.begin(), activities.end());
//     TrieNode* curr = root;
//     for(int i = 0; i < activities.size(); i++) {
//         if(curr->children.count(activities[i]) == 0) {
//             curr->children[activities[i]] = new TrieNode();
//         }
//         curr = curr->children[activities[i]];
//     }
//     curr->idx = m;
// }

// int findidx(TrieNode* root) {
//     if(root->idx != -1) {
//         return root->idx;
//     } else {
//         return findidx((*root->children.begin()).second);
//     }
// }

// void querysame(TrieNode* root) {
//     if(ans.first == -1) {
//         if(root->children.size() >= 2) {
//             ans.first = findidx((*root->children.begin()).second);
//             ans.second = findidx((*++root->children.begin()).second);
//         } else if(root->children.size() == 1) {
//             querysame((*root->children.begin()).second);
//         }
//     }
// }

// void query(TrieNode* root) {
//     for(auto child : root->children) {
//         querysame(child.second);
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     TrieNode* root = new TrieNode();

//     for(int i = 0; i < n; i++) {
//         int k; cin >> k;
//         vector<int> activities(k);
//         for(int &x : activities) cin >> x;
//         insertNode(root, activities, i+1);
//     }

//     query(root);

//     if(ans.first == -1) {
//         cout << "NO\n";
//         return 0;
//     } else {
//         cout << "YES\n";
//         cout << ans.first << " " << ans.second << "\n";
//     }


//     return 0;
// }