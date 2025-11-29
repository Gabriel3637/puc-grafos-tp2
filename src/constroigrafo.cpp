#include "../inc/graph.hpp"
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

const double INF = 1e18;

// -------------------------------------------------------
// Algoritmo de Edmonds–Tarjan (Chu–Liu)
// Retorna APENAS as arestas da DMST
// -------------------------------------------------------
static vector<Edge> dmst(int root, vector<Edge> edges, int N)
{
    vector<Edge> chosen_edges;

    while (true) {

        vector<double> in(N, INF);
        vector<int> pre(N, -1);
        vector<int> id(N, -1);
        vector<int> vis(N, -1);

        // Melhor aresta entrante por vértice
        for (auto &e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[root] = 0;

        // Se tem vértice sem aresta de entrada → DMST não existe
        for (int i = 0; i < N; i++)
            if (in[i] == INF)
                return {};

        // Detectar ciclos
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }

        // Não tem ciclo → fim
        if (cnt == 0) {
            for (int i = 0; i < N; i++)
                if (i != root)
                    chosen_edges.push_back({pre[i], i, in[i]});
            return chosen_edges;
        }

        // Reindexação: vértices fora do ciclo recebem novo id
        for (int i = 0; i < N; i++)
            if (id[i] == -1)
                id[i] = cnt++;

        // Gerar grafo contraído
        vector<Edge> newEdges;
        newEdges.reserve(edges.size());

        for (auto &e : edges) {
            int u = id[e.u];
            int v = id[e.v];
            double w = e.w;

            if (u != v)
                newEdges.push_back({u, v, w - in[e.v]});
        }

        edges = newEdges;
        root = id[root];
        N = cnt;
    }
}



// -------------------------------------------------------
// optimumBranching()
// Constrói um Graph contendo SOMENTE a DMST
// -------------------------------------------------------
Graph Graph::optimumBranching(int root, const vector<Edge>& edgesOriginal)
{
    int N = vertexes.size();

    // 1. Rodar DMST
    vector<Edge> dmstEdges = dmst(root, edgesOriginal, N);

    // 2. Criar grafo de retorno
    Graph result(N);

    // Se não existe DMST → grafo vazio
    if (dmstEdges.empty())
        return result;

    // 3. Inserir arestas escolhidas
    for (auto &e : dmstEdges)
        result.addEdge(e.u, e.v, e.w);

    return result;
}
