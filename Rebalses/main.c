#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Prestador.h"
#include "RAL.h"
#include "RAC.h"
#include "RS.h"

/*
                                            COMPARACION DE ESTRUCTURAS

                                        COSTOS          RS      RAL     RAC
                                _____________________________________________________
                                        MAX.EVOEX       7,00    55,00   33,00
                                        MED.EVOEX       1,55    2,54    2,09
                                        MAX.EVONOEX     4,00    62,00   131,00
                                        MED.EVONOEX     1,18    24,75   16,57
    Aquí las 3 estructuras, Rebalse Separado, Rebalso Abierto Lineal, Rebalse Abierto Cuadrático. Podemos ver que tenemos costos tanto bajos como altos,
     la mejor estructura (en costos) es el Rebalse Separado, con unos máximos muy bajos, podríamos decir que le sigue el RAL ya que su máximo de evocar no exitoso
    es bastante bajo comparado con el del RAC, que va hasta el final de la estructura comparando hasta la última celda. Lo que nos sorprendió fue el Rebalse Separado
    que incluso le gana a la búsqueda binaria y a los BST, teniendo unos máximos muy bajos.
*/

typedef struct {
    float max_evo_succ;
    float max_evo_fail;
    float med_evo_succ;
    float med_evo_fail;
    float cant_evo_succ;
    float cant_evo_fail;
}v_costos;

void init_costos(v_costos *c){
    c->max_evo_fail = 0;
    c->max_evo_succ = 0;
    c->med_evo_fail = 0;
    c->med_evo_succ = 0;
    c->cant_evo_succ = 0;
    c->cant_evo_fail = 0;
}

int main(){
    setlocale(LC_ALL,"");
    int opcion, opcion_muestra,operacion,exito;
    float costo,cost;
    int s=0,t=0;
    v_costos rs_c,ral_c,rac_c;
    init_costos(&rs_c);
    init_costos(&ral_c);
    init_costos(&rac_c);
    Prestador aux;
    RS r;
    RAL lineal;
    RAC cuadratico;
    inicializarRAL(&lineal);
    inicializarRAC(&cuadratico);
    init_RS(&r);
    do {
        printf("1. Comparar Estructuras\n");
        printf("2. Mostrar Estructuras\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        fflush(stdin);
        scanf("%d", &opcion);
        system("cls");

        switch (opcion) {
            case 1:{
                FILE *fp;
                borrar_RS(&r);
                init_RS(&r);
                inicializarRAC(&cuadratico);
                inicializarRAL(&lineal);
                if((fp = fopen("Operaciones-Prestadores.txt","r"))==NULL){
                    printf("\tNo se pudo abrir el archivo\n");
                }
                else{
                    while(!(feof(fp))){
                        fflush(stdin);
                        fscanf(fp,"%d\n",&operacion);
                        fscanf(fp,"%ld\n",&aux.dni);
                        switch(operacion){
                            case 1:{
                                fflush(stdin);
                                fscanf(fp, "%80[^\n]", aux.nomyape);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.servicios);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.domicilio);
                                fgetc(fp);
                                fscanf(fp, "%50s", aux.correo);
                                fgetc(fp);
                                fscanf(fp, "%s", aux.telefono);
                                costo=0;
                                alta_ral(&lineal,aux,&exito,&cost);
                                costo=0;
                                alta_rac(&cuadratico,aux,&exito,&cost);
                                costo=0;
                                AltaRS(&r,aux,&exito,&costo);
                                break;
                            }//fin case 1 alta
                            case 2:{
                                fscanf(fp, "%80[^\n]", aux.nomyape);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.servicios);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.domicilio);
                                fgetc(fp);
                                fscanf(fp, "%50s", aux.correo);
                                fgetc(fp);
                                fscanf(fp, "%s", aux.telefono);
                                fgetc(fp);
                                baja_RS(&r,aux,&exito,&cost);
                                if(lineal.cantidad>0)
                                    baja_ral(&lineal,aux,&exito,&cost);
                                if(cuadratico.cantidad>0)
                                    baja_rac(&cuadratico,aux,&exito,&cost);
                                break;
                            }//fin case 2 baja
                            case 3:{
                                exito = 0;
                                costo=0;
                                evocar_ral(lineal,aux.dni,&exito,&costo);
                                if(exito==1){
                                    ral_c.cant_evo_succ = ral_c.cant_evo_succ +1;
                                    ral_c.med_evo_succ = ral_c.med_evo_succ+costo;
                                    if (costo>ral_c.max_evo_succ)
                                        ral_c.max_evo_succ = costo;
                                    }else{
                                        ral_c.cant_evo_fail = ral_c.cant_evo_fail+1;
                                        ral_c.med_evo_fail = ral_c.med_evo_fail + costo;
                                        if (costo>ral_c.max_evo_fail)
                                            ral_c.max_evo_fail = costo;
                                    }
                                exito = 0;
                                costo=0;
                                evocar_rac(&cuadratico,aux.dni,&exito,&costo);
                                if(exito==1){
                                    rac_c.cant_evo_succ = rac_c.cant_evo_succ +1;
                                    rac_c.med_evo_succ = rac_c.med_evo_succ+costo;
                                    if (costo>rac_c.max_evo_succ)
                                        rac_c.max_evo_succ = costo;
                                    }else{
                                        rac_c.cant_evo_fail = rac_c.cant_evo_fail+1;
                                        rac_c.med_evo_fail = rac_c.med_evo_fail + costo;
                                        if (costo>rac_c.max_evo_fail)
                                            rac_c.max_evo_fail = costo;
                                    }
                                exito = 0;
                                costo = 0;
                                evocar_rs(&r,aux,&exito,&costo);
                                if(exito==1){
                                    rs_c.cant_evo_succ = rs_c.cant_evo_succ +1;
                                    rs_c.med_evo_succ = rs_c.med_evo_succ+costo;
                                    if (costo>rs_c.max_evo_succ)
                                        rs_c.max_evo_succ = costo;
                                    }else{
                                        rs_c.cant_evo_fail = rs_c.cant_evo_fail+1;
                                        rs_c.med_evo_fail = rs_c.med_evo_fail + costo;
                                        if (costo>rs_c.max_evo_fail)
                                            rs_c.max_evo_fail = costo;
                                    }
                            break;
                            }//fin case 3 evocacion

                        }//fin switch operaciones

                    }//fin while
                    fclose(fp);
                                //cuentaRAL(&lineal);
                                //cuentaRAC(&cuadratico);
                                printf("Lineal:%d\n",lineal.cantidad);
                                printf("Cuadratico: %d\n",cuadratico.cantidad);
                                printf("Separado: %d\n",r.CantR);///Aca va la cantidad de elementos printeada
                                printf("\t COMPARACION DE ESTRUCTURAS\n\n"
                   "COSTOS\t\tRS\tRAL\tRAC\n"
                   "_____________________________________________________\n");
            printf("MAX.EVOEX\t%.2f\t%.2f\t%.2f\n",rs_c.max_evo_succ,ral_c.max_evo_succ,rac_c.max_evo_succ);
            printf("MED.EVOEX\t%.2f\t%.2f\t%.2f\n",rs_c.med_evo_succ/rs_c.cant_evo_succ,ral_c.med_evo_succ/ral_c.cant_evo_succ,rac_c.med_evo_succ/rac_c.cant_evo_succ);
            printf("MAX.EVONOEX\t%.2f\t%.2f\t%.2f\n",rs_c.max_evo_fail,ral_c.max_evo_fail,rac_c.max_evo_fail);
            printf("MED.EVONOEX\t%.2f\t%.2f\t%.2f\n",rs_c.med_evo_fail/rs_c.cant_evo_fail,ral_c.med_evo_fail/ral_c.cant_evo_fail,rac_c.med_evo_fail/rac_c.cant_evo_fail);
                     }//fin else de lectura de archivo exitosa
                break;
            }//fin case 1 opciones menu
            case 2:{
                do{
                    printf("1. Mostrar Rebalse Abierto Lineal\n");
                    printf("2. Mostrar Rebalse Abierto Cuadratico\n");
                    printf("3. Mostrar Rebalse Separado\n");
                    printf("4. Volver al Menu\n");
                    printf("Elige una opcion: ");
                    fflush(stdin);
                    scanf("%d", &opcion_muestra);
                    switch(opcion_muestra){
                        case 1:{
                            if(lineal.cantidad>0)
                                mostrar_ral(lineal);
                            else
                                printf("\tNo hay elementos en la estructura\n");
                            break;
                        }
                        case 2:{
                            if(cuadratico.cantidad>0)
                                mostrar_rac(cuadratico);
                            else
                                printf("\tNo hay elementos en la estructura\n");
                            break;
                        }
                        case 3:{
                            if(r.CantR>0)
                                mostrar_rs(&r,&exito);
                            else
                                printf("\tNo hay elementos en la estructura\n");
                            break;
                        }
                        case 4:{
                            //no hace nada solo para salir del menu muestra
                            break;}
                        default:
                            printf("Ingrese una opcion valida\n");
                            break;
                    }//fin switch opcion muestra

                }while (opcion_muestra!=4);


            break;
            }//fin case 2 menu opciones
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }//fin switch menu principal
    } while (opcion != 3);

    return 0;
}//fin MAIN




void mostrar_ral(RAL r){
int i,j=0;
for(i=0;i<MAX_RAL;i++){
    if(r.arr[i].estado=='O'){
        //muestro los datos
        j++;
        printf("Celda numero: %d\n",i);
        printf("Número de documento: %ld \n", r.arr[i].dato.dni);
        printf("Nombre y Apellido: %s \n", r.arr[i].dato.nomyape);
        printf("Domicilio : %s \n", r.arr[i].dato.domicilio);
        printf("Correo electrónico: %s \n", r.arr[i].dato.correo);
        printf("Servicio: %s \n", r.arr[i].dato.servicios);
        printf("Número de teléfono: %s \n", r.arr[i].dato.telefono);
        printf("*********************************\n");
        }//fin 1er if
    if(r.arr[i].estado=='V'){
        printf("*********************************\n");
        printf("\n\tLa celda numero %d es virgen(V)\n",i);
        printf("*********************************\n");
    }

    if(r.arr[i].estado=='L'){
         printf("*********************************\n");
         printf("\n\tLa celda numero %d es libre(L)\n",i);
         printf("*********************************\n");}
    if(i%5 == 0){
        fflush(stdin);
        printf("Presione ENTER para la página siguiente...\n");
        getchar();
        }
    }//fin for
}
void mostrar_rac(RAC r){
int i,j=0;
for(i=0;i<MAX_RAC;i++){
    if(r.arr[i].estado=='O'){
        //muestro los datos
        j++;
        printf("Celda numero: %d\n",i);
        printf("Número de documento: %ld \n", r.arr[i].dato.dni);
        printf("Nombre y Apellido: %s \n", r.arr[i].dato.nomyape);
        printf("Domicilio : %s \n", r.arr[i].dato.domicilio);
        printf("Correo electrónico: %s \n", r.arr[i].dato.correo);
        printf("Servicio: %s \n", r.arr[i].dato.servicios);
        printf("Número de teléfono: %s \n", r.arr[i].dato.telefono);
        printf("*********************************\n");
        }//fin 1er if
    if(r.arr[i].estado=='V'){
        printf("*********************************\n");
        printf("\n\tLa celda numero %d es virgen(V)\n",i);
        printf("*********************************\n");
    }

    if(r.arr[i].estado=='L'){
         printf("*********************************\n");
         printf("\n\tLa celda numero %d es libre(L)\n",i);
         printf("*********************************\n");}
    if(i%5 == 0){
        fflush(stdin);
        printf("Presione ENTER para la página siguiente...\n");
        getchar();
        }
    }//fin for
}
