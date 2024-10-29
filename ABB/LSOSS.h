#ifndef LSOSS_H_INCLUDED
#define LSOSS_H_INCLUDED
#include <string.h>
#include <locale.h>
#include "Prestador.h"

void localizar(Prestador lista[], long id, int *pos, int *exito, int *cant,float *costo){
    int i = 0;
    *costo=0;
    if(cant >= 0){
        while(lista[i].dni < id){
            i++;
            *costo=*costo+1.0;
        }
        *costo=*costo+1.0;
        if(lista[i].dni == id){
            *costo=*costo+1.0;
            *exito = 1; //se encontr�
            *pos = i; // devuelvo la posici�n
        }else{
            *costo=*costo+1.0;
            *exito = 0; //no se encontr� el elemento
            *pos = i;
        }
    }else{
        *exito = -1; //no hay elementos guardados
        *pos = 0;
    }
}

void alta(Prestador lista[], Prestador x, int *exito, int *cant, float *costo) {
    int i = 0;
    int pos = 0;
    if ((*cant) >=MAX) {
        *exito = -1;
    } else {
        localizar(lista, x.dni, &pos, exito, cant, costo);
        if (*exito == 1) {
            *exito = -2;
        } else {
            i = (*cant);
            *costo = 0;
            for (i; i>=pos; i--) {
                lista[i+1] = lista[i];
                (*costo)=(*costo)+1.0;
            }
            lista[pos] = x;
            *exito = 1;
            (*cant)++;
        }
    }
}

void baja(Prestador lista[], Prestador aux, int *exito, int *cant,float *costo) {
    int op;
    int i = *cant;
    int pos = 0;
    localizar(lista, aux.dni, &pos, exito, cant, costo);
    if (*exito != 1) {
        *exito = -1;
    } else {
        if (0 == strcmpi(lista[pos].nomyape, aux.nomyape) &&
            0 == strcmpi(lista[pos].domicilio, aux.domicilio) &&
            0 == strcmpi(lista[pos].servicios, aux.servicios) &&
            0 == strcmpi(lista[pos].correo, aux.correo) &&
            0 == strcmpi(lista[pos].telefono, aux.telefono)) {
            *costo = 0;
            for (i = pos; i < *cant; i++) {
                lista[i] = lista[i + 1];
                *costo=*costo+1.0;
            }
            (*cant)--;
            *exito = 1;
        } else {
            *exito = 0;
        }
    }
}

Prestador evocar_prestador(Prestador lista[],long dni, int *exito,int *cant,float *costo){
    Prestador aux;
    int pos =0;
    localizar(lista,dni,&pos,exito,cant,costo);
    if(*exito==1){
        aux.dni=lista[pos].dni;
        strcpy(aux.nomyape,lista[pos].nomyape);
        strcpy(aux.correo,lista[pos].correo);
        strcpy(aux.servicios,lista[pos].servicios);
        strcpy(aux.domicilio,lista[pos].domicilio);
        strcpy(aux.telefono,lista[pos].telefono);
        return aux;
    }else
        *exito=0;
}

void muestra(Prestador lista[], int cant){
    setlocale(LC_ALL,"");
    int i = 0;
    int exito;
    while(i < cant){
        printf("Prestador: %d\n",i);
        printf("N�mero de documento: %ld \n", lista[i].dni);
        printf("Nombre y Apellido: %s \n", lista[i].nomyape);
        printf("Domicilio : %s \n", lista[i].domicilio);
        printf("Correo electr�nico: %s \n", lista[i].correo);
        printf("Servicio: %s \n", lista[i].servicios);
        printf("N�mero de tel�fono: %s \n", lista[i].telefono);
        printf("******************************************\n");
        i++;
        if(i%5 == 0){
            fflush(stdin);
            printf("Presione ENTER para la p�gina siguiente...\n");
            getchar();
        }
    }
}



#endif // LSOSS_H_INCLUDED
