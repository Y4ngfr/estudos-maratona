#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = INT_MAX;
/*
    distância entre dois atores não será tão grande para ser necessário ll, pois há no máximo 100 filmes
*/ 

const ll MAXNODES = 1e6;   // máximo de nós no grafo (máximo de atores)

vector<pair<ll, int>> adj[MAXNODES]; // adj[u] = {(v1, filme1}), (v2, filme2}), ...}
/*
    Não é necessário armazenar os pesos das arestas, pois todos serão igual a 1. Guardamos apenas
    o filme que interliga dois atores
*/

typedef pair<int, ll> pli; // {dist, node}

int dist[MAXNODES];
vector<ll> caminhos[MAXNODES];

void dijkstra(ll src, ll qtd_nodos) {
    fill(dist, dist + qtd_nodos + 1, INF);

    dist[src] = 0;

    priority_queue<pli, vector<pli>, greater<pli>> pq;

    caminhos[src] = {src};

    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); 

        pq.pop();

        if (d > dist[u]) continue; 

        for (auto [v, f] : adj[u]) {
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;

                caminhos[v] = caminhos[u];
                caminhos[v].push_back(f);
                caminhos[v].push_back(v);

                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;

    cin >> n >> m; // n --> numero de filmes; m --> numero de atores

    vector<ll> atores[n];

    ll a;
    string linha;
    istringstream linha_stream;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        linha.clear();
        getline(cin, linha);
        linha_stream.clear();
        linha_stream.str(linha);
        while(linha_stream >> a){
            atores[i].push_back(a);
        }
    }

    int q;
    cin >> q;
    vector<array<ll,3>> consultas(q);
    
    for(int i = 0; i < q; i++){
        cin >> consultas[i][0] >> consultas[i][1];
        consultas[i][2] = i;
    }

    // criação da lista de adjacencia
    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j <= atores[i][0] - 1; j++){ // atores[i][0] --> numero de atores
            for(int k = j + 1; k <= atores[i][0]; k++){
                adj[atores[i][j]].push_back({atores[i][k],  i+1});
                adj[atores[i][k]].push_back({atores[i][j],  i+1});
            }
        }
    }
    
    ll contagem[m+1]; // quantas vezes cada ator aparece nas consultas
    ostringstream saida[q];

    int qtd_q = q;
    
    while(qtd_q != 0){
        
        fill(contagem, contagem + m + 2, 0);

        ll ator_mais_frequente = 1;

        // cout << contagem[ator_mais_frequente] << endl;

        for(int j = 0; j < qtd_q; j++){
            contagem[consultas[j][0]]++;
            contagem[consultas[j][1]]++;
            
            if(contagem[consultas[j][0]] > contagem[ator_mais_frequente]){
                ator_mais_frequente = consultas[j][0];
            }

            if(contagem[consultas[j][1]] > contagem[ator_mais_frequente]){
                ator_mais_frequente = consultas[j][1];
            }
        }

        // cout << "teste" << endl;
        // cout << ator_mais_frequente << endl;

        dijkstra(ator_mais_frequente, m);

        for(auto it = consultas.begin(); it != consultas.end();)
        {
            auto consulta = *it;

            if(consulta[0] == ator_mais_frequente)
            {
                int tam_caminho = caminhos[consulta[1]].size();

                if(tam_caminho == 0){
                    saida[consulta[2]] << -1 << endl;
                }
                else{
                    saida[consulta[2]] << tam_caminho - tam_caminho/2 << endl;

                    for(int k = 0; k < tam_caminho; k++){
                        saida[consulta[2]] << caminhos[consulta[1]][k] << " ";
                    }
                    saida[consulta[2]] << endl;
                }

                it = consultas.erase(it); // após remoção retorna o próximo iterador válido
            }            
            else if(consulta[1] == ator_mais_frequente)
            {
                int tam_caminho = caminhos[consulta[0]].size();

                if(tam_caminho == 0){
                    saida[consulta[2]] << -1 << endl;
                    
                }
                else{
                    saida[consulta[2]] << tam_caminho + 1 << endl;

                    for(int k = tam_caminho; k >= 0; k++){
                        saida[consulta[2]] << caminhos[consulta[0]][k] << " ";
                    }
                    saida[consulta[2]] << endl;
                }

                it = consultas.erase(it);
            }
            else{
                it++;
            }
        }

        qtd_q = consultas.size();
    }

    for(int l = 0; l < q; l++){
        cout << saida[l].str();
    }


    return 0;
}