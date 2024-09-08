//BinaryTrie but implemented in a caseworky manner. TODO is exchange l / r with some array of sizing [N][2]. 

int depth = 31;
int nextchild = 3200000;

int l[3200000];
int r[3200000];
int m[3200000];

void reset() {
    for(int i = 0; i < nextchild; i++) {
        l[i] = -1;
        r[i] = -1;
        m[i] = -1;
    }
    nextchild = 1;
}

void insert(int i, int x) {
    int cur = 0;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if(!bit) {           
            if(l[cur] == -1) {
                l[cur] = nextchild++;
            }
            cur = l[cur];
        } else {
            if(r[cur] == -1) {
                r[cur] = nextchild++;
            }
            cur = r[cur];
        }
        m[cur] = i;
    }
}

int query(int x, int k) {

    int res = -1;
    int cur = 0;

    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if((k >> d) & 1) { //if bit is set for k, we have the option to check the offbit. Must not go in direction of bit
            if(!bit && l[cur] != -1) {
                res = max(res, m[l[cur]]);
            } 
            if(bit && r[cur] != -1) {
                res = max(res, m[r[cur]]);
            }
        }
        //in either case, go in the direction of x ^ k. 
        if(bit == ((k >> d) & 1)) {
            if(l[cur] != -1) {
                cur = l[cur];
            } else {
                return res;
            }
        } else {
            if(r[cur] != -1) {
                cur = r[cur];
            } else {
                return res;
            }
        }
    }
    return res;
}