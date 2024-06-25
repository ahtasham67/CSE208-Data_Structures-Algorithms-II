#include "header.cpp"

int COUNT(edge ed)
{
    int cnt = 0;
    for (auto vec : FinalMSTset)
    {
        for (auto e : vec)
        {
            if (e == ed)
                cnt++;
        }
    }
    return cnt;
}
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        make(i);
    }

    for (int i = 0; i < m; i++)
    {
        edge e;
        cin >> e.a >> e.b >> e.w;
        Edges.push_back(e);
    }

    initialMST(Edges);
    for (int i = 0; i < N; i++)
    {
        parent[i] = 0;
    }
    int mstcnt = 0;
    for (int mask = 0; mask < (1 << Edges.size()); mask++)
    {
        vector<edge> temp(Edges);
        vector<edge> subset;
        for (int i = 0; i < Edges.size(); i++)
        {
            if ((mask & (1 << i)) != 0)
            {
                subset.push_back(Edges[i]);
            }
        }
        isMST(subset);
        subset.clear();
    }

    // cout << FinalMSTset.size() << endl;
    vector<int> critical_edge;
    vector<int> pseudo_critical_edge;
    int indx = 0;
    for (auto e : Edges)
    {
        if (COUNT(e) == FinalMSTset.size())
            critical_edge.push_back(indx);
        else if (COUNT(e) > 0 && COUNT(e) < FinalMSTset.size())
        {
            pseudo_critical_edge.push_back(indx);
        }

        indx++;
    }
    cout << "Critical edges :[";
    for (int j = 0; j < critical_edge.size(); j++)
    {
        if (j == critical_edge.size() - 1)
            cout << critical_edge[j] << "]";
        else
            cout << critical_edge[j] << ",";
    }
    cout << endl;
    cout << "Pseudo critical edges :[";
    for (int j = 0; j < pseudo_critical_edge.size(); j++)
    {
        if (j == pseudo_critical_edge.size() - 1)
            cout << pseudo_critical_edge[j] << "]";
        else
            cout << pseudo_critical_edge[j] << ",";
    }

    return 0;
}