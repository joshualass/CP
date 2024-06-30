    //segtree range query, given starting point, finds largest ranges that satisfies cond, used successfully in https://codeforces.com/contest/1548/submission/268072577
    int rquery(int start, T condval) {
        return _rquery(1, 0, size, start, n, base, condval).second;
    }

    bool cond(T val, T condval) { //change this for different conditions
        return val != condval;
    }

    pair<T,int> _rquery(int idx, int currl, int currr, int &targetl, int &targetr, T curr, T &condval) {
        if(currr <= targetl || currl >= targetr) return {base,0};
        if(isLeaf(idx)) {
            if(cond(comb(curr,v[idx]), condval)) {
                return {comb(curr,v[idx]), 1};
            } else {
                return {base, 0};
            }
        }
        if(currl >= targetl && currr <= targetr) {//if the entire range is ok, we are ok
            if(cond(comb(curr, v[idx]), condval)) {
                return {comb(curr, v[idx]), currr - currl};
            }
        }
        int mid = (currl + currr) / 2;
        pair<T,int> lhs = _rquery(idx * 2, currl, mid, targetl, targetr, curr, condval);
        if(lhs.second != mid - max(currl,targetl) && mid > targetl) { //check if entire left range is still ok
            return lhs;
        } else { //if it is ok, try right side
            pair<T,int> rhs = _rquery(idx * 2 + 1, mid, currr, targetl, targetr, lhs.first, condval);
            return {comb(lhs.first,rhs.first) ,lhs.second + rhs.second};
        }
    }