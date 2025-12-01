//#include "../inc/graph.hpp"  // ou ajuste do caminho conforme o build

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <vector>
#include "graph.hpp"
#include <stack>
#include <unordered_set>

class Dmsta{

    public:
    #define NIL -1

    // ---------- TARJAN SCC UTIL ----------
    void SCCUtil(int u,
                        std::vector<int> &disc,
                        std::vector<int> &low,
                        std::stack<int> &st,
                        std::vector<bool> &stackMember,
                        std::vector<std::vector<int>> &result,
                        std::vector<std::vector<Edge>> lista_e,
                        std::vector<int> &gv_teste
                    )
    {
        static int time = 0;

        disc[u] = low[u] = ++time;
        st.push(u);
        stackMember[u] = true;

        // Percorre as arestas de saída de u
        for (auto &e : lista_e[u]) {
            int v = e.v;

            if (disc[v] == NIL) {
                SCCUtil(v, disc, low, st, stackMember, result, lista_e, gv_teste);
                low[u] = std::min(low[u], low[v]);
            }
            else if (stackMember[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        // Se u é a raiz da SCC
        if (low[u] == disc[u]) {
            std::vector<int> component;

            while (st.top() != u) {
                int w = st.top();
                component.push_back(w);
                stackMember[w] = false;
                st.pop();
            }

            component.push_back(u);
            stackMember[u] = false;
            st.pop();

            for(int v : component)
                gv_teste[v] = result.size();
            result.push_back(component);
        }
    }

    std::vector<int> SCC(std::vector<std::vector<Edge>> lista_e)
    {
        int V = lista_e.size();

        std::vector<std::vector<int>> result;

        std::vector<int> disc(V, NIL);
        std::vector<int> low(V, NIL);
        std::vector<bool> stackMember(V, false);
        std::stack<int> st;
        std::vector<int> gv_teste(V);
        
        for (int i = 0; i < V; i++) {
            if (disc[i] == NIL) {
                SCCUtil(i, disc, low, st, stackMember, result, lista_e, gv_teste);
            }
        }


/*         std::cout << "Vetor de conjuto: " << std::endl;
        for(int t : gv_teste)
            std::cout << t << std::endl; */
        return gv_teste;
    }

    std::vector<int> findRootComponents(int vqtd, const std::vector<Edge>& edges, const std::vector<int>& scc) {
        int numComponents = *std::max_element(scc.begin(), scc.end()) + 1; // número de SCCs
        std::vector<bool> hasIncoming(numComponents, false);

        // Percorre todas as arestas do grafo original
        for (const auto& e : edges) {
            int uComp = scc[e.u];
            int vComp = scc[e.v];
            if (uComp != vComp) {
                hasIncoming[vComp] = true; // Se recebe uma aresta externa, não é root
            }
        }

        // Coleta os componentes sem arestas entrando
        std::vector<int> rootComponents;
        for (int i = 0; i < numComponents; ++i) {
            if (!hasIncoming[i]) {
                rootComponents.push_back(i);
            }
        }

        return rootComponents;
    }

    Dmsta(){};
    void optimumBranchingTarjan(int vqtd, std::vector<Edge> &edgesOriginals){
        //S = componente com a raiz
        //W = componente fracamente conexo contendo S
        //c(v,w) = valores da aresta (provavel peso)
        //root componet = componente raiz se nenhuma aresta entra nele
    
        //pré-passo: determinar CFCs
    
        //passo 1: escolher um vértice em que uma aresta > 0
        //selecionar a aresta de maior valor
        //adcionar a aresta em H
    
        //loop:
        //1: componente raiz que tem um vértice interno não examinado > 0
        //2: Achar o maior vértice não examinado
        //3:
        
        //passo 1
        std::sort(edgesOriginals.begin(), edgesOriginals.end(), [](Edge a, Edge b) {
            return a > b;
        });
        std::vector<Edge> H(vqtd);
        
        std::vector<bool> validacaoEntrada(vqtd);
        int count = 0;
        for(Edge &edge : edgesOriginals){
            if(edge.w >= 0 && !validacaoEntrada[edge.v]){
                H[count] = edge;
                count++;
                validacaoEntrada[edge.v] = true;
            }
            
        }

        for(Edge e : H){
            std::cout << e << std::endl;
        }

        
        std::vector<std::vector<Edge>> adj(vqtd);
        for (auto& e : H) adj[e.u].push_back(e);
        
        std::vector<int>scc = SCC(adj);
        std::cout << "Conjunto:" << std::endl;
        for(int d : scc){
            std::cout << d << std::endl;
        }
        std::vector<int> roots = findRootComponents(vqtd, H, scc);
        
        std::cout << "Root Components:" << std::endl;
        for (int r : roots) {
            std::cout << r << std::endl;
        }
        
    }

    std::vector<Edge> optimumBranchingGabow(int root, int n, const std::vector<Edge>& edges) {
        std::vector<Edge> resultEdges;

        // 1. Para cada vértice, seleciona a aresta de menor peso entrando nele
        std::vector<Edge> inEdge(n);
        std::vector<bool> hasInEdge(n, false);

        for (int i = 0; i < n; ++i) {
            if (i == root) continue; // raiz não precisa de aresta entrando
            uint8_t minW = std::numeric_limits<uint8_t>::max();
            for (const auto& e : edges) {
                if (e.v == i && e.w < minW) {
                    minW = e.w;
                    inEdge[i] = e;
                    hasInEdge[i] = true;
                }
            }
            if (!hasInEdge[i]) {
                // Grafo não é conectável a partir da raiz
                return {};
            }
        }

        // 2. Detectar ciclos
        std::vector<int> cycle(n, -1);
        int cid = 0;

        for (int i = 0; i < n; ++i) {
            int v = i;
            std::unordered_set<int> path;

            while (v != root && cycle[v] == -1 && path.find(v) == path.end()) {
                path.insert(v);
                v = inEdge[v].u;
            }

            if (v != root && cycle[v] == -1) {
                // Encontramos um ciclo
                for (int u : path) {
                    cycle[u] = cid;
                    if (u == v) break;
                }
                cid++;
            }
        }

        // 3. Sem ciclos: a MSA é simplesmente todas as inEdge
        if (cid == 0) {
            for (int i = 0; i < n; ++i) {
                if (i != root) {
                    resultEdges.push_back(inEdge[i]);
                }
            }
            return resultEdges;
        }

        // 4. Contrair ciclos e reconstruir o grafo
        std::vector<int> newId(n, -1);
        int newN = 0;

        for (int i = 0; i < n; ++i)
            if (cycle[i] == -1) newId[i] = newN++;
        for (int i = 0; i < n; ++i)
            if (cycle[i] != -1) newId[i] = newN + cycle[i];
        newN += cid;

        std::vector<Edge> newEdges;
        for (const auto& e : edges) {
            int u = newId[e.u];
            int v = newId[e.v];
            if (u != v) {
                uint8_t w = e.w;
                if (cycle[e.v] != -1) w -= inEdge[e.v].w; // ajustar peso
                newEdges.push_back(Edge(u, v, w));
            }
        }

        // 5. Chamada recursiva na versão contraída
        std::vector<Edge> recEdges = optimumBranchingGabow(newId[root], newN, newEdges);

        // 6. Expandir ciclos e reconstruir arestas finais
        resultEdges = recEdges;
        for (int i = 0; i < n; ++i) {
            if (cycle[i] != -1) {
                resultEdges.push_back(inEdge[i]);
            }
        }

        return resultEdges;
    }

    ~Dmsta(){

    }
};
