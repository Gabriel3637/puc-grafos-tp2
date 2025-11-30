#pragma once

#include "graph.hpp"
#include <list>
#include <algorithm>



class Mst
{
  private:
    // só pra tirar o erro
    std::vector<Edge> _e;

  public:
    Mst(){
        _e = {};
    }


    std::vector<size_t> generateMST(std::vector<Edge> edgesOriginals, size_t vqtd, int hipK){
        std::cout << "Teste 2.2" << std::endl;

        //Declaração de variáveis
        std::vector<Edge> resp(vqtd - 1); //Contem um arvore geradora mínima
        std::vector<std::list<Edge>> cluster(vqtd); //Como as AGMs de todos os conjuntos
        std::vector<u_int8_t> IntConj(vqtd, 0); //Vetor para armazenar a maior aresta de cada conjunto

        size_t countMST = 0; //Contador para montar a AGM em resp
        std::vector<size_t> unionfind(vqtd); //Vetor para gerenciar o union find

        //Inicialização do union find isolando os vértices 
        for(size_t i = 0; i < vqtd; i++){
            unionfind[i] = i;
        }


        std::list<Edge> edgesSorted(edgesOriginals.begin(), edgesOriginals.end()); //Copia profunda do vetor de arestas
        //Usei lista para facilitar as operações de inserção e remoção
        
        edgesSorted.sort(); //Ordena a lista segundo a sobrecarda do operador em Edge

        //Realizar a operação do Kruskal
        for(size_t i = 0; i < edgesOriginals.size(); i++){

            Edge edgeInsert = edgesSorted.front(); //Seleciona o primeiro item do vetor
            edgesSorted.pop_front(); //Remove o primeiro item

            //Se pertencem a conjuntos diferentes
            if(unionfind[edgeInsert.u] != unionfind[edgeInsert.v]) {
                int IntConjU = (int)IntConj[unionfind[edgeInsert.u]]; //Identifica o maior peso das arestas do conjunto do vertice U do edge
                /* if(cluster[unionfind[edgeInsert.u]].size() > 0){
                    IntConjU = (*std::max_element(cluster[unionfind[edgeInsert.u]].begin(), cluster[unionfind[edgeInsert.u]].end())).w;
                } */

                int IntConjV = (int)IntConj[unionfind[edgeInsert.v]]; //Identifica o maior peso das arestas do conjunto do vertice V do edge
                /* if(cluster[unionfind[edgeInsert.v]].size() > 0){
                    IntConjV = (*std::max_element(cluster[unionfind[edgeInsert.v]].begin(), cluster[unionfind[edgeInsert.v]].end())).w;
                } */


                double TalU = (hipK/std::count(unionfind.begin(), unionfind.end(), unionfind[edgeInsert.u])); //Calcula tal do conjunto do vertice U com const k
                double TalV = (hipK/std::count(unionfind.begin(), unionfind.end(), unionfind[edgeInsert.v])); //Calcula tal do conjunto do vertice V com const k

                std::cout << "IntU: " << IntConjU << "IntV:" << IntConjV << std::endl;

                std::cout << "TalU: " << TalU << "TalV: " << TalV << std::endl;

                //Determina o Mint
                double MInt = std::min((TalU + IntConjU), (TalV + IntConjV));

                //Verifica D
                bool D = edgeInsert.w > MInt;

                std::cout << "D: " << D << std::endl;

                //Se D então podem formar o conjunto 
                if(!D){
                    //Realiza a operação menos custosa, move as arestas do conjunto com menor quantidade de arestas
                    if(cluster[unionfind[edgeInsert.u]].size() > cluster[unionfind[edgeInsert.v]].size()){
                        size_t conjunctV = unionfind[edgeInsert.v];//Armazena o identificado do conjunto de V em edge

                        //Realiza as alterações em todos que pertencem ao conjunto de V para o conjunto de U
                        for(size_t j = 0; j < vqtd; j++){
                            if(unionfind[j] == conjunctV)
                                unionfind[j] = unionfind[edgeInsert.u];
                        }

                        cluster[unionfind[edgeInsert.u]].splice(cluster[unionfind[edgeInsert.u]].end(), cluster[conjunctV]); //Adiciona a aresta ao conjunto de U
                        IntConj[unionfind[edgeInsert.u]] = edgeInsert.w; // Atualiza o maior peso
                        cluster[unionfind[edgeInsert.u]].push_back(edgeInsert); // Insere a aresta atualmente observada
                    } else {
                        size_t conjunctU = unionfind[edgeInsert.u]; //Armazena o identificado do conjunto de U em edge

                        //Realiza as alterações em todos que pertencem ao conjunto de U para o conjunto de V
                        for(size_t j = 0; j < vqtd; j++){
                            if(unionfind[j] == conjunctU)
                                unionfind[j] = unionfind[edgeInsert.v];
                        }
                        cluster[unionfind[edgeInsert.v]].splice(cluster[unionfind[edgeInsert.v]].end(), cluster[conjunctU]); //Adiciona a aresta ao conjunto de V
                        IntConj[unionfind[edgeInsert.v]] = edgeInsert.w; // Atualiza o maior peso
                        cluster[unionfind[edgeInsert.v]].push_back(edgeInsert); // Insere a aresta atualmente observada
                    }
                }
                    
                //Cria arvore isso tem que ser alterado, vou alterar
                resp[countMST] = edgeInsert;
                countMST++;
            }
        }

        for(size_t u : unionfind){
            std::cout << u << std::endl;
        }

        std::optional<size_t> anterior = std::nullopt;
        for(size_t i : unionfind){
            if(anterior != i){
                std::cout << "Cluster: " << std::endl;
                std::list<Edge> currentCluster = cluster[i];
                for(Edge j : currentCluster){
                    std::cout << j << std::endl;
                }
                anterior = i;
            }
        }

        //Retorno
        return unionfind;
    }
    ~Mst(){

    }

};