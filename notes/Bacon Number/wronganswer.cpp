#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = INT_MAX;
const ll MAXATORES = 1e6;
const ll MAXFILMES = 100;

struct filme;

typedef struct ator{

    ll id;
    vector<filme*> filmes;

} ator;

typedef struct filme{

    ll id;
    vector<ator*> atores;

} filme;

typedef pair<int, ator*> pli;

int dist[MAXATORES];
ll filme_anterior[MAXATORES]; // entrada: ator, saida: filme
ll ator_anterior[MAXATORES]; // entrada: filme, saida: ator

void dijkstra(vector<ator*> atores, vector<filme*> filmes, ll src, ll qtd_atores) 
{
    fill(dist, dist + qtd_atores + 1, INF);
    fill(filme_anterior, filme_anterior + qtd_atores + 1, -1);
    fill(ator_anterior, ator_anterior + qtd_atores + 1, -1);

    dist[src] = 0;
    filme_anterior[src] = -1;
    ator_anterior[src] = -1;

    priority_queue<pli, vector<pli>, greater<pli>> pq;

    pq.push({0, atores[src]});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); 

        pq.pop();

        if (d > dist[u->id]) continue; 

        for(filme* f : u->filmes){
            for(ator* a : f->atores){
                if(dist[u->id] + 1 < dist[a->id]){
                    dist[a->id] = dist[u->id] + 1;
                    pq.push({dist[a->id], a});

                    filme_anterior[a->id] = f->id;
                    ator_anterior[a->id] = u->id;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;

    cin >> n >> m; // n --> numero de filmes; m --> numero de atores

    vector<ator*> atores(m+1);
    vector<filme*> filmes(n+1);

    for(int i = 0; i < m+1; i++){
        atores[i] = new ator;
        atores[i]->id = i;
    }

    for (int i = 1; i < n + 1; i++) {
        int qtd_atores;
        cin >> qtd_atores;

        filmes[i] = new filme;
        filmes[i]->id = i;
        
        for(int j = 0; j < qtd_atores; j++){
            ll atorid;
            cin >> atorid;
            
            filmes[i]->atores.push_back(atores[atorid]);
            atores[atorid]->filmes.push_back(filmes[i]);
        }
    }
    
    int q;
    cin >> q;
    vector<array<ll,3>> consultas(q);
    
    for(int i = 0; i < q; i++){
        cin >> consultas[i][0] >> consultas[i][1];
        consultas[i][2] = i;
    }
    
    ll contagem[m+1]; // quantas vezes cada ator aparece nas consultas
    ostringstream saida[q];

    int qtd_q = q;
    
    while(qtd_q != 0){
        fill(contagem, contagem + m + 2, 0);

        ll ator_mais_frequente = 1;

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
        
        dijkstra(atores, filmes, ator_mais_frequente, m+1);

        for(auto it = consultas.begin(); it != consultas.end();)
        {
            auto consulta = *it;
            
            if(consulta[0] == ator_mais_frequente)
            {
                if(dist[consulta[1]] != INF){
                    stack<ll> pilha;
                    ll idx = consulta[1];

                    while(ator_anterior[idx] != -1){
                        pilha.push(idx);
                        pilha.push(filme_anterior[idx]);

                        idx = ator_anterior[idx];
                    }
                    pilha.push(idx);

                    saida[consulta[2]] << pilha.size() - pilha.size()/2 << endl;

                    while(!pilha.empty()){
                        saida[consulta[2]] << pilha.top() << " ";
                        pilha.pop();
                    }
                    
                    saida[consulta[2]] << endl;
                }
                else{
                    saida[consulta[2]] << -1 << endl;
                }

                it = consultas.erase(it); // após remoção retorna o próximo iterador válido
            }            
            else if(consulta[1] == ator_mais_frequente)
            {
                if(dist[consulta[0]] != INF){
                    stack<ll> pilha;
                    ll idx = consulta[0];

                    while(ator_anterior[idx] != -1){
                        pilha.push(idx);
                        pilha.push(filme_anterior[idx]);

                        idx = ator_anterior[idx];
                    }
                    pilha.push(idx);

                    saida[consulta[2]] << pilha.size() - pilha.size()/2 << endl;

                    while(!pilha.empty()){
                        saida[consulta[2]] << pilha.top() << " ";
                        pilha.pop();
                    }
                    
                    saida[consulta[2]] << endl;
                }
                else{
                    saida[consulta[2]] << -1 << endl;
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