#include <iostream>
#include <vector>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

int bellmanFord(int n, int m, vector<pair<int, pair<int, int> > > edges, int src, int dest) {
    vector<int> dist(n + 1, INF);
    dist[src] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = edges[j].second.first;
            int v = edges[j].second.second;
            int w = edges[j].first;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        int u = edges[j].second.first;
        int v = edges[j].second.second;
        int w = edges[j].first;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return INF;
        }
    }

    return dist[dest];
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int> > > edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
    }

    int A, B, L, H, S, D;
    cin >> A >> B >> L >> H >> S >> D;

    int originalDistance = bellmanFord(n, m, edges, S, D);

    if (originalDistance == INF) {
        cout << "impossible" << endl;
        return 0;
    }

    int minDistance = INF;
    int weight = -1;

    for (int edgeWeight = L; edgeWeight <= H; ++edgeWeight) {
        edges.push_back(make_pair(edgeWeight, make_pair(A, B)));
        int newDistance = bellmanFord(n, m + 1, edges, S, D);
        edges.pop_back();

        if (newDistance != INF && newDistance < minDistance) {
            minDistance = newDistance;
            weight = edgeWeight;
        }
    }

    if (weight == -1) {
        cout << "impossible" << endl;
    } else {
        cout << weight << " " << minDistance << endl;
    }

    return 0;
}
