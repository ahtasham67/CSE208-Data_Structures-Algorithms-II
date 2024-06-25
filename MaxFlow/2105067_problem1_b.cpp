#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
//#include <bits/stdc++.h>
using namespace std;

const int N = 51;
int graph[N][N];
int flow[N];

bool bfs(int rGraph[N][N], int s, int t, int V, int par[]);
void fordFulker(int V, int s, int t);

bool bfs(int rGraph[N][N], int s, int t, int V, int par[])
{
    bool vis[V + 1];
    memset(vis, 0, V + 1);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    par[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= V; v++)
        {
            if (!vis[v] && rGraph[u][v] > 0)
            {
                if (v == t)
                {
                    par[v] = u;
                    return true;
                }
                q.push(v);
                par[v] = u;
                vis[v] = true;
            }
        }
    }
    return false;
}

void dfs(int rGraph[N][N], int s, bool visited[], int V)
{
    visited[s] = true;
    for (int i = 1; i <= V; i++)
        if (rGraph[s][i] && !visited[i])
            dfs(rGraph, i, visited, V);
}

void fordFulker(int V, int s, int t)
{
    int parent[V + 1];
    int rGraph[N][N];
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            rGraph[i][j] = graph[i][j];
        }
    }
    int maxFlow = 0;
    while (bfs(rGraph, s, t, V, parent))
    {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    int maxNode = -1;
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            // cout << rGraph[i][j] << " ";
            flow[i] += rGraph[i][j];
        }
        // cout << endl;
    }
    int temp = -1;
    for (int i = 1; i < V; i++)
    {
        if (temp < flow[i])
        {
            // cout<<flow[i]<<" ";
            temp = flow[i];
            maxNode = i;
        }
    }
    //cout << maxFlow << " " << maxNode << endl;
    // cout << endl;
    // cout << maxFlow << endl;
    bool visited[V + 1];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited, V);
    int mincutflow = 0;
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            if (visited[i] && !visited[j] && graph[i][j])
            {
                //cout << i << " - " << j << endl;
                mincutflow += graph[i][j];
            }

    vector<int> s1, s2;

    for (int i = 1; i <= V; i++)
    {
        if (visited[i])
            s1.push_back(i);
        else
            s2.push_back(i);
    }
    cout << "[ {";
    for (int i = 0; i < s1.size(); i++)
    {
        if (i == s1.size() - 1)
            cout << s1[i] << "}";
        else
            cout << s1[i] << ",";
    }
    cout<<" , {";
    for (int i = 0; i < s2.size(); i++)
    {
        if (i == s2.size() - 1)
            cout << s2[i] << "}";
        else
            cout << s2[i] << ",";
    }
    cout << " ]"<<endl;
    //cout << endl;
    cout << mincutflow << endl;
}

int main()
{
    freopen("in1.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a][b] = c;
        // cout<<a<<" "<<b<<" "<<graph[a][b]<<endl;
    }
    int s, t;
    cin >> s >> t;
    fordFulker(n, s, t);
    return 0;
}
