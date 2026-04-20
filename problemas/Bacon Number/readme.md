# Essa é uma análise do problema Bacon Number 
### (https://codeforces.com/gym/105327/problem/B)

Nomeei os arquivos das tentativas de soluções com o seu respectivo retorno no codeforces.

#### Ideia inicial da solução
Nos dois casos de erro de runtimeerror e wronganswer a ideia da solução foi utilizar o algoritmo de dijkstra para encontrar o menor caminho de um ator para outro. Como são muitas consultas, utilizei uma ideia de algoritmo de solucionar em ordem de atores que mais aparecem nas consultas, buscando assim chamar a função de dijkstra o mínimo possível.


#### Primeira tentativa (Runtimeerror)
Na primeira tentativa utilizei apenas atores como nodos do grafo, os filmes estão nas arestas (o peso da aresta não é determinado pelo filme, o peso é sempre igual à 1). O problema é que a criação dessa lista de adjascencia é potencialmente muito custosa pois cada ator de um filme tem que estar conectado a todos os outros do mesmo filme, ou seja, O(n²).
Além disso, a gracação dos caminhos é feita de maneira ineficiente e consome muita memória.

#### Segunda tentativa (timelimit)
Na segunda tentativa utilizei tanto os atores quanto os filmes como nodos do grafo e uma lista de adjscencias implementada de forma um pouco diferente (criei as estruturas para representar ator e filme). Assim, em um filme ao invés de cada ator precisar estar conectado a todos os outros, apenas é necessário que cada ator esteja conectado ao filme O(n) e que o filme esteja conectado a todos os atores O(n), resultando em um tempo linear.
Além disso, a recontrução do caminho é feita apenas guardando o ator e filme antecessor de cada ator no caminho mais curta que o dijkstra descobriu.

#### Dijkstra
Para utilizar o dijkstra de forma eficiente realizei uma revisão do algoritmo. No arquivo dijkstra.cpp deixei uma explicação sobre o seu funcionamento, isso serviu como um estudo para relembrar alguns conceitos e revisar o algoritmo de dijkstra.