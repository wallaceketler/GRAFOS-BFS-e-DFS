#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;


typedef struct TipoItem Item;
typedef struct TipoFila Fila;


struct graph{
	int V;  //define número de vértices
	int E;  //define número de arestas
	int **mat; //matriz de adjacência
};

//fila
struct TipoItem{
    int data;
	Item *prox;
};

struct TipoFila{
	Item *head;
	Item *tail;
	int size;
};

//// procs FILA

Fila* FFVazia(){
	Fila *f = (Fila*) malloc(sizeof(Fila));
	f->head = NULL;
	f->tail = NULL;
	return f;
}

void Queue(Fila *f, int vertex){
	Item *d = (Item *) malloc (sizeof(Item));
	d->data = vertex;
	d->prox = NULL;

	if(f->head == NULL){
		f->head = d;
		f->tail = d;
	}else{
		f->tail->prox = d;
		f->tail = d;
	}

	f->size ++;
}

Item* Dequeue(Fila *f){
	Item *aux;

	if(f->head == NULL)
		return NULL;

	aux = f->head;
	f->head = f->head->prox;
	f->size --;

	return aux;
}

//// fim procs FILA

void VertexInitialize(int V, Graph G)
{
	
	//Para finalizar colocamos os valores da matriz como 0, ou seja, nenhuma aresta feita

	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			G->mat[i][j]=0;
		}
	}

	//return mat;
}

Graph GraphInitialize(int V)
{
	Graph G = malloc (sizeof(Graph));
	G->V=V; //Inicialmente temos que declarar quantos vértices temos
	G->E=0; //inicialmente não temos arestas conectadas
	//G->mat=VertexInitialize(V, G);

	G->mat=malloc(V*sizeof(int*));

	for(int i=0; i<V; i++)
	{
		G->mat[i]=malloc(V*sizeof(int*));
	}
	VertexInitialize(V,G);


	return G;

}

void GraphInsertEdge(Graph G, int v1, int v2)
{
	if(v1<=G->V && v2<=G->V)
	{
		G->mat[v1][v2]=1;
		G->E ++;
	}
	else
	{
		printf("Intervalo inválido");
	}
}

void ImprimeGraph(Graph G){
	
		
		for(int i=0; i<G->V; i++)
		{
			for(int j=0; j<G->V; j++)
			{
				printf("%d ", G->mat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
}


void DFS_VISIT(Graph G, int v, int *cor, int *d, int *f, int *tempo){
	cor[v]  = 1;
	*tempo        += 1;
	d[v]    = *tempo;

	for(int i=0; i<G->V; i++)
	{
		if(G->mat[v][i]!=0)
		{
			if(cor[i] == 0)
				DFS_VISIT(G, i, cor, d, f, tempo);
		}
	}


	cor[v] = 2;
	*tempo += 1;
	f[v] = *tempo;
	printf("Vertex:%d D:%d, F:%d \n", v, d[v], f[v]);
}

void DFS(Graph G){
	int cor[G->V]; // Branco 0, Cinza 1, Preto 2
	int d[G->V];   // Tempo de descoberta
	int f[G->V];   // Tempo de finalização
	int tempo = 0;

	for(int v=0; v<G->V; v++)
		cor[v] = 0;

	for(int v=0; v<G->V; v++)
		if(cor[v] == 0)
			DFS_VISIT(G, v, cor, d, f, &tempo);
}




int main(int argc, char const *argv[])
{
	Graph G = GraphInitialize(10);

	//Modelo de Grafo do slide 13 / aula 10
	//S=0, W=1, R=2, V=3, T=4, X=5, U=6, Y=7
	GraphInsertEdge(G, 0, 2);
	GraphInsertEdge(G, 0, 1);
	GraphInsertEdge(G, 1, 0);
	GraphInsertEdge(G, 1, 4);
	GraphInsertEdge(G, 1, 5);
	GraphInsertEdge(G, 2, 0);
	GraphInsertEdge(G, 2, 3);
	GraphInsertEdge(G, 3, 2);
	GraphInsertEdge(G, 4, 1);
	GraphInsertEdge(G, 4, 5);
	GraphInsertEdge(G, 4, 6);
	GraphInsertEdge(G, 5, 1);
	GraphInsertEdge(G, 5, 4);
	GraphInsertEdge(G, 5, 6);
	GraphInsertEdge(G, 5, 7);
	GraphInsertEdge(G, 6, 4);
	GraphInsertEdge(G, 6, 5);
	GraphInsertEdge(G, 6, 7);
	GraphInsertEdge(G, 7, 6);
	GraphInsertEdge(G, 7, 5);


	ImprimeGraph(G);

	DFS(G);

	return 0;
}













