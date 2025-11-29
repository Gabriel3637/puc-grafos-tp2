/*
#include "../inc/graph.hpp"
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <sstream>

using namespace std;

const double INF = 1e18;


// ====================================================================
// DMST (Edmonds–Tarjan / Chu–Liu) – retorna vetor de arestas escolhidas
// ====================================================================
static vector<Edge> dmst(int root, vector<Edge> edges, int N)
{
    vector<Edge> chosen_edges;

    while (true)
    {
        vector<double> in(N, INF);
        vector<int> pre(N, -1);
        vector<int> id(N, -1);
        vector<int> vis(N, -1);

        // Melhor aresta entrante por vértice
        for (auto &e : edges)
        {
            if (e.u != e.v && e.w < in[e.v])
            {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[root] = 0;

        // Se algum vértice não tem aresta de entrada -> DMST inexistente
        for (int i = 0; i < N; i++)
            if (in[i] == INF)
                return {};

        // Detectar ciclos
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1)
            {
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }

        // Se não tem ciclos → fim
        if (cnt == 0)
        {
            for (int i = 0; i < N; i++)
                if (i != root)
                    chosen_edges.push_back(Edge(pre[i], i, in[i]));
            return chosen_edges;
        }

        // Reindexar vértices sem ciclo
        for (int i = 0; i < N; i++)
            if (id[i] == -1)
                id[i] = cnt++;

        // Recriar lista de arestas para grafo contraído
        vector<Edge> newEdges;
        newEdges.reserve(edges.size());

        for (auto &e : edges)
        {
            int u = id[e.u];
            int v = id[e.v];
            double w = e.w;

            if (u != v)
                newEdges.push_back(Edge(u, v, w - in[e.v]));
        }

        edges = newEdges;
        root = id[root];
        N = cnt;
    }
}



// ============================================================
// Construtor
// ============================================================
Graph::Graph(int numVertices)
{
    vertexes.resize(numVertices);
    listaAdjacencia.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
        vertexes[i] = i;
}



// ============================================================
// toString()
// ============================================================
string Graph::toString()
{
    stringstream ss;

    for (size_t i = 0; i < listaAdjacencia.size(); i++)
    {
        ss << i << ": ";
        for (const auto &e : listaAdjacencia[i])
        {
            ss << "(" << e.u << " -> " << e.v << "), w=" << e.w << " | ";
        }
        ss << "\n";
    }

    return ss.str();
}



// ============================================================
// addEdge
// ============================================================
void Graph::addEdge(int u, int v, int w)
{
    listaAdjacencia[u].push_back(Edge(u, v, w));
}



// ============================================================
// optimumBranching()
//     → Monta vetor de arestas do grafo
//     → Roda DMST
//     → Retorna novo Graph contendo apenas as arestas da DMST
// ============================================================
Graph Graph::optimumBranching()
{
    int N = vertexes.size();

    // Construir lista de edges do grafo atual
    vector<Edge> edges;
    for (int u = 0; u < N; u++)
        for (auto &e : listaAdjacencia[u])
            edges.push_back(e);

    int root = 0; // raiz padrão

    vector<Edge> dmstEdges = dmst(root, edges, N);

    // Retorna grafo vazio se não existe DMST
    Graph g2(N);
    if (dmstEdges.empty())
        return g2;

    // Inserir apenas as arestas da DMST
    for (auto &e : dmstEdges)
        g2.addEdge(e.u, e.v, e.w);

    return g2;
}
*/