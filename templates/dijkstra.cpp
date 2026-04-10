#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;
const int MAXN = 1e5 + 5;

vector<pair<int, ll>> adj[MAXN];

typedef pair<ll, int> pli;

ll dist[MAXN];

void dijkstra(int src, int qtd_nodos) {
    fill(dist, dist + qtd_nodos + 1, INF);

    dist[src] = 0;

    priority_queue<pli, vector<pli>, greater<pli>> pq;

    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); 

        pq.pop();

        if (d > dist[u]) continue; 

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}