#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    

    return 0;
}

//failing BPE
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