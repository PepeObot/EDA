#ifndef BISECCION_H_INCLUDED
#define BISECCION_H_INCLUDED
#define MAX 110
#define inf 999999999
#include "Prestador.h"
#include <string.h>
#include <locale.h>

void localizar_bise(Prestador lista[],long id, int *pos, int *exito, int *cant, float *costo){
    int li,ls,m;li = 0;ls = *cant;
    int l = 0;
    m=floor((li+ls)/2.0);
    if(cant != 0){
        while (li<ls && id != lista[m].dni){
            (*costo) = (*costo)+1;
            if(id > lista[m].dni)
            {
                li = m+1;
            }
            else
            {
                ls = m;
            }
            m=floor((li+ls)/2.0);
        }
        if(li<ls)
            *costo = *costo +1;
        if (l == 0 && ls != 0){
            (*costo) = (*costo)+1;
        }
        if (lista[m].dni == id){
            (*costo) = (*costo)+1;
            *exito = 1;
        }else *exito = 0;
    }
    *pos = m;
}

void alta_bise(Prestador lista[], Prestador x, int *exito, int *cant, float *costo) {
    int i = 0;
    int pos = 0;
    if ((*cant + 1) > MAX) {
        *exito = -1;
    } else {
        localizar_bise(lista, x.dni, &pos, exito, cant, costo);
        if (*exito == 1) {
            *exito = -2;
        } else {
            i = (*cant);
            *costo = 0;
            for (i; pos < i; i--) {
                lista[i] = lista[i - 1];
                *costo=*costo+1.0;
            }
            lista[i] = x;
            *exito = 1;
            (*cant)++;
        }
    }
}

void baja_bise(Prestador lista[], Prestador aux, int *exito, int *cant, int *pos, float *costo) {
    int op;
    int i = *cant;
    localizar_bise(lista, aux.dni, pos, exito, cant, costo);
    if (*exito != 1) {
        *exito = -1;
    } else {
        if (0 == strcmpi(lista[*pos].nomyape, aux.nomyape) &&
            0 == strcmpi(lista[*pos].domicilio, aux.domicilio) &&
            0 == strcmpi(lista[*pos].servicios, aux.servicios) &&
            0 == strcmpi(lista[*pos].correo, aux.correo) &&
            0 == strcmpi(lista[*pos].telefono, aux.telefono)) {
            *costo = 0;
            for (i = *pos; i < *cant; i++) {
                lista[i] = lista[i + 1];
                *costo=*costo+1.0;
            }
            *costo = *costo -1;
            (*cant)--;
            *exito = 1;
        } else {
            *exito = 0;
        }
    }
}

Prestador evocar_prestador_bise(Prestador lista[],long dni, int *exito,int *cant,float *costo){
    Prestador aux;
    int pos =0;
    float c = 0;
    localizar_bise(lista,dni,&pos,exito,cant,&c);
    if(*exito==1){
        *costo = c;
        aux.dni=lista[pos].dni;
        strcpy(aux.nomyape,lista[pos].nomyape);
        strcpy(aux.correo,lista[pos].correo);
        strcpy(aux.servicios,lista[pos].servicios);
        strcpy(aux.domicilio,lista[pos].domicilio);
        strcpy(aux.telefono,lista[pos].telefono);
        return aux;
    }else
        *costo = c;
        *exito=0;
}

void muestra_bise(Prestador lista[], int cant){
    setlocale(LC_ALL,"");
    int i = 0;
    int exito;
    while(i < cant){
        printf("Prestador: %d\n",i);
        printf("Número de documento: %ld \n", lista[i].dni);
        printf("Nombre y Apellido: %s \n", lista[i].nomyape);
        printf("Domicilio : %s \n", lista[i].domicilio);
        printf("Correo electrónico: %s \n", lista[i].correo);
        printf("Servicio: %s \n", lista[i].servicios);
        printf("Número de teléfono: %s \n", lista[i].telefono);
        printf("******************************************\n");
        i++;
        if(i%5 == 0){
            fflush(stdin);
            printf("Presione ENTER para la página siguiente...\n");
            getchar();
        }
    }
}

#endif // BISECCION_H_INCLUDED
