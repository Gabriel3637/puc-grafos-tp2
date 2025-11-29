/*
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;
    double w;
};

const double INF = 1e18;

// Distância Euclidiana no espaço RGB
double rgbDist(const array<int,3>& a, const array<int,3>& b) {
    double dr = a[0] - b[0];
    double dg = a[1] - b[1];
    double db = a[2] - b[2];
    return sqrt(dr*dr + dg*dg + db*db); 
}

/*
    Edmonds–Tarjan (Chu-Liu/Edmonds)
    Retorna o custo total da arborecência mínima dirigida a partir de root
*/
/*
double dmst(int root, vector<Edge> edges, int N) {
    double result = 0;

    while (true) {
        vector<double> in(N, INF);
        vector<int> pre(N, -1);
        vector<int> id(N, -1);
        vector<int> vis(N, -1);

        // Para cada vértice, escolha aresta de entrada mínima
        for (auto &e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[root] = 0;

        // Se algum vértice (exceto a raiz) não tem aresta entrante, não existe arborecência
        for (int i = 0; i < N; i++) {
            if (in[i] == INF) return -1;
        }

        //Detectando ciclos
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            result += in[i];
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

        if (cnt == 0) break; // sem ciclos: fim

        // Remanejar vértices sem ciclos
        for (int i = 0; i < N; i++)
            if (id[i] == -1) id[i] = cnt++;

        // Ajustar pesos e contrair ciclos
        vector<Edge> newEdges;
        for (auto &e : edges) {
            int u = id[e.u];
            int v = id[e.v];
            double w = e.w;

            if (u != v) {
                w -= in[e.v];
                newEdges.push_back({u, v, w});
            }
        }

        N = cnt;
        root = id[root];
        edges = newEdges;
    }

    return result;
}

int main() {
    int H, W;
    cin >> H >> W;

    vector<vector<array<int,3>>> img(H, vector<array<int,3>>(W));

    // Entrada RGB
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            cin >> img[r][c][0] >> img[r][c][1] >> img[r][c][2];

    int N = H * W;

    auto id = [&](int r, int c) {
        return r * W + c;
    };

    vector<Edge> edges;

    // Criar grafo direcionado simples:
    // de cada pixel -> para direita e para baixo
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {

            // Direita
            if (c + 1 < W) {
                double w = rgbDist(img[r][c], img[r][c+1]);
                edges.push_back({id(r,c), id(r,c+1), w});
            }

            // Esquerda
            if (c - 1 >= 0) {
                double w = rgbDist(img[r][c], img[r][c-1]);
                edges.push_back({id(r,c), id(r,c-1), w});
            }

            // Baixo
            if (r + 1 < H) {
                double w = rgbDist(img[r][c], img[r+1][c]);
                edges.push_back({id(r,c), id(r+1,c), w});
            }

            // Cima
            if (r - 1 >= 0) {
                double w = rgbDist(img[r][c], img[r-1][c]);
                edges.push_back({id(r,c), id(r-1,c), w});
            }
        }
    }

    int root = id(0,0); // pixel (0,0)


    return 0;
}
*/