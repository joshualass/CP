#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int depth = 31;

/* 
https://www.geeksforgeeks.org/maximum-xor-of-two-numbers-in-an-array-set-2/#
O(n * log(depth)) 
*/

struct TrieNode {
    int value;
    TrieNode *arr[2];
};

TrieNode *newNode() {
    TrieNode *temp = new TrieNode;
    temp->value = 0;
    temp->arr[0] = nullptr;
    temp->arr[1] = nullptr;
    return temp;
}

void insertNode(int num, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1;
        if(curr->arr[idx]) {
            curr = curr->arr[idx];
        } else {
            curr->arr[idx] = newNode();
            curr = curr->arr[idx];
        }
    }
    curr->value = num;
}

int findMax(int num, TrieNode* root) {
    TrieNode *curr = root;
    for(int i = 0; i < depth; i++) {
        int bit = ((num >> (depth - i - 1)) & 1) ^ 1;
        if(curr->arr[bit]) {
            curr = curr->arr[bit];
        } else {
            curr = curr->arr[bit ^ 1];
        }
    }
    return num ^ curr->value;
}

int maxXor(vector<int> v) {
    TrieNode *root = newNode();
    int maxXOR = 0;
    for(int i = 0; i < v.size(); i++) {
        insertNode(v[i], root);
    }
    for(int i = 0; i < v.size(); i++) {
        maxXOR = max(maxXOR, findMax(v[i], root));
    }
    return maxXOR;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    
    cout << maxXor(v) << "\n";

    return 0;
}
