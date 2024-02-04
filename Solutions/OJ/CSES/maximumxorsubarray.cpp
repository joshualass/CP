#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
finds maximum xor subarray of array in O(n log(depth)) time
CF 1847D
*/

const int depth = 32;

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
 
void solve() {
    int n; cin >> n;
    int most = 0;
    int cur = 0;
    TrieNode* root = newNode();
    insertNode(0,root);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        cur ^= num;
        insertNode(cur, root);
        most = max(most, findMax(cur, root));
    }
    cout << most << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    solve();
    return 0;
}