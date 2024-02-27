const int depth = 31;

struct TrieNode {
    int value;
    TrieNode *arr[3];
};

TrieNode *newNode() {
    TrieNode *temp = new TrieNode;
    temp->value = 0;
    temp->arr[0] = nullptr;
    temp->arr[1] = nullptr;
    temp->arr[2] = nullptr;
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
            curr->arr[idx]->arr[2] = curr;
            curr = curr->arr[idx];
        }
    }
    curr->value = num;
}

int query(int num, TrieNode* root) { //queries the maximum xor value 
    TrieNode* curr = root;
    int ans = 0;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1; //get the depth - ith bit of num
        if(curr->arr[idx ^ 1]) {
            ans += (1 << (depth - i - 1));
            curr = curr->arr[idx ^ 1];
        } else {
            curr = curr->arr[idx];
        }
    }
    return ans;
}

void eraseNode(int num, TrieNode* root) { //erases a node from the trie
    TrieNode* curr = root;
    int ans = 0;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1;
        curr = curr->arr[idx];
    }

    for(int i = 0; i < depth - 1; i++) {
        int idx = (num >> i) & 1;
        TrieNode* parent = curr->arr[2];
        if(parent->arr[idx ^ 1] ) {
            parent->arr[idx] = nullptr;
            return;
        }
        curr = parent;
    }
}