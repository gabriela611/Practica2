#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// Estructura para representar una arista ponderada en el grafo
struct Edge {
    int src, dest, weight;
};

// Estructura para representar un grafo dirigido y ponderado
struct Graph {
    int V, E;           // V = número de vértices, E = número de aristas
    struct Edge* edge;  // Grafo representado como un array de aristas
};

// Crea un grafo con V vértices y E aristas
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// Función para imprimir el resultado
void printArr(const vector<int>& dist) {
    cout << "Vertex   Distance from Source\n";
    for (size_t i = 0; i < dist.size(); ++i)
        cout << i << "\t\t" << dist[i] << "\n";
}

// Función principal que encuentra las distancias más cortas desde src
// a todos los demás vértices usando el algoritmo de Bellman-Ford.
// También detecta ciclos negativos.
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    vector<int> dist(V, INT_MAX); // Usar un vector en lugar de un arreglo estático

    // Paso 1: Inicializar distancias de src a todos los demás vértices como INFINITO
    dist[src] = 0;

    // Paso 2: Relajar todas las aristas |V| - 1 veces.
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Paso 3: Comprobar ciclos de peso negativo
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle";
            return;
        }
    }

    printArr(dist);
}

// Código del conductor
int main() {
    int V = 5; // Número de vértices en el grafo
    int E = 8; // Número de aristas en el grafo
    struct Graph* graph = createGraph(V, E);

    // Añadir aristas
    graph->edge[0] = {0, 1, -1};
    graph->edge[1] = {0, 2, 4};
    graph->edge[2] = {1, 2, 3};
    graph->edge[3] = {1, 3, 2};
    graph->edge[4] = {1, 4, 2};
    graph->edge[5] = {3, 2, 5};
    graph->edge[6] = {3, 1, 1};
    graph->edge[7] = {4, 3, -3};

    // Llamada a la función
    BellmanFord(graph, 0);

    return 0;
}
