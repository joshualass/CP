#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void printAdj(const vector<vector<int>> &adj) {
    cout << "adj:\n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i: " << i << " -";
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

struct TNode {
    char val;
    TNode* left;
    TNode* right;
};

struct TNode* getNode(char c) {
    struct TNode* node = new TNode;
    node->left = nullptr;
    node->right = nullptr;
    node->val = c;
    return node;
}

struct TNode* build(string &s, int i) {
    if(i >= s.size()) return nullptr;
    TNode* node = getNode(s[i]);
    node->left = build(s, i * 2 + 1);
    node->right = build(s, i * 2 + 2);
    return node;
}

int perm[6];

void prePrint(TNode* t, string &s);
void inPrint(TNode* t, string &s);
void postPrint(TNode* t, string &s);

void prePrint(TNode* t, string &s) {
    s.push_back(t->val);
    if(t->left != nullptr) {
        switch(perm[0]) {
            case 0 : prePrint(t->left, s); break;
            case 1 : inPrint(t->left, s); break;
            case 2 : postPrint(t->left, s); break;
        }
    }
    if(t->right != nullptr) {
        switch(perm[1]) {
            case 0 : prePrint(t->right, s); break;
            case 1 : inPrint(t->right, s); break;
            case 2 : postPrint(t->right, s); break;
        }
    }
}

void inPrint(TNode *t, string &s) {
    if(t->left != nullptr) {
        switch(perm[2]) {
            case 0 : prePrint(t->left, s); break;
            case 1 : inPrint(t->left, s); break;
            case 2 : postPrint(t->left, s); break;
        }
    }
    s.push_back(t->val);
    if(t->right != nullptr) {
        switch(perm[3]) {
            case 0 : prePrint(t->right, s); break;
            case 1 : inPrint(t->right, s); break;
            case 2 : postPrint(t->right, s); break;
        }
    }    
}

void postPrint(TNode *t, string &s) {
    if(t->left != nullptr) {
        switch(perm[4]) {
            case 0 : prePrint(t->left, s); break;
            case 1 : inPrint(t->left, s); break;
            case 2 : postPrint(t->left, s); break;
        }
    }
    if(t->right != nullptr) {
        switch(perm[5]) {
            case 0 : prePrint(t->right, s); break;
            case 1 : inPrint(t->right, s); break;
            case 2 : postPrint(t->right, s); break;
        }
    }     
    s.push_back(t->val);
}

vector<vector<int>> mapper(vector<string> str) {
    int n = str[0].size();
    vector<vector<int>> v(2,vector<int>(n));
    for(int i = 1; i < 3; i++) {
        for(int j = 0; j < n; j++) {
            v[i-1][j] = str[0].find(str[i][j]);
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> inputStrings(3);
    for(auto &x: inputStrings) cin >> x;
    vector<vector<int>> key = mapper(inputStrings);
    cout << "key "; printAdj(key);

    string str = "";
    for(int i = 0; i < inputStrings[0].size(); i++) {
        str.push_back('A' + i);
    }
    TNode* tree = build(str, 0);
    // cout << tree->val << " " << tree->left->val << " " << tree->right << "\n";
    // cout << "str? " << str << "\n";

    vector<vector<int>> ans(0);
    for(int i = 0; i < 729; i++) {
        vector<int> cnts(3);
        int copy = i;
        bool flag = true;
        for(int j = 0; j < 6; j++) {
            perm[j] = copy % 3;
            cnts[copy%3]++;
            if(cnts[copy%3] > 2) flag = false;
            copy /= 3;
        }
        if(flag) {
            vector<string> strs(3);
            string s = ""; 
            prePrint(tree,s); strs[0] = s; s = ""; 
            inPrint(tree,s); strs[1] = s; s = "";
            postPrint(tree,s); strs[2] = s; s = "";
            vector<vector<int>> match = mapper(strs);
            if(perm[0] == 0 && perm[1] == 2 && perm[2] == 1 && perm[3] == 2 && perm[4] == 1 && perm[5] == 0) {
                for(auto x : strs) cout << x << "\n";
                cout << "match "; printAdj(match);
            }
            if(key == match) {
                vector<int> v(6);
                for(int i = 0; i < 6; i++) v[i] = perm[i];
                ans.push_back(v);
            }
        }
    }
    cout << "ans?\n";
    printAdj(ans);
    cout << "no rte? " << "\n";
    return 0;
}