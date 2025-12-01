
#include <iostream>

#include "graph.hpp"

#include <cmath>
#include "Dmsta.cpp"
#include <cstdint>


class tarjanMSA{
    public:
    tarjanMSA(){}
    
    struct InternalEdge {
        int u, v;
        int w;
        int id; 
        int conflictEdgeId; // ID da aresta do ciclo que esta aresta substitui (se houver)
    };

    // Função Recursiva para encontrar as arestas
    // N: número de nós, root: raiz, edges: lista de arestas originais
    std::vector<int> chuLiuEdmonds(int N, int root, std::vector<InternalEdge> edges) {
        std::vector<int> bestInEdge(N, -1);
        std::vector<int> minInWeight(N, 1e9);

        // Firt steps: Encontrar a aresta de maior peso entrando em cada nó
        for (const auto& e : edges) {
            if (e.u == e.v) continue; // Ignora auto-laços
            if (e.w < minInWeight[e.v]) {
                minInWeight[e.v] = e.w;
                bestInEdge[e.v] = e.id; // Guarda o ID 
            }
        }

        bestInEdge[root] = -1;

        // Detectar Ciclos
        std::vector<int> group(N, -1);
        std::vector<int> visited(N, -1);
        std::vector<int> cycleNode; // Armazena nós do ciclo encontrado
        
        int cycleCount = 0;
        
        // Tenta encontrar pelo menos um ciclo
        for (int i = 0; i < N; ++i) {
            if (i == root) continue;
            
            int curr = i;
            //Visita os pais em busca de arestas visitadas na mesma iteração
            while (curr != root && visited[curr] != i && group[curr] == -1) {
                visited[curr] = i;
                if (bestInEdge[curr] == -1) break; // Sem pai (grafo desconexo), sai
                
                int parent = -1;
                for(const auto& e : edges) {
                    if(e.id == bestInEdge[curr]) {
                        parent = e.u;
                        break;
                    }
                }
                if (parent != -1) curr = parent;
                else break;
            }

            // Se encontrou ciclo
            if (curr != root && visited[curr] == i) {
                cycleCount++;
                int v = curr;
                // Marca todos os nós do ciclo com o mesmo ID de grupo
                while (group[v] == -1) {
                    group[v] = cycleCount;
                    cycleNode.push_back(v);
                    
                    // Avança no ciclo
                    int parent = -1;
                    for(const auto& e : edges) {
                        if(e.id == bestInEdge[v]) {
                            parent = e.u;
                            break;
                        }
                    }
                    v = parent;
                    if (v == curr) break;
                }
                break; // Tratamos apenas um ciclo por nível 
            }
        }

        //  Sem ciclos 
        if (cycleCount == 0) {
            std::vector<int> resultEdges;
            for (int i = 0; i < N; ++i) {
                if (i != root && bestInEdge[i] != -1) {
                    resultEdges.push_back(bestInEdge[i]);
                }
            }
            return resultEdges;
        }

        //Contração 
        int newN = 0;
        std::vector<int> mapToNewNode(N);
        
        // Mapeia nós do ciclo para um único Supernó
        int superNodeID = -1;
        for (int i = 0; i < N; ++i) {
            if (group[i] != -1) {
                if (superNodeID == -1) superNodeID = newN++;
                mapToNewNode[i] = superNodeID;
            } else {
                mapToNewNode[i] = newN++;
            }
        }

        std::vector<InternalEdge> newEdges;
        
        // Constrói as arestas do novo grafo contraído
        for (const auto& e : edges) {
            int u_new = mapToNewNode[e.u];
            int v_new = mapToNewNode[e.v];

            if (u_new != v_new) {
                InternalEdge ne;
                ne.u = u_new;
                ne.v = v_new;
                ne.id = e.id; // Mantém o ID original para referência final
                ne.conflictEdgeId = -1;

                if (v_new == superNodeID) {
                    int weightInCycle = 0;
                    // Acha o peso da aresta do ciclo que entra em e.v
                    int conflictId = bestInEdge[e.v];
                    for(const auto& ce : edges) {
                        if (ce.id == conflictId) {
                            weightInCycle = ce.w;
                            break;
                        }
                    }

                    ne.w = e.w - weightInCycle;
                    ne.conflictEdgeId = conflictId; // Se escolhermos esta aresta, removemos 'conflictId'
                } else {
                    // Aresta normal ou saindo do ciclo
                    ne.w = e.w;
                }
                newEdges.push_back(ne);
            }
        }

        int newRoot = mapToNewNode[root];
        std::vector<int> recursiveResult = chuLiuEdmonds(newN, newRoot, newEdges);

        // EXPANSÃO
        std::vector<int> finalEdges;
        bool cycleBroken = false;

        // Adiciona arestas escolhidas pela recursão
        for (int chosenId : recursiveResult) {
            int conflict = -1;
            for(const auto& ne : newEdges) {
                if (ne.id == chosenId) {
                    conflict = ne.conflictEdgeId;
                    break;
                }
            }
            
            finalEdges.push_back(chosenId);
            
            if (conflict != -1) {
                // Adiciona arestas do ciclo, exceto a conflituosa
                for (int nodeInCycle : cycleNode) {
                    int cycleEdgeId = bestInEdge[nodeInCycle];
                    if (cycleEdgeId != -1 && cycleEdgeId != conflict) {
                        finalEdges.push_back(cycleEdgeId);
                    }
                }
                cycleBroken = true;
            }
        }


        if (!cycleBroken) {
            // Procura a aresta de maior peso dentro do ciclo para quebrar
            int maxW = -1e9;
            int edgeToRemove = -1;
            
            for (int nodeInCycle : cycleNode) {
                int edgeId = bestInEdge[nodeInCycle];
                if (edgeId != -1) {
                    int w = 0;
                    for(const auto& e : edges) if(e.id == edgeId) w = e.w;
                    
                    if (w > maxW) {
                        maxW = w;
                        edgeToRemove = edgeId;
                    }
                }
            }
            
            for (int nodeInCycle : cycleNode) {
                int edgeId = bestInEdge[nodeInCycle];
                if (edgeId != -1 && edgeId != edgeToRemove) {
                    finalEdges.push_back(edgeId);
                }
            }
        }

        return finalEdges;
    }


    std::vector<Edge> solveMaximumBranching(size_t numNodes, size_t root, std::vector<Edge> edges) {
        std::vector<InternalEdge> internalEdges;
        internalEdges.reserve(edges.size());
        for (size_t i = 0; i < edges.size(); ++i) {
            InternalEdge ie;
            ie.u = (int)edges[i].u;
            ie.v = (int)edges[i].v;
            ie.w = (int)edges[i].w;
            ie.id = (int)i; 
            ie.conflictEdgeId = -1;
            internalEdges.push_back(ie);
        }

        std::vector<int> selectedIndices = chuLiuEdmonds((int)numNodes, (int)root, internalEdges);

        std::vector<Edge> solution;
        long long totalWeight = 0;
        for (int idx : selectedIndices) {
            solution.push_back(edges[idx]);
            totalWeight += edges[idx].w;
        }
        
        std::cout << "Peso Total da Arborescencia Mínima: " << totalWeight << std::endl;
        return solution;
    }

    struct UnionFind {
        std::vector<int> parent, rank;

        UnionFind(int n){
            parent.resize(n);
            rank.resize(n, 0);
            for(int i = 0; i < n; i++)
                parent[i] = i;
        }

        int find(int x){
            if(parent[x] != x)
                parent[x] = find(parent[x]); // path compression
            return parent[x];
        }

        void unite(int a, int b){
            a = find(a);
            b = find(b);
            if(a == b) return;

            if(rank[a] < rank[b]) parent[a] = b;
            else if(rank[a] > rank[b]) parent[b] = a;
            else{
                parent[b] = a;
                rank[a]++;
            }
        }
    };

    std::vector<int> componentesFracamenteConexos(int V, std::vector<Edge> edges) {

        UnionFind uf(V);

        // Para componentes FRACAMENTE conexos,
        // ignoramos a direção das arestas e unimos u <-> v
        for (auto &e : edges) {
        uf.unite(e.u, e.v);
    }

        // Cada vértice recebe o ID do seu componente
        std::vector<int> comp(V);
        for(int i = 0; i < V; i++)
            comp[i] = uf.find(i);

        return comp;
    }

    ~tarjanMSA(){}
};