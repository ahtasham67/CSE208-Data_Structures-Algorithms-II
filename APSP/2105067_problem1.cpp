#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <bits/stdc++.h>
using namespace std;

const int N = 500;
int dist[N][N];
int cnt[N];
const int INF = 99999;

void floydWarsh(int n)
{

    // for each level k
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                //  dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int x, y, wt;
        cin >> x >> y >> wt;
        dist[x][y] = wt;
        dist[y][x] = wt;
    }
    int t;
    cin >> t;
    floydWarsh(n);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         if (dist[i][j] == 1e5 + 10)
    //             cout << "INF ";
    //         else
    //             cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int minCnt = INF;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] != INF && dist[i][j] != 0 && dist[i][j] <= t)
                cnt[i]++;
        }
        minCnt = min(minCnt, cnt[i]);
    }
    // cout << endl;
    //  for (int i = 1; i <= n; i++)
    //  {
    //      cout << cnt[i] << " ";
    //  }
    // cout << endl;
    // cout << minCnt << endl;
    for (int i = 1; i <= n; i++)
    {
        if (minCnt == cnt[i])
        {
            cout << i << " ";
        }
    }
}
