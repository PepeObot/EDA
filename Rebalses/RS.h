#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Prestador.h"
#define fRS  64
// PARA EL RS SU MÁXIMO ES: RS MAX = 64.
// ÉSTOS SERÍAN SUS NÚMEROS PRIMOS MÁS CERCANOS.

typedef struct balde{
	Prestador R;
	struct balde *next;
}balde;

typedef struct RS{
	balde X[fRS];
	balde *cur;
	balde *aux;
	int CantR;
}RS;

Prestador vacio = {-1,"","","","",""};

void init_RS(RS *lis){
    int i;
    for(i=0;i<fRS;i++){
        lis->X[i].R = vacio;
        (*lis).X[i].next = NULL;
    }
    (*lis).cur = NULL;
    (*lis).aux = NULL;
    (*lis).CantR = 0;
}

void borrar_RS(RS *lis){
    int i;
    balde *tmp;
	for(i = 0; i < fRS; i++){
		lis->aux = &(lis->X[i]);
		lis->cur = lis->aux->next;
		while(lis->cur != NULL){
			tmp = lis->cur;
			lis->cur = lis->cur->next;
			free(tmp);
		}
	}
    lis->CantR= 0;
}

int hashing_rs(long dni, int cant){
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


int localizarRS(RS *l, long id, int *exito, float *costo,int *h){
    int pos = hashing_rs(id,fRS);
    *h=pos;
    *costo = 0;
    (*l).aux = &(l->X[pos]);
    (*l).cur = &(l->X[pos]);
    while((l->cur != NULL) && l->cur->R.dni != id){
        *costo = *costo + 1.0;
        l->aux = l->cur;
        l->cur = l->cur->next;
    }
    if(l->cur != NULL && l->cur->R.dni == id){
        *costo = *costo +1.0;
        *exito=1;
    }else *exito =0;
    return *exito;
}

int AltaRS(RS *l, Prestador a, int *exito, float *costo) {
    balde *x;
    float c = 0;
    int i;
    localizarRS(l, a.dni, exito, &c,&i);
    if (*exito == 1) {
        return *exito = 0;
    } else {
        if(l->X[i].R.dni == -1){
                l->X[i].R = a;
                l->X[i].next = NULL; // Consultar si lo dejo o lo saco.
        }else{
            x = (balde*)malloc(sizeof(balde));
            if (x == NULL) {
                free(x);
                return *exito = -1;
            } else {
                x->R = a;
                x->next = l->X[i].next;
                l->X[i].next = x;
            }
        }
        (*l).CantR++;
        *costo = c;
        *exito = 1;
    }
    return *exito;
}

int baja_RS(RS *l, Prestador a, int *exito, float *costo){
    float c = 0;
    int e = 0, i;
    if (localizarRS(l,a.dni,&e,&c,&i)){
        if (0==strcmpi((*l).cur->R.nomyape,a.nomyape)&&
        0==strcmpi((*l).cur->R.domicilio,a.domicilio)&&
        0==strcmpi((*l).cur->R.servicios,a.servicios)&&
        0==strcmpi((*l).cur->R.telefono,a.telefono)&&
        0==strcmpi((*l).cur->R.correo,a.correo)){
            if(l->cur==&(l->X[i])){
                if(l->cur->next == NULL){
                    l->X[i].R = vacio; // Pongo la posición en 0 para que lo marque vacio.
                    l->X[i].next = NULL;
                }else{
                    l->X[i].R = l->cur->next->R;
                    l->X[i].next = l->cur->next->next;
                }
            }else{
                l->aux->next = l->cur->next; // Al puntero siguiente del anterior le doy el puntero al siguiente del actual. Hago que el actual tenga el siguiente del actual, pero no lo trato como anterior del siguiente.
                l->cur = NULL; // Al puntero actual que es el que quiero eliminar lo pongo null y debajo lo libero.
                free(l->cur);
            }
            (*l).CantR = (*l).CantR-1;
            *exito = 1;
       }
    }else *exito = 0;
    return *exito;
}

Prestador evocar_rs(RS *l, Prestador a, int *exito, float *costo){
    float c =0;int i;
    Prestador r;
    if(localizarRS(l,a.dni,exito,&c,&i) == 1){
        r = l->cur->R;
        *costo = c;
        *exito = 1;
        return r;
    }else *exito = 0;
    *costo = c;
}

void mostrar_rs(RS *l, int *exito){
    int i = 0,c=0;
    balde *temp;
    for(i;i<fRS;i++){
        temp = &(l->X[i]);
        if(temp->R.dni == -1){
            printf("\nCabecera NRO: %d apunta a NULL, lista vacia.\n\n",i);
        }else{
            while(temp != NULL){
                c++;
                printf("Cabecera NRO: %d\n",i);
                printf("Prestador: %d\n",c);
                printf("Número de documento: %ld \n", temp->R.dni);
                printf("Nombre y Apellido: %s \n", temp->R.nomyape);
                printf("Domicilio : %s \n", temp->R.domicilio);
                printf("Correo electrónico: %s \n", temp->R.correo);
                printf("Servicio: %s \n", temp->R.servicios);
                printf("Número de teléfono: %s \n", temp->R.telefono);
                printf("*********************************\n");
                temp = temp->next;
            }
            if(i%5 == 0){
                fflush(stdin);
                printf("Presione ENTER para la página siguiente...\n");
                getchar();
            }
        }
    }
    //free(temp); // Ya que uso un nodo auxiliar lo libero para que no guarde memoria.
}

#endif // RS_H_INCLUDED
