#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Prestador.h"

// PARA LOS REBALSES LINEALES Y CUADRÁTICOS SUS RESPECTTIVOS MÁXIMOS SON: RAL MAX = 131, RAC = 127.
// ÉSTOS SERÍAN SUS RESPECTIVOS NÚMEROS PRIMOS MÁS CERCANOS.

typedef struct balde{
	Prestador R;
	struct celda *next;
}balde;

typedef struct RS{
	balde X[61];
	balde *cur;
	balde *aux;
	int CantR;
}RS;

void init_RS(RS *lis){
    int i;
    for(i=0;i<61;i++){
        (*lis).X[i].next = NULL;
    }
    (*lis).cur = NULL;
    (*lis).aux = NULL;
    (*lis).CantR = 0;
}

int hashing(long dni, int cant){
    char x[10];
    int longi, i;
    int contador = 0;
    sprintf(x, "%d",dni);
    longi = strlen(x);
    for(i=0;i<longi;i++){
        contador+=((int)x[i]*(i+1));
    }
    return (contador % cant);
}

int localizarRS(RS *l, long id, int *exito, float *costo){
    int pos = hashing(id,10);
    (*l).aux = &(l->X[pos]);
    (*l).cur = &(l->X[pos]);
    long aux1 = 0;
    if (l->cur == NULL) {
        *exito = 0;
        return 0;
    }
    while((l->cur != NULL) && l->cur->R.dni != id){
        //Costos
        l->aux = l->cur;
        l->cur = l->cur->next;
    }
    if ((*l).cur != NULL){
        aux1 = (*l).cur->R.dni;
    }
    if (aux1 == id){
        //Costos
        *exito = 1;
    }else *exito = 0;
    return *exito;
}

int AltaRS(RS *l, Prestador a, int *exito, float *costo){
    balde *x;
    int pos = hashing(a.dni,10);
    float c = 0;
    if(localizarRS(l,a.dni,exito,&c)){
        return *exito = 0;
    }else{
        x = (balde*)malloc(sizeof(balde));
        if (x==NULL){
            free((void*)x);
            return *exito = -1;
        }else{
            (*x).R = a;
            (*l).aux->next = x;
        }
        (*l).CantR++;
        //Costos.
        return *exito = 1;
    }
}



#endif // RS_H_INCLUDED
