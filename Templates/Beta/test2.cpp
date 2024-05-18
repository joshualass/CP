#include <bits/stdc++.h>
using namespace std;

unordered_map<string, unordered_set<string>> adjList;
unordered_map<string, unordered_set<string>> reverseAdjList;
unordered_map<string, bool> visited;

vector<unordered_set<string>> components;
stack<string> s;

void addEdge(string speak, string know)
{
    adjList[speak].insert(know);
    visited[speak] = false;
    visited[know] = false;
}

void resetVisited()
{
    for (auto iter = visited.begin(); iter != visited.end(); iter++)
    {
        iter->second = false;
    }
}

void DFS(string node)
{
    visited[node] = true;

    // build reverse adjacency list
    if (reverseAdjList.find(node) == reverseAdjList.end())
    {
        reverseAdjList[node] = {};
    }

    for (string adjNode : adjList[node])
    {
        // build reverse adjacency list
        if (reverseAdjList.find(adjNode) == reverseAdjList.end())
        {
            reverseAdjList[adjNode] = {};
        }
        reverseAdjList[adjNode].insert(node);

        // DFS
        if (!visited[adjNode])
        {
            DFS(adjNode);
        }
    }

    s.push(node);
}

void DFS2(string node, int compIdx)
{
    // cout << node << " ";
    visited[node] = true;

    components[compIdx].insert(node);
    for (string adjNode : reverseAdjList[node])
    {
        if (!visited[adjNode])
        {
            DFS2(adjNode, compIdx);
        }
    }
}

void SCC()
{
    for (auto iter : adjList)
    {
        if (!visited[iter.first])
        {
            DFS(iter.first);
        }
    }

    // cout << "DFS completed" << endl;

    int compIdx = 0;

    resetVisited();
    // cout << "reset visited" << endl;
    components = vector<unordered_set<string>>(adjList.size());
    while (!s.empty())
    {
        string node = s.top();
        s.pop();
        // cout << node << endl;

        if (!visited[node])
        {
            // cout << "component ";
            // cout << compIdx << ": ";
            DFS2(node, compIdx);
            compIdx += 1;
            // cout << endl;
        }
    }
}

int main()
{

    int N;
    string buf;
    getline(cin, buf);
    N = stoi(buf);
    vector<string> speaks;
    for (int i = 0; i < N; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);

        string name;
        iss >> name;
        string speak;
        iss >> speak;
        speaks.push_back(speak);
        if (adjList.find(speak) == adjList.end())
        {
            adjList[speak] = {};
        }
        string know;
        while (iss >> know)
        {
            addEdge(speak, know);
        }
    }

    // find strongly connected components
    SCC();

    int maximum = 0;
    int index = 0;
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i].size() > maximum)
        {
            maximum = components[i].size();
            index = i;
        }
    }
    int cnt = 0;
    for (string lgg : speaks)
    {
        if (components[index].find(lgg) != components[index].end())
        {
            cnt++;
        }
    }

    cout << N - cnt << endl;

    return 0;
}