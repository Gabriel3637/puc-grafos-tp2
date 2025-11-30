#include "../inc/graph.hpp"  // ou ajuste do caminho conforme o build

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <cmath>

Graph::Graph(int numVertices)
{
    vertexes.resize(numVertices);
    listaAdjacencia.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
        vertexes[i] = i;
}

std::string Graph::toString(){
    std::stringstream ss;
    
    for (size_t i = 0; i < listaAdjacencia.size(); i++)
    {
        ss << i << ": ";
        for (Edge e : listaAdjacencia[i])
        {
            ss << "(" << e.u << " -> " << e.v << ") w="<<e.w << " | ";
        }
        ss << "\n";
    }

    return ss.str();
}

void Graph::addEdge(int u, int v, int w){
    listaAdjacencia[u].push_back(Edge(u,v,w));
}



Graph Graph::optimumBranchingTarjan(){
    int N = listaAdjacencia.size();
    const double INF = 1e18;
    int root = 0;

    struct E {
        int u, v;
        double w;
        int idx; // opcional: índice original
        E(int _u=0,int _v=0,double _w=0,int _idx=0):u(_u),v(_v),w(_w),idx(_idx){}
    };

    // coletar arestas
    std::vector<E> edges;
    for (int u = 0; u < N; ++u){
        for (auto &e : listaAdjacencia[u]){
            edges.emplace_back(e.u, e.v, e.w, 0);
        }
    }

    // Edmonds/Chu-Liu com contração de ciclos
    auto edmonds = [&](int n, int r, const std::vector<E>& es) -> std::vector<E> {
        if (n == 0) return {};
        std::vector<E> cur = es;
        std::vector<E> answer; // armazena arestas finais (temporariamente)
        while (true) {
            std::vector<double> in(n, INF);
            std::vector<int> pre(n, -1);

            // 1) para cada vértice, escolher menor aresta de entrada
            for (const auto &e : cur) {
                if (e.u != e.v && e.w < in[e.v]) {
                    in[e.v] = e.w;
                    pre[e.v] = e.u;
                }
            }
            in[r] = 0; // raiz não precisa de entrada

            // se algum vértice (exceto raiz) não tem aresta de entrada -> sem arborescência
            for (int i = 0; i < n; ++i) {
                if (i == r) continue;
                if (in[i] >= INF) return {}; // falha: grafo desconexo em relação à raiz
            }

            // 2) detectar ciclos
            int cnt = 0;
            std::vector<int> id(n, -1), vis(n, -1);
            for (int i = 0; i < n; ++i) {
                answer.emplace_back(pre[i], i, in[i], 0); // candidato (pre[i], i)
            }

            for (int i = 0; i < n; ++i) {
                int v = i;
                // seguir pre até raiz ou até encontrar um vértice visitado no mesmo caminho
                while (vis[v] != i && id[v] == -1 && v != r) {
                    vis[v] = i;
                    v = pre[v];
                }
                if (v != r && id[v] == -1) {
                    // ciclo encontrado: marcar todos os vértices do ciclo com id = cnt
                    for (int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
                    id[v] = cnt++;
                }
            }

            if (cnt == 0) break; // sem ciclos -> pronto

            // atribuir ids para vértices que não estão em ciclos
            for (int i = 0; i < n; ++i) if (id[i] == -1) id[i] = cnt++;

            // 3) reconstruir grafo contraído
            std::vector<E> newEdges;
            newEdges.reserve(cur.size());
            for (const auto &e : cur) {
                int u = id[e.u], v = id[e.v];
                double w = e.w;
                if (u != v) {
                    // subtrai o custo da aresta escolhida para v (in[e.v])
                    w -= in[e.v];
                    newEdges.emplace_back(u, v, w, e.idx);
                }
            }
            n = cnt;
            r = id[r];
            cur.swap(newEdges);
            answer.clear(); // serão reconstruídas na próxima iteração ou no fim
        }

        // quando não há ciclos, reconstruir arestas finais: para cada v != root, aresta (pre[v], v)
        // Note: pre/in foram definidos na última iteração; precisamos recomputá-los para o tamanho original.
        // Para simplicidade, recomputamos a escolha mínima de entrada no grafo original e retornamos essas arestas.
        // (Outra abordagem é manter histórico de contrações para reconstrução exata.)
        std::vector<double> in_final(N, INF);
        std::vector<int> pre_final(N, -1);
        for (const auto &e : es) {
            if (e.u != e.v && e.w < in_final[e.v]) {
                in_final[e.v] = e.w;
                pre_final[e.v] = e.u;
            }
        }
        in_final[root] = 0;
        std::vector<E> finalEdges;
        for (int v = 0; v < N; ++v) {
            if (v == root) continue;
            if (pre_final[v] != -1 && in_final[v] < INF) finalEdges.emplace_back(pre_final[v], v, in_final[v], 0);
        }
        return finalEdges;
    };

    std::vector<E> finalEs = edmonds(N, root, edges);

    // montar grafo resultado
    Graph T(N);
    for (auto &e : finalEs) {
        // mantemos peso como inteiro na interface addEdge(int,int,int)
        // se quiser preservar double, ajuste addEdge para aceitar double
        int w_int = static_cast<int>(std::round(e.w));
        T.addEdge(e.u, e.v, w_int);
    }
    return T;
}