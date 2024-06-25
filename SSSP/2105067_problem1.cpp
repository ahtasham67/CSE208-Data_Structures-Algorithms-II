#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, pair<int, int> > State; // (cost, (city, gas))


int findMinCost(int source, int destination, int capacity, vector<vector<pair<int, int> > >& graph, vector<int>& gasPrices)
{
    priority_queue<State, vector<State>, greater<State> > pq;
    vector<vector<int> > dist(graph.size(), vector<int>(capacity + 1, INT_MAX));
    pq.push(make_pair(0, make_pair(source, 0)));
    dist[source][0] = 0;

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int u = pq.top().second.first;
        int gas = pq.top().second.second;
        pq.pop();

        //state is already processed
        if (cost > dist[u][gas])
            continue;

        // Buy 1 liter of gas
        if (gas < capacity && cost + gasPrices[u] < dist[u][gas + 1])
        {
            dist[u][gas + 1] = cost + gasPrices[u];
            pq.push(make_pair(dist[u][gas + 1], make_pair(u, gas + 1)));
        }

        // Move to adjacent cities
        for (auto& neighbor : graph[u])
        {
            int v = neighbor.first;
            int distance = neighbor.second;

            if (gas >= distance && cost < dist[v][gas - distance])
            {
                dist[v][gas - distance] = cost;
                pq.push(make_pair(dist[v][gas - distance], make_pair(v, gas - distance)));
            }
        }
    }

    int minCost = INT_MAX;
    for (int i = 0; i <= capacity; ++i)
    {
        minCost = min(minCost, dist[destination][i]);
    }
    
    if(minCost==INT_MAX) return -1;
    return minCost;
}

int main()
{
    int N, M, C, S, D;
    cin >> N >> M >> C;

    vector<int> gasPrices(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        cin >> gasPrices[i];
    }

    vector<vector<pair<int, int> > > graph(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back(make_pair(v, d));
        graph[v].push_back(make_pair(u, d));
    }

    cin >> S >> D;

    int result = findMinCost(S, D, C, graph, gasPrices);

    if (result == -1)
    {
        cout << "impossible" << endl;
    }
    else
    {
        cout << result << endl;
    }

    return 0;
}
