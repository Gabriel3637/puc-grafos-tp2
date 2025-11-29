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

double intensity(const array<int,3>& a) {
    return (a[0] + a[1] + a[2]) / 3.0;
}

// Distância Euclidiana RGB
double rgbDist(const array<int,3>& a, const array<int,3>& b) {
    double dr = a[0] - b[0];
    double dg = a[1] - b[1];
    double db = a[2] - b[2];
    return sqrt(dr*dr + dg*dg + db*db); 
}

/*
    Edmonds–Tarjan DMST (Chu-Liu)
    Retorna uma lista de arestas da DMST
*/
/*
vector<Edge> dmst(int root, vector<Edge> edges, int N) {

    vector<Edge> chosen_edges;

    while (true) {
        vector<double> in(N, INF);
        vector<int> pre(N, -1);
        vector<int> id(N, -1);
        vector<int> vis(N, -1);

        // melhor aresta entrante
        for (auto &e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[root] = 0;

        // nó sem aresta entrante = falha
        for (int i = 0; i < N; i++)
            if (in[i] == INF)
                return {};

        int cnt = 0;
        double total = 0;

        // detecção de ciclos
        for (int i = 0; i < N; i++) {
            total += in[i];
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

        if (cnt == 0) {
            // fim, reconstruir DMST
            for (int i = 0; i < N; i++) {
                if (i == root) continue;
                chosen_edges.push_back({pre[i], i, in[i]});
            }
            return chosen_edges;
        }

        for (int i = 0; i < N; i++)
            if (id[i] == -1)
                id[i] = cnt++;

        vector<Edge> newEdges;
        vector<double> cycleIn(N);

        for (int i = 0; i < N; i++)
            cycleIn[i] = in[i];

        for (auto &e : edges) {
            int u = id[e.u];
            int v = id[e.v];
            double w = e.w;

            if (u != v)
                newEdges.push_back({u, v, w - cycleIn[e.v]});
        }

        edges = newEdges;
        N = cnt;
        root = id[root];
    }
}

int main() {
    int H, W;
    cin >> H >> W;

    vector<vector<array<int,3>>> img(H, vector<array<int,3>>(W));

    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            cin >> img[r][c][0] >> img[r][c][1] >> img[r][c][2];

    int N = H * W;

    auto id = [&](int r, int c) {
        return r * W + c;
    };

    vector<Edge> edges;

    // Criar arestas direcionadas pelo critério de intensidade
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {

            array<int,3> &px = img[r][c];
            int u = id(r,c);
            double Iu = intensity(px);

            auto try_add = [&](int nr, int nc) {
                array<int,3>& py = img[nr][nc];
                int v = id(nr,nc);
                double Iv = intensity(py);
                double w = rgbDist(px, py);

                // direcione sempre do mais escuro → mais claro
                if (Iu <= Iv)
                    edges.push_back({u, v, w});
                else
                    edges.push_back({v, u, w});
            };

            if (c+1 < W) try_add(r, c+1);
            if (r+1 < H) try_add(r+1, c);
            if (c-1 >= 0) try_add(r, c-1);
            if (r-1 >= 0) try_add(r-1, c);
        }
    }

    int root = 0;

    vector<Edge> tree = dmst(root, edges, N);

    if (tree.empty()) {
        cout << "Nao existe DMST\n";
        return 0;
    }

    // SEGMENTAÇÃO
    // cortar arestas mais pesadas
    vector<double> weights;
    for (auto &e : tree) weights.push_back(e.w);

    sort(weights.begin(), weights.end());

    // threshold simples: percentil 80%
    double thr = weights[weights.size() * 0.80];

    vector<int> parent(N);
    for (int i = 0; i < N; i++) parent[i] = i;

    function<int(int)> findp = [&](int x) {
        return (parent[x] == x ? x : parent[x] = findp(parent[x]));
    };

    auto unite = [&](int a, int b) {
        a = findp(a);
        b = findp(b);
        if (a != b) parent[b] = a;
    };

    for (auto &e : tree) {
        if (e.w <= thr)
            unite(e.u, e.v);
    }

    // produzir rotulos
    vector<int> label(N);
    for (int i = 0; i < N; i++)
        label[i] = findp(i);

    cout << "Segmentacao (label por pixel):\n";
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            cout << label[id(r,c)] << " ";
        }
        cout << "\n";
    }

    return 0;
}
*/