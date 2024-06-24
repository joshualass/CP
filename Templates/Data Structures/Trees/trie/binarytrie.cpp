const int depth = 31;

struct Trie {
    int cnt;
    Trie* arr[2];
    Trie() {
        cnt = 0;
        arr[0] = nullptr;
        arr[1] = nullptr;
    }
};

void insert(int num, Trie* root) {
    Trie* curr = root;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (num >> d) & 1;
        if(curr->arr[bit] == nullptr) {
            curr->arr[bit] = new Trie();
        }
        curr = curr->arr[bit];
        curr->cnt++;
    }
}

int query(int num, Trie* root) { //queries the maximum xor value (what else are you going to use a binary trie for lol)
    Trie* curr = root;
    int ans = 0;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (num >> d) & 1;
        if(curr->arr[bit ^ 1] && curr->arr[bit ^ 1]->cnt) {
            curr = curr->arr[bit^1];
            ans += 1 << d;
        } else if(curr->arr[bit] && curr->arr[bit]->cnt)  {
            curr = curr->arr[bit];
        }
    }
    return ans;
}

bool find(int num, Trie* root) { //returns if element is present
    Trie* curr = root;
    for(int d = depth - 1; d >= 0; d--) {
        if(curr->arr[(num >> d) & 1] == nullptr) return 0;
        curr = curr->arr[(num >> d) & 1];       
    }
    return 1;
}

bool erase(int num, Trie* root) { //return 1 if element was removed, 0 if element DNE
    bool contains = find(num,root);
    if(contains) {
        Trie* curr = root;
        for(int d = depth - 1; d >= 0; d--) {
            curr = curr->arr[(num >> d) & 1];
            curr->cnt--;
        }
    }
    return contains;
}

void printHelper(Trie* root, int currdepth, int value) { 
    Trie* curr = root;
    if(currdepth == -1) {
        cout << "value : " << value << " cnt : " << curr->cnt << '\n';
    } else {
        if(curr->arr[0] && curr->arr[0]->cnt) printHelper(curr->arr[0],currdepth-1, value);
        if(curr->arr[1] && curr->arr[1]->cnt) printHelper(curr->arr[1],currdepth-1, value + (1 << currdepth));
    }
}

void print(Trie* root) { //prints all values and cnts in Trie
    printHelper(root, depth - 1, 0);
}