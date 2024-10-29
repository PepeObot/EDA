#ifndef PRESTADOR_H_INCLUDED
#define PRESTADOR_H_INCLUDED
//include setlocale
typedef struct{
    long dni;
    char nomyape[80];
    char servicios[120];
    char domicilio[120];
    char correo[50];
    char telefono[30];
}Prestador;


void init_prestador(Prestador lista[]){
    lista[0].dni=999999999;
    strcpy(lista[0].nomyape,"INF");
    strcpy(lista[0].servicios,"INF");
    strcpy(lista[0].correo,"INF");
    strcpy(lista[0].domicilio,"INF");
    strcpy(lista[0].telefono,"INF");
}
#endif // PRESTADOR_H_INCLUDED
