#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

/*Gera uma instância do tipo Grafo*/
grafo createGraph(){
    grafo anyGrafo = NULL;

    anyGrafo = createLista();

    return anyGrafo;
}
/*Gera uma instância do tipo Point, com um id e sua cor*/
point* createPoint(int registrador, int k){
    point* anyPoint = NULL;

    anyPoint = (point*) malloc(sizeof(point));
    anyPoint->registrador = registrador;
    anyPoint->interferencias = createLista();
    anyPoint->removido = 0;

    if (registrador < k) {
        anyPoint->cor = registrador;
    }
    else anyPoint->cor = -1;

    return anyPoint;
}
/*Insere um registrador no grafo*/
point* insertPoint(grafo anyGrafo, int registrador, int k){
    point* anyPoint = NULL;

	if(findPoint(anyGrafo, registrador)==NULL){
	    anyPoint = createPoint(registrador, k);
	    addNode(anyGrafo, anyPoint);
	}
	else
		anyPoint = getThing(findPoint(anyGrafo, registrador));

    return anyPoint;
}
void createEdge(point* reg1, point* reg2){
    edge* anyEdge = NULL;

    anyEdge = (edge*) malloc(sizeof(edge));
    anyEdge->reg1 = reg1;
    anyEdge->reg2 = reg2;
    addNode(reg1->interferencias, anyEdge);
    addNode(reg2->interferencias, anyEdge);
}
int existEdge(point *reg1, point *reg2) {
    Node anyNode;
    edge *anyEdge;

    anyNode = getFirstNode(reg1->interferencias);
    while (anyNode != NULL) {
        anyEdge = getThing(anyNode);

        if (anyEdge->reg1 == reg1) {
            if (anyEdge->reg2 == reg2) {
                return 1;
            }
        }
        else if (anyEdge->reg2 == reg1) {
            if (anyEdge->reg1 == reg2) {
                return 1;
            }
        }

        anyNode = getNext(anyNode);
    }

    return 0;
}
/*Insere uma aresta entre Point 'reg1' e Point 'reg2'*/
void insertEdge(grafo anyGrafo, int reg1, int reg2, int k){
    point* anyPoint = NULL;
    point* anotherPoint = NULL;
    Node anyNode1 = NULL;
    Node anyNode2 = NULL;

    anyNode1 = findPoint(anyGrafo, reg1);
    anyNode2 = findPoint(anyGrafo, reg2);

    if(anyNode1 != NULL)
        anyPoint = getThing(anyNode1);
    if(anyNode2 != NULL)
        anotherPoint = getThing(anyNode2);
    if(anyPoint==NULL && anotherPoint==NULL){
        anyPoint = insertPoint(anyGrafo, reg1, k);
        anotherPoint = insertPoint(anyGrafo, reg2, k);
    }
    else if(anyPoint==NULL){
        anyPoint = insertPoint(anyGrafo, reg1, k);
    }
    else if(anotherPoint==NULL){
        anotherPoint = insertPoint(anyGrafo, reg2, k);
    }
    if (!existEdge(anyPoint, anotherPoint)) {
        createEdge(anyPoint, anotherPoint);
    }
}
/*Remove a aresta entre Point 'reg1' e Point 'reg2'*/
void removeEdge(grafo anyGrafo, int reg1, int reg2){
    point* anyPoint = NULL;
    point* anotherPoint = NULL;
    //edge* anyEdge = NULL;
    Node anyNode = NULL;
    Node anotherNode = NULL;

    if(findPoint(anyGrafo, reg1)!=NULL)
        anyPoint = getThing(findPoint(anyGrafo, reg1));
    if(findPoint(anyGrafo, reg2)!=NULL)
        anotherPoint = getThing(findPoint(anyGrafo, reg2));
    if(anyPoint==NULL || anotherPoint==NULL){
        printf("-AUSÊNCIA DE UM DOS REGISTRADORES-\n");
    }
    else{
        anyNode = findEdge(anyGrafo, reg1, reg2);
        anotherNode = findEdge(anyGrafo, reg2, reg1);
        if(anyNode!=NULL && anotherNode!=NULL){
            printf("-PRESENÇA DOS REGISTRADORES- '%p'\n", anyNode);
            //anyEdge = getThing(anyNode);
            printf("LISTA1 SIZE: %d\n", lenghtLista(anyPoint->interferencias));
            removeNode(anyPoint->interferencias, anyNode, 0);
            printf("LISTA1 SIZE: %d\n", lenghtLista(anyPoint->interferencias));
            printf("LISTA2 SIZE: %d\n", lenghtLista(anotherPoint->interferencias));
            removeNode(anotherPoint->interferencias, anotherNode, 1);
            printf("LISTA2 SIZE: %d\n", lenghtLista(anotherPoint->interferencias));
        }
        else{
            printf("-ARESTA INEXISTENTE- (%d<-->%d)\n", reg1, reg2);
        }
    }
}
/*Remove o registrador*/
void removePoint(grafo anyGrafo, int registrador){
    int i;
    Node anyNode = NULL;
    Node anyNode2 = NULL;
    Node anotherNode = NULL;
    Node anotherNode2 = NULL;
    point* anyPoint = NULL;
    point* anotherPoint = NULL;
    edge* anyEdge = NULL;

    anotherNode = findPoint(anyGrafo, registrador);
    if(anotherNode!=NULL){
        anyPoint = getThing(anotherNode);

        anyNode = getFirstNode(anyPoint->interferencias);
        for(i=1;i<=lenghtLista(anyPoint->interferencias)+2;i++){
            if(anyNode==NULL){
                printf("QUEBRANDO AQUI %d\n", i);
                break;
            }
            anyEdge = getThing(anyNode);
            if(anyEdge->reg1==anyPoint)
                anotherPoint = anyEdge->reg2;
            else if(anyEdge->reg2==anyPoint)
                anotherPoint = anyEdge->reg1;
            anotherNode2 = findEdge(anyGrafo, anotherPoint->registrador, anyPoint->registrador);
            anyNode2 = getNext(anyNode);
            removeNode(anyPoint->interferencias, anyNode, 0);
            removeNode(anotherPoint->interferencias, anotherNode2, 1);
            anyNode = anyNode2;
        }
        free(anyPoint);
    }
    else{
        printf("-AUSÊNCIA DO REGISTRADOR-\n");
    }
}
/*Printa todas as interferências de um dado registrador*/
void printPoint(grafo anyGrafo, int registrador){
    int i;
    Node anyNode = NULL;
    Node anotherNode = NULL;
    point* anyPoint = NULL;
    point* anotherPoint = NULL;
    edge* anyEdge = NULL;

    anotherNode = findPoint(anyGrafo, registrador);
    if(anotherNode!=NULL){
        anyPoint = getThing(anotherNode);
        printf("%d --> ", anyPoint->registrador);
        anyNode = getFirstNode(anyPoint->interferencias);
        for(i=1;i<=lenghtLista(anyPoint->interferencias);i++){
            if(anyNode==NULL)
                break;
            anyEdge = getThing(anyNode);
            if(anyEdge->reg1==anyPoint)
                anotherPoint = anyEdge->reg2;
            else if(anyEdge->reg2==anyPoint)
                anotherPoint = anyEdge->reg1;
            printf("%d ", anotherPoint->registrador);
            anyNode = getNext(anyNode);
        }
        printf("\n");
    }
    else{
        printf("-AUSÊNCIA DO REGISTRADOR-\n");
    }
}
void printGraph(grafo anyGrafo){
    int i;
    Node anyNode = NULL;
    point* anyPoint = NULL;

    anyNode = getFirstNode(anyGrafo);
    for (i=0; i<lenghtLista(anyGrafo); i++) {
        anyPoint = getThing(anyNode);
        printPoint(anyGrafo, anyPoint->registrador);

        anyNode = getNext(anyNode);
    }
}
/*Encontra o registrador no grafo (retorna 1 para*/
Node findPoint(grafo anyGrafo, int registrador){
    int i, sizeList;
    point* anyPoint = NULL;
    Node anyNode = NULL;

    sizeList = lenghtLista(anyGrafo);
    anyNode = getFirstNode(anyGrafo);
    for(i=1;i<=sizeList;i++){
        if(anyNode==NULL)
            break;
        anyPoint = getThing(anyNode);
        if(anyPoint->registrador == registrador)
            break;
        anyNode = getNext(anyNode);
    }
    if(i <= sizeList)
        return anyNode;
    else
        return NULL;
}
/*Encontra a aresta entre Point 'reg1' e Point 'reg2', retorna nulo se não existir ligação*/
Node findEdge(grafo anyGrafo, int reg1, int reg2){
    int i;
    point* anyPoint = NULL;
    point* anotherPoint = NULL;
    edge* anyEdge = NULL;
    Node anyNode = NULL;

    if(findPoint(anyGrafo, reg1)!=NULL)
        anyPoint = getThing(findPoint(anyGrafo, reg1));
    if(findPoint(anyGrafo, reg2)!=NULL)
        anotherPoint = getThing(findPoint(anyGrafo, reg2));
    if(anyPoint==NULL && anotherPoint==NULL){
        printf("-AUSÊNCIA DE UM DOS PONTOS-\n");
    }
    else if(anyPoint==NULL){
        printf("-AUSÊNCIA DE UM DOS PONTOS-\n");
    }
    else if(anotherPoint==NULL){
        printf("-AUSÊNCIA DE UM DOS PONTOS-\n");
    }
    else{
        anyPoint = getThing(findPoint(anyGrafo, reg1));
        anyNode = getFirstNode(anyPoint->interferencias);
        for(i=1;i<=lenghtLista(anyPoint->interferencias);i++){
            if(anyNode==NULL)
                break;
            anyEdge = getThing(anyNode);
            if(anyEdge->reg1==anotherPoint || anyEdge->reg2==anotherPoint)
                break;
            anyNode = getNext(anyNode);
        }
    }
    if(i<=lenghtLista(anyPoint->interferencias))
        return anyNode;
    else
        return NULL;
}
/*Libera a memória do grafo*/
void encerraGrafo(grafo anyGrafo){

}
/*Libera a memória da lista de interferências*/
void destroiEdges(int registrador){

}
/* ---------------------------------------------------- */
/* Remove um vértice do grafo; */
void removeVertex(grafo anyGrafo, int registrador){
    point* anyPoint = NULL;

    anyPoint = getThing(findPoint(anyGrafo, registrador));
    anyPoint->removido = 1;
}
/* Empilha o grafo na pilha(stack); */
Lista pileGraph(grafo anyGrafo, Lista stack){

}
/* Desempilha a pilha reformando o grafo; */
void unpileStack(grafo anyGrafo, Lista stack){

}
/* Encontra o vértice com um grau menor do que K */
point* findLessK(grafo anyGrafo, int k){
    int i, sizeList;
    point* anyPoint = NULL;
    Node anyNode = NULL;

    // printf("\n\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\n");

    sizeList = lenghtLista(anyGrafo);
    anyNode = getLastNode(anyGrafo);
    for(i=0;i<sizeList;i++){
        anyPoint = getThing(anyNode);
        // printf(">>>>>>>>>>>>>>> %d ----- %d\n\n", anyPoint->registrador, i);
        if (anyPoint->removido == 0)
            if(countDegree(anyGrafo, anyPoint->registrador)<k)
                break;   
        anyNode = getPrevious(anyNode);
    }
    if(i<sizeList)
        return anyPoint;
    else
        return NULL;
}
/* Encontra algum potencial spill no grafo; */
point* findPotencialSpill(grafo anyGrafo){
    int i, count, sizeList, biggerDegree = -1;
    point* anyPoint = NULL;
    point* resp = NULL;
    Node anyNode = NULL;

    sizeList = lenghtLista(anyGrafo);
    anyNode = getFirstNode(anyGrafo);
    for(i=0;i<sizeList;i++){
        anyPoint = getThing(anyNode);
        if (anyPoint->removido == 0) {
            count = countDegree(anyGrafo, anyPoint->registrador);

            if(count > biggerDegree){
                biggerDegree = count;
                resp = anyPoint;
            }
            else if(count == biggerDegree && resp != NULL){
                if(anyPoint->registrador < resp->registrador){
                    resp = anyPoint;
                }
            }            
        }
        anyNode = getNext(anyNode);
    }

    return resp;
}
/* Conta o número de vértices ativos no grafo; */
int countVertexes(grafo anyGrafo){
    int i, sizeList, resp=0;
    point* anyPoint = NULL;
    Node anyNode = NULL;

    sizeList = lenghtLista(anyGrafo);
    anyNode = getFirstNode(anyGrafo);
    for(i=0;i<sizeList;i++){
        anyPoint = getThing(anyNode);
        // printf("Registrador -----> %d", anyPoint->registrador);
        if(anyPoint->removido == 0)
            resp++;
        anyNode = getNext(anyNode);
    }

    return resp;
}
/* Conta o grau do registrador; */
int countDegree(grafo anyGrafo, int registrador){
    int i, sizeList, resp=0;
    point* anyPoint = NULL;
    point* otherPoint = NULL;
    edge* anyEdge = NULL;
    Node anyNode = NULL;

    anyPoint = getThing(findPoint(anyGrafo, registrador));
    sizeList = lenghtLista(anyPoint->interferencias);
    anyNode = getFirstNode(anyPoint->interferencias);
    for(i=0;i<sizeList;i++){
        anyEdge = getThing(anyNode);
        if(anyEdge->reg1 == anyPoint)
            otherPoint = anyEdge->reg2;
        else otherPoint = anyEdge->reg1;
        if(otherPoint->removido == 0)
            resp++;
        anyNode = getNext(anyNode);
    }

    return resp;
}
/* Atribui uma cor ao registrador; retorna 1 para sucesso e 0 para erro ao atribuir; */
int assignColor(point* anyPoint, int k){
    int* neighbourColor = (int*) malloc(k*sizeof(int));
    int i, j=0, aux;
    point* anotherPoint = NULL;
    edge* anyEdge = NULL;
    Node anyNode = NULL;

    for(i=0;i<k;i++)
        neighbourColor[i] = 0;
    anyNode = getFirstNode(anyPoint->interferencias);
    for(i=0;i<lenghtLista(anyPoint->interferencias);i++){
        anyEdge = getThing(anyNode);
        if(anyEdge->reg1==anyPoint)
            anotherPoint = anyEdge->reg2;
        else if(anyEdge->reg2==anyPoint)
            anotherPoint = anyEdge->reg1;        
        if(anotherPoint->removido == 0){
        		j++;
                if(anotherPoint->cor>=0){
			        neighbourColor[anotherPoint->cor] = 1;
			    }
		}
        anyNode = getNext(anyNode);
    }
  //  printf("PRINTANDO VETOR DE CORES:\n");
    //for(i=0;i<k;i++)
		//printf("COR: %d ESTADO: %d\n", i, neighbourColor[i]);
//     if(j == 0){
//         anyPoint->cor = 0;
//         anyPoint->removido = 0;
// //        printf("HÃM ? --- ASSIMILANDO COR %d AO REG %d\n", anyPoint->cor, anyPoint->registrador);
//         return 1;
//     }
    // else{
        for(i=0;i<k;i++){
            if(neighbourColor[i] == 0){
                anyPoint->cor = i;
                anyPoint->removido = 0;
         //       printf("ASSIMILANDO COR %d AO REG %d\n", anyPoint->cor, anyPoint->registrador);
                return 1;
            }
        }        
       // printf("ERRO AO ASSIMILAR COR AO REG\n");
        return 0;
    // }
}