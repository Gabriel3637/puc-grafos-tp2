
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
        int conflictEdgeId;
    };

private:
    // Vetores auxiliares alocados uma vez e reutilizados
    std::vector<int> bestInEdge;
    std::vector<int> minInWeight;
    std::vector<int> group;
    std::vector<int> visited;
    std::vector<int> cycleNode;

public:
    std::vector<int> chuLiuEdmonds(int N, int root, const std::vector<InternalEdge> &edges) {
        bestInEdge.assign(N, -1);
        minInWeight.assign(N, 1e9);
        group.assign(N, -1);
        visited.assign(N, -1);
        cycleNode.clear();

        // 1. Escolher a aresta de menor peso entrando em cada nó
        for (const auto &e : edges) {
            if (e.u == e.v) continue;
            if (e.w < minInWeight[e.v]) {
                minInWeight[e.v] = e.w;
                bestInEdge[e.v] = e.id;
            }
        }
        bestInEdge[root] = -1;

        // 2. Detectar ciclos
        int cycleCount = 0;
        for (int i = 0; i < N; ++i) {
            if (i == root) continue;
            int curr = i;
            while (curr != root && visited[curr] != i && group[curr] == -1) {
                visited[curr] = i;
                if (bestInEdge[curr] == -1) break;

                int parent = -1;
                for (const auto &e : edges)
                    if (e.id == bestInEdge[curr]) { parent = e.u; break; }

                if (parent == -1) break;
                curr = parent;
            }

            if (curr != root && visited[curr] == i) {
                // Ciclo encontrado
                cycleCount++;
                int v = curr;
                while (group[v] == -1) {
                    group[v] = cycleCount;
                    cycleNode.push_back(v);
                    int parent = -1;
                    for (const auto &e : edges)
                        if (e.id == bestInEdge[v]) { parent = e.u; break; }
                    v = parent;
                    if (v == curr) break;
                }
                break; // um ciclo por vez
            }
        }

        // 3. Sem ciclos
        if (cycleCount == 0) {
            std::vector<int> resultEdges;
            for (int i = 0; i < N; ++i)
                if (i != root && bestInEdge[i] != -1)
                    resultEdges.push_back(bestInEdge[i]);
            return resultEdges;
        }

        // 4. Contração do ciclo
        int newN = 0;
        std::vector<int> mapToNewNode(N);
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
        newEdges.reserve(edges.size());
        for (const auto &e : edges) {
            int u_new = mapToNewNode[e.u];
            int v_new = mapToNewNode[e.v];
            if (u_new == v_new) continue;

            InternalEdge ne = e;
            ne.u = u_new; ne.v = v_new; ne.conflictEdgeId = -1;

            if (v_new == superNodeID) {
                int weightInCycle = 0;
                int conflictId = bestInEdge[e.v];
                for (const auto &ce : edges)
                    if (ce.id == conflictId) { weightInCycle = ce.w; break; }
                ne.w -= weightInCycle;
                ne.conflictEdgeId = conflictId;
            }
            newEdges.push_back(ne);
        }

        int newRoot = mapToNewNode[root];
        std::vector<int> recursiveResult = chuLiuEdmonds(newN, newRoot, newEdges);

        // 5. Expansão
        std::vector<int> finalEdges;
        bool cycleBroken = false;
        for (int chosenId : recursiveResult) {
            int conflict = -1;
            for (const auto &ne : newEdges)
                if (ne.id == chosenId) { conflict = ne.conflictEdgeId; break; }

            finalEdges.push_back(chosenId);

            if (conflict != -1) {
                for (int nodeInCycle : cycleNode) {
                    int cycleEdgeId = bestInEdge[nodeInCycle];
                    if (cycleEdgeId != -1 && cycleEdgeId != conflict)
                        finalEdges.push_back(cycleEdgeId);
                }
                cycleBroken = true;
            }
        }

        if (!cycleBroken) {
            int maxW = -1e9, edgeToRemove = -1;
            for (int nodeInCycle : cycleNode) {
                int edgeId = bestInEdge[nodeInCycle];
                if (edgeId == -1) continue;
                int w = 0;
                for (const auto &e : edges) if (e.id == edgeId) w = e.w;
                if (w > maxW) { maxW = w; edgeToRemove = edgeId; }
            }
            for (int nodeInCycle : cycleNode) {
                int edgeId = bestInEdge[nodeInCycle];
                if (edgeId != -1 && edgeId != edgeToRemove) finalEdges.push_back(edgeId);
            }
        }

        return finalEdges;
    }

    std::vector<Edge> solveMaximumBranching(size_t numNodes, size_t root, const std::vector<Edge> &edges) {
        std::vector<InternalEdge> internalEdges;
        internalEdges.reserve(edges.size());
        for (size_t i = 0; i < edges.size(); ++i) {
            internalEdges.push_back({(int)edges[i].u, (int)edges[i].v, (int)edges[i].w, (int)i, -1});
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

    // ... (UnionFind e componentesFracamenteConexos continuam iguais)

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