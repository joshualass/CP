int depth = -1;
int nextchild = 20000000;

int a[20000000][2];
ll m[20000000];

void reset() {
    for(int i = 0; i < nextchild; i++) {
        a[i][0] = -1;
        a[i][1] = -1;
        m[i] = 0;
    }
    nextchild = 1;
}

void insert(int x) {
    int cur = 0;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;

        if(a[cur][bit] == -1) {
            a[cur][bit] = nextchild++;
        }
        cur = a[cur][bit];
        m[cur] += x;
    }
}

ll countless(int x) {

    ll res = 0;
    int cur = 0;

    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if((x >> d) & 1) { //if bit is set for k, we have the option to check the offbit. Must not go in direction of bit
            if(a[cur][0] != -1) {
                res += m[a[cur][0]];
            }
        }
        if(a[cur][bit] != -1) {
            cur = a[cur][bit];
        } else {
            return res;
        }
    }
    return res;
}