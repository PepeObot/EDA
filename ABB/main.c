#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <ctype.h>
#include "Biseccion.h"
#include "Prestador.h"
#include "LSOSS.h"
#include "ABB.h"
#define MAX 110
#define inf 999999999


/*

                                    COMPARACION DE ESTRUCTURAS (Lote de Prueba dado por la Catedra)

                                            COSTOS          LSO     LSOBT   ABB
                                    _____________________________________________________
                                            MAX.ALTA        109,00  108,00  0,50
                                            MED.ALTA        28,71   27,71   0,50
                                            MAX.BAJA        98,00   97,00   1,50
                                            MED.BAJA        31,59   30,59   0,84
                                            MAX.EVOEX       99,00   15,00   23,00
                                            MED.EVOEX       37,79   11,64   11,03
                                            MAX.EVONOEX     84,00   15,00   21,00
                                            MED.EVONOEX     32,93   12,50   13,45




  Estas son las 3 estructuras solicitadas por la cátedra. Podemos ver que sus costos en algunos casos son bastantes parecidos, pero en otros como el ABB
podemos ver que es el más efectivo en cuanto a corrimientos y localización de elementos dentro de la misma. Los primeros 4 costos (MAX ALTA, MED ALTA, MAX BAJA, MED BAJA)
de las estructuras secuenciales como LSO y LSOBT, son practicamente iguales si no fueran porque en la LSO estamos considerando la marca de infinito, esto, no parece raro
ya que si estamos contando corrimientos de elementos dentro de la estructura tendría sentido que fueran casi iguales, ya que tienen la misma capacidad y mismo funcionamiento
de inserción de elementos y eliminación de elementos. En los costos de los evocar, el claro perderor sería la LSO ya que es mucho menos efectivo recorrer los N elementos de la
lista hasta encontrar el deseado, en cambio los de la LSOBT podemos ver que es mucho más efectivo ir partiendo cada vez en más partes chicas la lista hasta encontrarlo.
 En cuanto a los costos de alta y baja del ABB, se puede decir que van a tener un costo fijo ya que lo único que tenemos que correr en éste es un nodo tanto sea para la supresión de un elemento o la inserción. Los costos de evocar son otro tema, pero aún así podemos ver que siguen siendo muy efectivos comparados a las otras dos.

*/

typedef struct{
    float maximo_alta;
    float medio_alta;
    float maximo_baja;
    float medio_baja;
    float max_evo_succ;
    float med_evo_succ;
    float max_evo_fail;
    float med_evo_fail;
    float cant_altas;
    float cant_bajas;
    float cant_evos_succ;
    float cant_evos_fail;
}v_costo;

void init_costo(v_costo *x){
    (*x).maximo_alta=0;
    (*x).medio_alta=0;
    (*x).maximo_baja=0;
    (*x).medio_baja=0;
    (*x).max_evo_succ=0;
    (*x).med_evo_succ=0;
    (*x).max_evo_fail=0;
    (*x).med_evo_fail=0;
    (*x).cant_altas=0;
    (*x).cant_bajas=0;
    (*x).cant_evos_fail=0;
    (*x).cant_evos_succ=0;
}



int main(){
    setlocale(LC_ALL,"");
    int opcion,operacion,opcion_muestra;
    int cant_ss=0,cant_tris=0,cant_abb=0;
    int cant_altas,cant_bajas,cant_evos,cant_rep=0,cant_rep_trs=0;
    int exito_alta=0,exito_baja=0,exito_evo=0,red=0;
    ABB a;
    init_ABB(&a);
    //RS rs;
    //init_RS(&rs);
    cant_altas=0;cant_bajas=0;cant_evos=0;
    v_costo c_lss;
    v_costo c_ltris;
    v_costo c_abb;
    init_costo(&c_lss);
    init_costo(&c_ltris);
    init_costo(&c_abb);
    float costo;
    float cost;
    int pos=0;
    int i=0;
    cant_ss=0;
    cant_tris=0;
    cant_abb=0;
    Prestador aux;
    Prestador lista[MAX+1];
    Prestador lista_tris[MAX];
    init_prestador(lista);
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
                borrar_arbol(&a.raiz);
                init_ABB(&a);
                FILE *fp;
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
                                fgetc(fp);
                                costo=0;
                                exito_alta=0;
                                //AltaRS(&rs,aux,&exito_alta,&cost);
                                AltaABB(&a,aux,&exito_alta,&costo);
                                if(exito_alta==1){
                                    c_abb.cant_altas++;
                                    c_abb.medio_alta=c_abb.medio_alta+costo;
                                    if(costo>c_abb.maximo_alta)
                                        c_abb.maximo_alta=costo;
                                }
                                exito_alta=0;
                                if(aux.dni<inf && cant_ss<MAX)
                                    alta(lista,aux,&exito_alta,&cant_ss,&costo);
                                if(exito_alta==1){
                                    c_lss.cant_altas = c_lss.cant_altas +1.0;
                                    c_lss.medio_alta=c_lss.medio_alta+costo;
                                    if(costo>c_lss.maximo_alta){
                                        c_lss.maximo_alta = costo;
                                        }
                                }
                                if (exito_alta==-2){
                                    cant_rep++;
                                }
                                exito_alta=0;
                                alta_bise(lista_tris,aux,&exito_alta,&cant_tris,&costo);
                                if(exito_alta==1){
                                    c_ltris.cant_altas =  c_ltris.cant_altas +1;
                                    c_ltris.medio_alta=c_ltris.medio_alta+costo;
                                    if(costo>c_ltris.maximo_alta)
                                        c_ltris.maximo_alta=costo;

                                }
                                if (exito_alta==-2){
                                    cant_rep_trs++;
                                }
                                cant_altas++;
                                break;
                            }
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
                                costo=0;
                                exito_baja=0;
                                if(cant_ss>0 && aux.dni<inf){
                                    baja(lista,aux,&exito_baja,&cant_ss,&costo);
                                }
                                if(exito_baja==1){
                                    c_lss.cant_bajas = c_lss.cant_bajas +1;
                                    c_lss.medio_baja=c_lss.medio_baja+costo;
                                    if(costo>c_lss.maximo_baja)
                                        c_lss.maximo_baja=costo;
                                }
                                exito_baja=0;
                                costo=0;
                                if(cant_tris>0)
                                    baja_bise(lista_tris,aux,&exito_baja,&cant_tris,&pos,&costo);
                                if(exito_baja==1){

                                    c_ltris.cant_bajas = c_ltris.cant_bajas +1;
                                    c_ltris.medio_baja=c_ltris.medio_baja+costo;
                                    if(costo>c_ltris.maximo_baja)
                                        c_ltris.maximo_baja=costo;
                                }
                                exito_baja=0;
                                costo=0;
                                if(a.raiz != NULL){
                                    baja_ABB(&a,aux,&exito_baja,&costo);
                                }
                                if(exito_baja==1){
                                    c_abb.cant_bajas = c_abb.cant_bajas +1;
                                    c_abb.medio_baja=c_abb.medio_baja+costo;
                                    if(costo>c_abb.maximo_baja)
                                        c_abb.maximo_baja=costo;
                                }
                                cant_bajas++;
                                break;
                            }//fin case 2
                            case 3:{
                                costo=0;
                                exito_evo=0;
                                if(aux.dni<inf)
                                    evocar_prestador(lista,aux.dni,&exito_evo,&cant_ss,&costo);
                                if(exito_evo==1){
                                    c_lss.cant_evos_succ = c_lss.cant_evos_succ+1;
                                    c_lss.med_evo_succ=c_lss.med_evo_succ+costo;
                                    if(costo>c_lss.max_evo_succ)
                                        c_lss.max_evo_succ=costo;
                                }else{
                                    c_lss.cant_evos_fail = c_lss.cant_evos_fail+1;
                                    c_lss.med_evo_fail=c_lss.med_evo_fail+costo;
                                    if(costo>c_lss.max_evo_fail)
                                        c_lss.max_evo_fail=costo;
                                }
                                exito_evo=0;
                                evocar_prestador_bise(lista_tris,aux.dni,&exito_evo,&cant_tris,&costo);
                                if(exito_evo==1){
                                    c_ltris.cant_evos_succ = c_ltris.cant_evos_succ+1;
                                    c_ltris.med_evo_succ=c_ltris.med_evo_succ+costo;
                                    if(costo>c_ltris.max_evo_succ)
                                        c_ltris.max_evo_succ=costo;
                                }else{
                                    c_ltris.cant_evos_fail = c_ltris.cant_evos_fail+1;
                                    c_ltris.med_evo_fail=c_ltris.med_evo_fail+costo;
                                    if(costo>c_ltris.max_evo_fail)
                                        c_ltris.max_evo_fail=costo;
                                }
                                evocar_prestador_ABB(&a,aux.dni,&exito_evo,&costo);
                                if(exito_evo==1){
                                    c_abb.cant_evos_succ = c_abb.cant_evos_succ+1;
                                    c_abb.med_evo_succ=c_abb.med_evo_succ+costo;
                                    if(costo>c_abb.max_evo_succ)
                                        c_abb.max_evo_succ=costo;
                                }else{
                                    c_abb.cant_evos_fail = c_abb.cant_evos_fail+1;
                                    c_abb.med_evo_fail=c_abb.med_evo_fail+costo;
                                    if(costo>c_abb.max_evo_fail)
                                        c_abb.max_evo_fail=costo;

                                }
                            cant_evos++;
                            break;
                            }//fin case 3 de operaciones

                        }//fin switch operaciones

                    }//fin while
                    fclose(fp);

                                printf("Cantidad De Elementos en LSO: %d\n",cant_ss);
                                printf("Cantidad De Elementos en LSOBB: %d\n",cant_tris);
                                printf("Cantidad De Elementos en ABB: %d\n\n",a.Nodos);
                                printf("\t COMPARACION DE ESTRUCTURAS\n\n"
                   "COSTOS\t\tLSO\tLSOBT\tABB\n"
                   "_____________________________________________________\n");
            printf("MAX.ALTA\t%.2f\t%.2f\t%.2f\n",c_lss.maximo_alta,c_ltris.maximo_alta,c_abb.maximo_alta);
            printf("MED.ALTA\t%.2f\t%.2f\t%.2f\n",c_lss.medio_alta/c_lss.cant_altas,c_ltris.medio_alta/c_ltris.cant_altas,c_abb.medio_alta/c_abb.cant_altas);
            printf("MAX.BAJA\t%.2f\t%.2f\t%.2f\n",c_lss.maximo_baja,c_ltris.maximo_baja,c_abb.maximo_baja);
            printf("MED.BAJA\t%.2f\t%.2f\t%.2f\n",c_lss.medio_baja/c_lss.cant_bajas,c_ltris.medio_baja/c_ltris.cant_bajas,c_abb.medio_baja/c_abb.cant_bajas);
            printf("MAX.EVOEX\t%.2f\t%.2f\t%.2f\n",c_lss.max_evo_succ,c_ltris.max_evo_succ,c_abb.max_evo_succ);
            printf("MED.EVOEX\t%.2f\t%.2f\t%.2f\n",c_lss.med_evo_succ/c_lss.cant_evos_succ,c_ltris.med_evo_succ/c_ltris.cant_evos_succ,c_abb.med_evo_succ/c_abb.cant_evos_succ);
            printf("MAX.EVONOEX\t%.2f\t%.2f\t%.2f\n",c_lss.max_evo_fail,c_ltris.max_evo_fail,c_abb.max_evo_fail);
            printf("MED.EVONOEX\t%.2f\t%.2f\t%.2f\n",c_lss.med_evo_fail/c_lss.cant_evos_fail,c_ltris.med_evo_fail/c_ltris.cant_evos_fail,c_abb.med_evo_fail/c_abb.cant_evos_fail);
                     }//fin else de lectura de archivo exitosa
                break;
            }//fin case 1 opciones menu
            case 2:{
                do{
                    printf("1. Mostrar LSO Busqueda Secuencial\n");
                    printf("2. Mostrar LSO Busqueda por Triseccion\n");
                    printf("3. Mostrar Arbol Binario de Busqueda\n");
                    printf("4. Volver al Menu\n");
                    printf("Elige una opcion: ");
                    fflush(stdin);
                    scanf("%d", &opcion_muestra);
                    switch(opcion_muestra){
                        case 1:{
                            if(cant_ss>0)
                                muestra(lista,cant_ss);
                            else
                                printf("\tLa lista esta vacia\n");
                            break;
                        }
                        case 2:{
                            if(cant_tris>0)
                                muestra_bise(lista_tris,cant_tris);
                            else
                                printf("\tLa lista esta vacia\n");
                            break;
                        }
                        case 3:{
                            if(a.Nodos>0)
                                muestra_abb(a.raiz);
                            else
                                printf("\tEl arbol esta vacio\n");
                            break;
                        }
                        case 4:{

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
                printf("Opci�n no v�lida\n");
                break;
        }//fin switch menu principal
    } while (opcion != 3);

    return 0;

}// FIN MAIN
