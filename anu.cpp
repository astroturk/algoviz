#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int salt = 848296207;

class Graph
{
private:
    map<pair<int, int>, pair<int, int>> edge_map;
    int nodes_count = 0;
    int edge_count = 0;
    unordered_set<int> nodes_high;
    unordered_set<int> edges_high;

    void print()
    {
        printNodes();
        printEdges();
        printSelections();
    }
    void printNodes()
    {
        cout << "{\"nodes\":[";
        for (int i = 0; i < nodes_count; i++)
        {
            cout << "{\"id\":" << i << ",\"label\":" << i << "}";
            if (i != nodes_count - 1)
                cout << ",";
        }
        cout << "],";
    }
    void printEdges()
    {
        cout << "\"edges\":[";
        auto it = edge_map.begin();
        int dummy = 0;
        for (it; it != edge_map.end(); it++)
        {
            dummy++;
            cout << "{\"from\":" << it->first.first << ",\"to\":" << it->first.second << ",\"id\":" << it->second.first;
            if (it->second.second != salt)
                cout << ",\"label\":" << it->second.second;
            cout << "}";
            if (dummy != edge_count)
                cout << ",";
        }
        cout << "],";
    }
    void printSelections()
    {
        cout << "\"selections\":{";
        cout << "\"nodes\":[";
        int dummy = 0;
        int sz = nodes_high.size();
        for (auto u : nodes_high)
        {
            dummy++;
            cout << u;
            if (dummy != sz)
                cout << ",";
        }
        cout << "],";
        cout << "\"edges\":[";
        dummy = 0;
        sz = edges_high.size();
        for (auto u : edges_high)
        {
            dummy++;
            cout << u;
            if (dummy != sz)
                cout << ",";
        }
        cout << "]";
        cout << "}},";
    }

public:
    void TotalNodes(int n)
    {
        nodes_count = n;
    }
    void AddEdge(int from, int to)
    {
        edge_map[{from, to}] = {edge_count, salt};
        edge_count++;
        print();
    }
    void AddEdge(int from, int to, int label)
    {
        edge_map[{from, to}] = {edge_count, label};
        edge_count++;
        print();
    }
    void removeEdge(int from, int to)
    {
        edge_map.erase({from, to});
        edge_count--;
        print();
    }
    void HighlightNode(int id)
    {
        nodes_high.insert(id);
        print();
    }
    void HighlightEdge(int from, int to)
    {
        edges_high.insert(edge_map[{from, to}].first);
        print();
    }
    void DimNode(int id)
    {
        nodes_high.erase(id);
        print();
    }
    void DimEdge(int from, int to)
    {
        edges_high.erase(edge_map[{from, to}].first);
        print();
    }
};

vector<vector<int>> adj;
Graph G;

void dfs(int v)
{
    G.HighlightNode(v);
    for (auto u : adj[v])
    {
        G.HighlightEdge(v, u);
        dfs(u);
        G.DimEdge(v, u);
    }
    G.DimNode(v);
}

void solve()
{
    int n = 7;
    adj.assign(n, vector<int>(0));
    G.TotalNodes(n);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(5);
    adj[2].push_back(6);
    G.AddEdge(0, 2);
    G.AddEdge(0, 1);
    G.AddEdge(1, 3);
    G.AddEdge(1, 4);
    G.AddEdge(2, 5);
    G.AddEdge(2, 6);
    dfs(0);
}
//// DO NOT DISTURB INT MAIN///////
int main()
{
    cout<<"{\"data\":[";
    solve();
    cout<<"{}]}";
}