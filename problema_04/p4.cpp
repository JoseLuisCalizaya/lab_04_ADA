#include <iostream>
#define vertex int

typedef struct node *link;
struct node {
  vertex w;
  link next;
};

struct graph {
  int V;
  int A;
  link *adj;
};
typedef struct graph *Graph;

static link NEWnode(vertex w, link next) {
  link a = (link)malloc(sizeof(struct node));
  a->w = w;
  a->next = next;
  return a;
}

Graph GRAPHinit(int V) {
  Graph G = (Graph)malloc(sizeof *G);
  G->V = V;
  G->A = 0;
  G->adj = (link *)malloc(V * sizeof(link));
  for (vertex v = 0; v < V; ++v)
    G->adj[v] = NULL;
  return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
  for (link a = G->adj[v]; a != NULL; a = a->next)
    if (a->w == w)
      return;
  G->adj[v] = NEWnode(w, G->adj[v]);
  G->A++;
}

bool GRAPHisolated(Graph G, vertex v) {
  if (G->adj[v] != NULL)
    return false;
  for (vertex u = 0; u < G->V; ++u) {
    for (link a = G->adj[u]; a != NULL; a = a->next) {
      if (a->w == v)
        return false;
    }
  }
  return true;
}

int GRAPHoutdeg(Graph G, vertex v) {
  int count = 0;
  for (link a = G->adj[v]; a != NULL; a = a->next)
    count++;
  return count;
}

int GRAPHindeg(Graph G, vertex v) {
  int count = 0;
  for (vertex u = 0; u < G->V; ++u) {
    for (link a = G->adj[u]; a != NULL; a = a->next) {
      if (a->w == v)
        count++;
    }
  }
  return count;
}

void GRAPHshow(Graph G) {
    std::cout << "Grafo (V=" << G->V << ", A=" << G->A << ")" << std::endl;
    for (vertex v = 0; v < G->V; ++v) {
        std::cout << v << ":";
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            std::cout << " " << a->w;
        }
        std::cout << std::endl;
    }
}

int main() {
  // Crear un grafo con 6 vértices (0 a 5)
  Graph G = GRAPHinit(6);

  std::cout << "--- Creando grafo de ejemplo ---" << std::endl;

  GRAPHinsertArc(G, 0, 1);
  GRAPHinsertArc(G, 0, 5);
  GRAPHinsertArc(G, 1, 0);
  GRAPHinsertArc(G, 1, 5);
  GRAPHinsertArc(G, 2, 4);
  GRAPHinsertArc(G, 3, 1);
  GRAPHinsertArc(G, 5, 3);
  /*
    ---  Grafo Inicial ---a0: 5 1
  1: 5 0
  2: 4
  3: 1
  4:
  5: 3
  */
  std::cout << "\nGrados del vertice 1" << std::endl;
  std::cout << "Grado de salida de 1: " << GRAPHoutdeg(G, 1) << std::endl;
  std::cout << "Grado de entrada de 1: " << GRAPHindeg(G, 1) << std::endl;
  std::cout << "\nGrados del vertice 3" << std::endl;
  std::cout << "Grado de salida de 3: " << GRAPHoutdeg(G, 3) << std::endl;
  std::cout << "Grado de entrada de 3: " << GRAPHindeg(G, 3) << std::endl;

  //Problema 4
  std::cout << "\n--- (E4) Grafo Inicial ---" << std::endl;
  GRAPHshow(G);
}
