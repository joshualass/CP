    void euler_tour(int i, int p, vector<vector<int>> &adj, vector<int> &euler_tour) {
        euler_tour.push_back(i);
        for(auto x : adj[i]) {
            if(x != p) {
                euler_tour(x,i);
                euler_tour.push_back(i);
            }
        }
    }