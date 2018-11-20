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
point* createPoint(int registrador, int cor){
    point* anyPoint = NULL;

    anyPoint = (point*) malloc(sizeof(point));
    anyPoint->registrador = registrador;
    anyPoint->interferencias = createLista();
    anyPoint->removido = 0;
    anyPoint->cor = cor;

    return anyPoint;
}
/*Insere um registrador no grafo*/
point* insertPoint(grafo anyGrafo, int registrador, int cor){
    point* anyPoint = NULL;

    anyPoint = createPoint(registrador, cor);
    addNode(anyGrafo, anyPoint);

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
/*Insere uma aresta entre Point 'reg1' e Point 'reg2'*/
void insertEdge(grafo anyGrafo, int reg1, int cor1, int reg2, int cor2){
    point* anyPoint = NULL;
    point* anotherPoint = NULL;

    if(findPoint(anyGrafo, reg1)!=NULL)
        anyPoint = getThing(findPoint(anyGrafo, reg1));
    if(findPoint(anyGrafo, reg2)!=NULL)
        anotherPoint = getThing(findPoint(anyGrafo, reg2));
    if(anyPoint==NULL && anotherPoint==NULL){
        anyPoint = insertPoint(anyGrafo, reg1, cor1);
        anotherPoint = insertPoint(anyGrafo, reg2, cor2);
    }
    else if(anyPoint==NULL){
        anyPoint = insertPoint(anyGrafo, reg1, cor1);
    }
    else if(anotherPoint==NULL){
        anotherPoint = insertPoint(anyGrafo, reg2, cor2);
    }
    createEdge(anyPoint, anotherPoint);
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
/*Encontra o registrador no grafo (retorna 1 para*/
Node findPoint(grafo anyGrafo, int registrador){
    int i;
    point* anyPoint = NULL;
    Node anyNode = NULL;

    anyNode = getFirstNode(anyGrafo);
    for(i=1;i<=lenghtLista(anyGrafo);i++){
        if(anyNode==NULL)
            break;
        anyPoint = getThing(anyNode);
        if(anyPoint->registrador == registrador)
            break;
        anyNode = getNext(anyNode);
    }
    if(i<=lenghtLista(anyGrafo))
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
