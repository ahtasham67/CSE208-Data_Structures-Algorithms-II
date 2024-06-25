#include"header.cpp"

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
    int indx = 1;
    for (auto vec : FinalMSTset)
    {
        cout << indx << ": [";
        for (auto e : vec)
        {
            cout << "[" << e.a << "," << e.b << "," << e.w << "], ";
        }
        cout << "]" << endl;
        indx++;
    }
    return 0;
}