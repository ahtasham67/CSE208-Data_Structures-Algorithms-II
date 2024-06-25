#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int parent[N];
int total_cost;
bool vis[N + 1];
int edgeCnt;

class edge
{
public:
    int a, b, w;
    edge() {}
    edge(int x, int y, int z)
    {
        a = x;
        b = y;
        w = z;
    }
    bool operator!=(const edge &other) const
    {
        return (a != other.a) || (b != other.b) || (w != other.w);
    }
    bool operator==(const edge &other) const
    {
        return (a == other.a) && (b == other.b) && (w == other.w);
    }
};

vector<edge> Edges;
vector<vector<edge> > FinalMSTset;

void make(int a)
{
    parent[a] = a;
}

int find(int a)
{
    if (parent[a] == a)
        return a;
    else
        return parent[a] = find(parent[a]);
}

bool cmp(edge a, edge b)
{
    return a.w < b.w;
}

void UNION(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    parent[b] = a;
}

void initialMST(vector<edge> edges)
{
    vector<edge> tmp;
    sort(edges.begin(), edges.end(), cmp);
    for (auto e : edges)
    {
        if (find(e.a) == find(e.b))
            continue;
        UNION(e.a, e.b);
        total_cost += e.w;
        edge ed(e.a, e.b, e.w);
        tmp.push_back(ed);
        edgeCnt++;
    }
    //cout << total_cost << endl;
    FinalMSTset.push_back(tmp);
}
bool isConnected(vector<edge> edges)
{
    int rep = find(edges[0].a);
    for (auto e : edges)
    {
        if (find(e.a) != rep || find(e.b) != rep)
        {
            return false;
        }
    }

    return true;
}

bool unq(const vector<edge> &tmp)
{
    for (const auto &vec : FinalMSTset)
    {
        if (tmp.size() != vec.size())
        {
            continue;
        }

        bool isEqual = true;
        for (int i = 0; i < tmp.size(); ++i)
        {
            if (tmp[i] != vec[i])
            {
                isEqual = false;
                break;
            }
        }

        if (isEqual)
        {
            return false;
        }
    }
    return true;
}

void isMST(vector<edge> edges)
{
    sort(edges.begin(), edges.end(), cmp);
    int totalWeight = 0;

    // Reset parent array before processing each subset
    for (int i = 0; i < N; i++)
    {
        parent[i] = i;
    }
    int cnt = 0;
    vector<edge> temp;
    for (auto e : edges)
    {
        if (find(e.a) == find(e.b))
            continue;

        UNION(e.a, e.b);
        edge E(e.a, e.b, e.w);
        temp.push_back(E);
        totalWeight += e.w;
        cnt++;
    }
    if (totalWeight == total_cost && isConnected(temp) && cnt == edgeCnt && unq(temp))
    {
        FinalMSTset.push_back(temp);
        temp.clear();
    }
}
