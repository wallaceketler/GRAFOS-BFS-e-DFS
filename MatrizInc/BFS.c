#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;


typedef struct TipoItem Item;
typedef struct TipoFila Fila;


struct graph{
	int V;  //define número de vértices
	int E;  //define número de arestas
	int **mat; //matriz de incidência
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


void VertexInitialize(int V, int E, Graph G)
{
	
	//Para finalizar colocamos os valores da matriz como 0, ou seja, nenhuma aresta feita

	for(int i=0; i<V; i++)
	{
		for(int j=0; j<E; j++)
		{
			G->mat[i][j]=0;
		}
	}

	//return mat;
}

Graph GraphInitialize(int V, int E)
{
	Graph G = malloc (sizeof(Graph));
	G->V=V; //Inicialmente temos que declarar quantos vértices temos
	G->E=E; //inicialmente não temos arestas conectadas
	//G->mat=VertexInitialize(V, G);

	G->mat=malloc(V*sizeof(int*));

	for(int i=0; i<V; i++)
	{
		G->mat[i]=malloc(E*sizeof(int*));
	}
	VertexInitialize(V,E,G);


	return G;
}



void GraphInsertEdge(Graph G, int V, int E)
{
	if(V<=G->V && E<=G->E)
	{
		G->mat[V][E]=1;
	}
	else
	{
		printf("Intervalo inválido");
	}
}

void ImprimeGraph(Graph G){
	
		
		for(int i=0; i<G->V; i++)
		{
			for(int j=0; j<G->E; j++)
			{
				printf("%d ", G->mat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
}


void BFS(Graph G, int s){
	int cor[G->V]; //0 Branco, 1 Cinza, 2 Preto
	int d[G->V];
	int pi[G->V]; // -1 == NULL
	int aux[G->E];
	int cont=0;
	Fila *f = FFVazia();

	for(int i=0; i<G->V; i++)
		if(i != s){
			cor[i] = 0;
			d[i]   = -1; //infinito
			pi[i]  = -1; // ? não tem pai ainda
		}


	cor[s] = 1;
	d[s]   = 0;
	pi[s]  = -1;

	Queue(f, s);

	

	
	///////////////////////////////////////////////
	
	while (f->size > 0){
		Item *u = Dequeue(f);

		cont=0;
		//Encontra os vértices adjacentes a U
		for(int i=0; i<G->E; i++)
		{
			aux[i]=G->mat[u->data][i];
			//printf(" %d ", aux[i]);
		}
		for(int i=0; i<G->V; i++)
		{
			for(int j=0; j<G->E; j++)
			{
				if(i!=s && G->mat[i][j] == 1 && aux[j]==1)
					cont++;
			}
		}
		int aux2[cont];
		cont=0;
		for(int i=0; i<G->V; i++)
		{
			for(int j=0; j<G->E; j++)
			{
				if(i!=s && G->mat[i][j] == 1 && aux[j]==1)
				{
					aux2[cont]=i;
					cont++;
				}
			}
		}
		
		for(int i=0; i<cont; i++){//Percorre a linha do vértice selecionado
			
				if(cor[aux2[i]] == 0){
					cor[aux2[i]] = 1;
					d[aux2[i]]   = d[u->data] + 1;
					pi[aux2[i]]  = u->data;
					Queue(f, aux2[i]);
				}
			
		}
		
		cor[u->data] = 2;
		printf("Vertex:%d\n", u->data);
	}
	
}



int main(int argc, char const *argv[])
{
	Graph G = GraphInitialize(10,10);

	
	GraphInsertEdge(G, 0, 2);
	GraphInsertEdge(G, 0, 1);
	GraphInsertEdge(G, 1, 0);
	GraphInsertEdge(G, 1, 9);
	GraphInsertEdge(G, 1, 8);
	GraphInsertEdge(G, 2, 0);
	GraphInsertEdge(G, 2, 3);
	GraphInsertEdge(G, 3, 2);
	GraphInsertEdge(G, 4, 9);
	GraphInsertEdge(G, 4, 5);
	GraphInsertEdge(G, 4, 6);
	GraphInsertEdge(G, 5, 1);
	GraphInsertEdge(G, 5, 4);
	GraphInsertEdge(G, 5, 6);
	GraphInsertEdge(G, 5, 7);
	GraphInsertEdge(G, 6, 4);
	GraphInsertEdge(G, 6, 5);
	GraphInsertEdge(G, 6, 7);
	GraphInsertEdge(G, 7, 3);
	GraphInsertEdge(G, 7, 8);

	ImprimeGraph(G);

	BFS(G, 0);

	return 0;
}













