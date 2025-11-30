#pragma once

#include "graph.hpp"
#include <algorithm>
#include <vector>

class Mst
{
  private:
    std::vector<Edge> _e;

    size_t find(std::vector<size_t> &disjointUnion, size_t i)
    {
        // Encontra a raíz absoluta
        size_t root = i;
        while (disjointUnion[root] != root)
        {
            root = disjointUnion[root];
        }

        // Faz todos apontarem para a raiz (otimização)
        size_t curr = i;
        while (curr != root)
        {
            size_t next = disjointUnion[curr];
            disjointUnion[curr] = root;
            curr = next;
        }

        return root;
    }

  public:
    Mst() { _e = {}; }

    std::vector<size_t> generateMST(std::vector<Edge> &edgesOriginals,
                                    size_t vertexCount, int k)
    {
        // Declaração de variáveis
        std::vector<Edge> resp(vertexCount -
                               1); // Contem um arvore geradora mínima

        std::vector<float> IntConj(
            vertexCount,
            0.0f); // Vetor para armazenar a maior aresta de cada conjunto

        size_t countMST = 0; // Contador para montar a AGM em resp
        std::vector<size_t> unionfind(vertexCount); // Vetor para gerenciar o
                                                    // union find

        std::vector<size_t> sizes(vertexCount, 1);

        // Inicialização do union find isolando os vértices 
        for (size_t i = 0; i < vertexCount; i++)
        {
            unionfind[i] = i;
        }

        std::sort(edgesOriginals.begin(), edgesOriginals.end());

        // Realizar a operação do Kruskal
        for (const auto &edgeInsert : edgesOriginals)
        {
            size_t u = find(unionfind, edgeInsert.u);
            size_t v = find(unionfind, edgeInsert.v);

            // Se pertencem a conjuntos diferentes
            if (unionfind[edgeInsert.u] != unionfind[edgeInsert.v])
            {
                int IntConjU = (int)
                    IntConj[unionfind[edgeInsert.u]]; // Identifica o maior peso
                                                      // das arestas do conjunto
                                                      // do vertice U do edge

                int IntConjV = (int)
                    IntConj[unionfind[edgeInsert.v]]; // Identifica o maior peso
                                                      // das arestas do conjunto
                                                      // do vertice V do edge

                float TalU = k / sizes[u]; // Calcula tal do conjunto
                                           // do vertice U com const k
                float TalV = k / sizes[v]; // Calcula tal do conjunto
                                           // do vertice V com const k

                // Determina o Mint
                float MInt = std::min((TalU + IntConjU), (TalV + IntConjV));

                // Verifica D
                bool D = edgeInsert.w > MInt;

                // Se D então podem formar o conjunto 
                if (!D)
                {
                    unionfind[u] = v;
                    sizes[v] += sizes[u];
                    IntConj[v] = std::max<float>(
                        {IntConj[v], IntConj[u], (float)edgeInsert.w});
                }
            }
        }

        // Convertendo a estrutura em ids de conjuntos
        std::vector<size_t> final_ids(vertexCount);
        for (size_t i = 0; i < vertexCount; i++)
        {
            final_ids[i] = find(unionfind, i);
        }

        return final_ids;
    }
    ~Mst() {}
};
