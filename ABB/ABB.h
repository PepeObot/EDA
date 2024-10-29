#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Prestador.h"
#define MAX 111


typedef struct nodo{
   Prestador arb;
   struct nodo *hi;
   struct nodo *hd;
}nodo;

typedef struct {
    nodo *raiz;
    int Nodos;
}ABB;

void init_ABB(ABB *a){
    (*a).raiz=NULL;
    (*a).Nodos=0;
}

void borrar_arbol(nodo **x){
    if (*x!=NULL){
        borrar_arbol(&(*x)->hi);
        borrar_arbol(&(*x)->hd);
        (*x) = NULL;
        free(*x);
    }
}

int LocalizarABB(ABB *a,long id,nodo **x, nodo **y,int *exito, float *costo){
    *x=(*a).raiz;
    *y=*x;
    *costo = 0;
    while((*x!=NULL)&&(**x).arb.dni!=id){
        (*costo)=(*costo)+1.0;
        *y=*x;
        if ((**x).arb.dni < id){
            *x = (**x).hd;
        }else{
            *x = (**x).hi;
            }
    }
    *costo=*costo+1.0;
    if (*x != NULL){
        *exito=1;
    }else *exito = 0;
    return *exito;
}

int AltaABB(ABB *a, Prestador l, int *exito, float *costo) {
    nodo *x, *y;
    *costo = 0;
    float c = 0;
    if (LocalizarABB(a, l.dni, &x, &y, exito, &c) == 1){
        return *exito = 0;
    } else {
        x = (nodo*)malloc(sizeof(nodo));
        if (x == NULL) {
            free((void*)x);
            return *exito = -1;
        }
        (*x).arb = l;
        (*x).hd = NULL;
        (*x).hi = NULL;
        if ((*a).Nodos == 0) {
            (*a).raiz = x;
        } else {
            if ((*y).arb.dni < l.dni) {
                (*y).hd = x;
            } else {
                (*y).hi = x;
            }
        }
        (*a).Nodos++;
        *costo = 0.5;
        return *exito = 1;
    }
}


 int baja_ABB(ABB *a, Prestador aux, int *exito, float *costo) {
    nodo *x, *y,*u,*u1;
    *costo = 0;
    float c = 0;
    if (LocalizarABB(a, aux.dni, &x, &y, exito, &c)) {
    if(0==strcmpi((*x).arb.nomyape,aux.nomyape)&&
       0==strcmpi((*x).arb.domicilio,aux.domicilio)&&
       0==strcmpi((*x).arb.servicios,aux.servicios)&&
       0==strcmpi((*x).arb.telefono,aux.telefono)&&
       0==strcmpi((*x).arb.correo,aux.correo)){
    (*a).Nodos--;
    if (x->hi == NULL && x->hd == NULL) {
        if (x == a->raiz) {
            a->raiz = NULL;
        } else {
            if (y->hd == x) {
                y->hd = NULL;
            } else {
                y->hi = NULL;
            }
        }
        *costo = 0.5;
    } else if (x->hi == NULL && x->hd != NULL) {
        if (x == a->raiz) {
            if ((*x).hd != NULL){
                    (*a).raiz = (*x).hd;
                }else{
                    (*a).raiz = (*x).hi;
                }
        } else {
            if (y->hd == x) {
                y->hd = x->hd;
            } else {
                y->hi = x->hd;
            }
        }
        *costo = 0.5;
    } else if (x->hd == NULL && x->hi != NULL) {
        if (x == a->raiz) {
            if ((*x).hi != NULL){
                    (*a).raiz = (*x).hi;
                }else{
                    (*a).raiz = (*x).hd;
                }
        } else {
                if ((*y).hd == x){
                    (*y).hd = (*x).hi;
                }
                else (*y).hi = (*x).hi;
        }
        *costo = 0.5;
    } else {
        u = x->hd;
        u1 = x->hd;
        while (u->hi != NULL) {
            u1 = u;
            u = u->hi;
        }
        if (u == u1) {
            x->hd = u->hd;
            x->arb = u->arb;
        } else {
            x->arb = u->arb;
            u1->hi = u->hd;
        }
        *costo = 1.5;
        x = u;
    }
        free(x);
        return *exito = 1;
    }
    }else{
        *exito = 0;
    }
}

Prestador evocar_prestador_ABB(ABB *a, long id, int *exito,float *costo){
    nodo *x, *y; Prestador aux;
    float c = 0;LocalizarABB(a,id,&x,&y,exito,&c);
    if (*exito == 1){
        if(x!=NULL){
        aux = (*x).arb;}
        *costo = c;
        *exito =1;
        return aux;
    }else{
        *exito=0;
        *costo = c;
    }
}

int muestra_abb(nodo *x){
    setlocale(LC_ALL,"");
    int i =0, top =0;
    nodo *aux, **l;
    l = (nodo**)malloc(sizeof(nodo*));
    aux = x;
    while (aux != NULL || top > 0){
        while(aux != NULL){
            printf("Prestador: %d\n",i);
            printf("Número de documento: %ld \n", (*aux).arb.dni);
            printf("Nombre y Apellido: %s \n", (*aux).arb.nomyape);
            printf("Domicilio : %s \n", (*aux).arb.domicilio);
            printf("Correo electrónico: %s \n", (*aux).arb.correo);
            printf("Servicio: %s \n", (*aux).arb.servicios);
            printf("Número de teléfono: %s \n", (*aux).arb.telefono);
            if((*aux).hd != NULL){
                printf("\nDNI Del hijo derecho: %d\n",(*aux).hd->arb.dni);
            }
            if((*aux).hi != NULL){
                printf("\nDNI Del hijo izquierdo: %d\n",(*aux).hi->arb.dni);
            }
            if((*aux).hi == NULL && (*aux).hd == NULL){
                printf("Sin hijos.\n");
            }
            printf("******************************************\n");
            i++;
            if(i%5 == 0){
                fflush(stdin);
                printf("Presione ENTER para la p�gina siguiente...\n");
                getchar();
            }
            l[top++] = aux;
            aux = aux->hi;
        }
        aux = l[--top];
        aux = aux->hd;
    }
    free(l);
}


#endif // ABB_H_INCLUDED
