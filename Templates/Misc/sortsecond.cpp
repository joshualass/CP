struct sort_second {
    bool operator()(const pair<int,int> &left, const pair<int,int> &right) {
        if(left.second == right.second) {
            return left.first < right.first;
        } else {
            return left.second < right.second;
        }
    }
};