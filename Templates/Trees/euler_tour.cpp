void euler_tour(int i, int p, vector<vector<int>> &adj, vector<int> &euler_tour) {
    //version 1 - adds first and last index of tour, good for solving subtree problems with segment tree
    order.push_back(i);
    for(int x : adj[i]) {
        if(x != p) eulerTour(x,i,order,adj);
    }
    order.push_back(i);
    //version 2 - 
    /*
    euler_tour.push_back(i);
    for(auto x : adj[i]) {
        if(x != p) {
            euler_tour(x,i);
            euler_tour.push_back(i);
        }
    }
    */
}