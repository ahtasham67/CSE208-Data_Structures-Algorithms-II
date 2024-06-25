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
vector<pair<int, pair<int, int> > > males;
vector<pair<int, pair<int, int> > > females;

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
    for (int i = 0; i <= V; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            // cout << rGraph[i][j] << " ";
            flow[i] += rGraph[i][j];
        }
        // cout << endl;
    }
    int temp = -1;
    for (int i = 1; i <= V; i++)
    {
        if (temp < flow[i])
        {
            // cout<<flow[i]<<" ";
            temp = flow[i];
            maxNode = i;
        }
    }
    cout << maxFlow << endl;
}

int main()
{
    freopen("in2.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        males.push_back(make_pair(a, make_pair(b, c)));
        // graph[a][b] = c;
        //  cout<<a<<" "<<b<<" "<<graph[a][b]<<endl;
    }
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        females.push_back(make_pair(a, make_pair(b, c)));
        // graph[a][b] = c;
        //  cout<<a<<" "<<b<<" "<<graph[a][b]<<endl;
    }
    int V = n + m + 2;
    for (int i = 2; i <= n + 1; i++)
    {
        graph[1][i] = 1;
    }

    for (int i = n + 2; i < V; i++)
    {
        graph[i][V] = 1;
    }

    int k = 0;
    for (int i = 2; i < n + 2; i++)
    {
        int f = 0;
        for (int j = n + 2; j < V; j++)
        {
            if (abs(males[k].first - females[f].first) <= 10 &&
                abs(males[k].second.first - females[f].second.first) <= 5 &&
                males[k].second.second == females[f].second.second)
            {
                graph[i][j] = 1;
            }
            f++;
        }
        k++;
    }

    // for (int i = 1; i <= V; i++)
    // {
    //     for (int j = 1; j <= V; j++)
    //     {

    //         cout << graph[i][j] << " ";
    //         // flow[i] += rGraph[i][j];
    //     }
    //     cout << endl;
    // }
    // int s, t;
    // cin >> s >> t;
    fordFulker(V, 1, V);
    return 0;
}
