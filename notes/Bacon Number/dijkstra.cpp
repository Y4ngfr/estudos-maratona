#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;
const int MAXN = 1e5 + 5;   // máximo de nós no grafo

vector<pair<int, ll>> adj[MAXN]; // adj[u] = {(v1, peso1), (v2, peso2), ...}

typedef pair<ll, int> pli; // {dist, node}
/*
    Define a distância da origem (ll) até um nó.
    Essa definição será usada na priority_queue e portanto precisa que o elemento de ordenação
    esteja em primeiro lugar.
*/

ll dist[MAXN];

void dijkstra(int src, int qtd_nodos) {
    fill(dist, dist + qtd_nodos + 1, INF);
    /*
        Inicializa o array de distâncias:
        fill(primeiro, ultimo, valor).
        Observe que dist e dist + n + 1 são ponteiros.
        Além disso é necessário referenciar um elemento após o último [primeiro, ultimo)
    */

    dist[src] = 0;  // distancia da origem até ela mesmo é 0

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    /*
        priority_queue<pli, vector<pli>, greater<pli>> pq;
                       ^^^  ^^^^^^^^^^^^  ^^^^^^^^^^^^
                       tipo  container    comparador 
                       
        a priority_queue é uma fila que sempre mantém um elemento de maior prioridade no topo. 
        Nesse caso greater define a ordenação do menor para o maior (min-heap) o que garante que
        no topo sempre estará elemento de menor valor. Como os elementos são pares (pair<ll, int>) 
        ele vai comparar apenas o primeiro valor (ll). O container é a estrutura de dados interna 
        que a priority_queue usa para armazenar fisicamente os elementos.
    */


    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); 
        /*
            significa:
            ll d = pq.top().first;
            int u = pq.top().second;
        */

        pq.pop();   // remove do topo

        if (d > dist[u]) continue; 
        /*
            Note que entre src e um nodo u podem existir mais de um caminho.
            Quando isso acontece dist[u] vai atualizando, ou seja, durante a execução do
            algoritmo dist[u] pode receber o valor do pior caminho, em seguida de um caminho
            um pocuo melhor e depois finalmente o melhor caminho.
            Porém enquanto isso acontece a fila de prioridades não remove os caminhos ruins
            automaticamente, o que pode resultar em uma tentativa de comparação desatualizada.
            Com essa linha, impedimos isso.
        */

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
        /*
            percorre o vetor de pares da lista de adjacencia do nodo u.
            Verifica se a distancia da origem até u + o peso da aresta de u até v (w) é
            menor que a distância atual da origem até v (possivel mente INF).
            Se sim a distância da origem até v recebe a distancia até u + peso ded u até v.
            Em seguida adiciona-se na fila de prioridade o identificador da distancia da
            origem (src) até um nó v.
        */
    }
}