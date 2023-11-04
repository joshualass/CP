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

//setup for https://cses.fi/problemset/task/1138 (Path Queries)
void euler_tour(int i, int p, vector<int> &order, vector<int> &subtree_size, vector<int> &visitedTime, vector<vector<int>> &adj) {
    visitedTime[i] = order.size();
    order.push_back(i);
    subtree_size[i] = 1;

    for(int x : adj[i]) {
        if(x == p) continue;

        euler_tour(x,i,order,subtree_size,visitedTime,adj);
        subtree_size[i] += subtree_size[x];
    }

}