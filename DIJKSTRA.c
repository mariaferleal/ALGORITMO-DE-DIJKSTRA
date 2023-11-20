#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura TipoGrafo
typedef struct {
  int NumVertices;
  int **Mat; // Matriz de adjacência para representar o grafo
} TipoGrafo;

void caminho_mais_curto(TipoGrafo *grafo, int origem, int destino) {
  int i, vert, k, NovaDist, min;
  int *M, *L, *A, *caminho;

  M = (int *)malloc(grafo->NumVertices * sizeof(int));
  L = (int *)malloc(grafo->NumVertices * sizeof(int));
  A = (int *)malloc(grafo->NumVertices * sizeof(int));
  caminho = (int *)malloc(grafo->NumVertices * 3 * sizeof(int));

  for (i = 0; i < grafo->NumVertices; i++) {
    M[i] = 0;      // false
    A[i] = -1;     // Determina caminho mais curto
    L[i] = 300000; // infinito determina o caminho mais curto
  }

  vert = origem;
  L[vert] = 0;

  while (vert != destino && vert != -1) {
    for (i = 0; i < grafo->NumVertices; i++) {
      if (grafo->Mat[vert][i] != 0 && M[i] == 0) {
        NovaDist = L[vert] + grafo->Mat[vert][i];
        if (NovaDist < L[i]) {
          L[i] = NovaDist;
          A[i] = vert;
        }
      }
    }
    M[vert] = 1;
    min = 300000;
    vert = -1;
    for (i = 0; i < grafo->NumVertices; i++) {
      if (M[i] == 0 && L[i] < min) {
        min = L[i];
        vert = i;
      }
    }
  }
  // fim do while

  if (vert == destino) {
    printf("caminho mais curto entre %4d e %4d tem comprimento %4d: ", origem,
           destino, L[destino]);
    caminho[0] = destino;
    k = 1;
    while (vert != origem) {
      caminho[k] = A[vert];
      vert = A[vert];
      k++;
    }
    for (i = k - 1; i >= 0; i--) {
      printf("%4d", caminho[i]);
    }

  } else
    printf("nao existe caminho entre %4d e %4d", origem, destino);
}

int main(void) {
  // Definição do grafo com 5 vértices
  TipoGrafo grafo;
  grafo.NumVertices = 6;

  // Definição e preenchimento da matriz de adjacência (exemplo)
  int matriz[6][6] = {{0, 1, 4, 0, 0, 0}, {1, 0, 4, 2, 7, 0},
                      {4, 4, 0, 3, 5, 0}, {0, 2, 3, 0, 4, 6},
                      {0, 7, 5, 4, 0, 7}, {0, 0, 0, 6, 7, 0}};

  // Alocando memória para a matriz de adjacência no struct do grafo
  grafo.Mat = (int **)malloc(grafo.NumVertices * sizeof(int *));
  for (int i = 0; i < grafo.NumVertices; i++) {
    grafo.Mat[i] = (int *)malloc(grafo.NumVertices * sizeof(int));
    for (int j = 0; j < grafo.NumVertices; j++) {
      grafo.Mat[i][j] = matriz[i][j];
    }
  }

  // Chamando a função para encontrar o caminho mais curto
  int origem = 0;  // Vértice de origem
  int destino = 5; // Vértice de destino
  caminho_mais_curto(&grafo, origem, destino);

  // Liberando a memória alocada para a matriz de adjacência
  for (int i = 0; i < grafo.NumVertices; i++) {
    free(grafo.Mat[i]);
  }
  free(grafo.Mat);

  return 0;
}
