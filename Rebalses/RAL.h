#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#define MAX_RAL 137//137
 typedef struct
 {
    char estado; // V (virgen) L (libre) O (ocupada)
    Prestador dato;
 }Balde;

 typedef struct
 {
    Balde arr[MAX_RAL];
    int cantidad;
 }RAL;

void inicializarRAL(RAL *r){
    int i;
    for(i=0;i<MAX_RAL;i++){
        r->arr[i].estado='V';
    }
    r->cantidad=0;
}

int hashing(long dni, int M){
    char x[10];
    int longi, i;
    int contador = 0;
    sprintf(x, "%ld",dni);
    longi = strlen(x);
    for(i=0;i<longi;i++){
        contador+=((int)x[i]*(i+1));
    }
    return (contador % M);
}
void localizar_ral(RAL ral,int dni, int *pos, int *exito, float *cost){
    int i = hashing(dni,MAX_RAL);
    int j=1;
    int pLibre = -1;
    while(j < MAX_RAL){

        if((ral.arr[i].estado == 'L') && (pLibre == -1)){
            pLibre = i;
        }
        if(ral.arr[i].estado == 'V'){
            *cost = *cost + 1.0;
            if(pLibre == -1)
                *pos = i;
            else
                *pos = pLibre;
            *exito = 0;
            return;
        }
        if((ral.arr[i].estado == 'O') && (ral.arr[i].dato.dni == dni)){
            *cost = *cost + 1.0;
            *pos = i;
            *exito = 1;
            return;
        }
        *cost = *cost + 1.0;
        i = (i+1) % MAX_RAL;
        j = j + 1;
    }
    *exito = -1;
}

/*void localizar_ral(RAL r, long dni, int *pos,int *exito,float *costo){
    int i=hashing(dni,MAX_RAL);
    *costo = 0;
    int j=0;
    int flag=0;
    while(j<MAX_RAL && r.arr[i].estado != 'V'){
        *costo=*costo+1;
        if((r.arr[i].dato.dni==dni)&&(r.arr[i].estado=='O')){
            *exito=1;
            *pos=i;
            return *exito;
        }
        else{
            if ((r.arr[i].estado=='L')&& (flag==0))
            {
                flag++;
                *pos=i;
            }
            j++;
            i=(i+1)%MAX_RAL;
        }
    }
    *costo=*costo+1;
    if(flag==1)
        *exito=0;//llegue a un balde libre
    else{
        *pos=i;
        *exito=0;} //llegue un balde virgen
    if(j==MAX_RAL)
        *exito=-1;// no hay espacio
}*/

int alta_ral(RAL *r, Prestador p,int *exito,float *costo){
    int pos=0;
    if((*r).cantidad==MAX_RAL){
        *exito=-1;
        return *exito;
    }else{
    localizar_ral(*r,p.dni,&pos,exito,costo);
    if(*exito==1){
        *exito=0; //se encontro al prestador
        return *exito;
    }
    if(*exito==-1){
        *exito=-1; //no hay espacio
        return *exito;
    }
    if (*exito==0){
        (*r).arr[pos].dato=p;
        (*r).arr[pos].estado='O';
        (*r).cantidad++;
        *exito=1; // alta exitosa
        return *exito;
    }}
}

void baja_ral(RAL *r,Prestador p, int *exito,float *costo){
    int pos=0;
    localizar_ral(*r,p.dni,&pos,exito,costo);
    if(*exito!=1)
        *exito=-1; //no se encontro al prestador
    else
        if ((0 == strcmpi(r->arr[pos].dato.nomyape, p.nomyape) &&
            0 == strcmpi(r->arr[pos].dato.domicilio, p.domicilio) &&
            0 == strcmpi(r->arr[pos].dato.servicios, p.servicios) &&
            0 == strcmpi(r->arr[pos].dato.correo, p.correo) &&
            0 == strcmpi(r->arr[pos].dato.telefono, p.telefono))){
                r->arr[pos].estado='L';
                r->cantidad=r->cantidad-1;
                *exito=1;
        }
        else
            *exito=-1; //no coinciden los datos para confirmacion
    }

Prestador evocar_ral(RAL r,long dni,int *exito,float *costo){
    int pos=0;
    Prestador aux;
    float c= 0;
    localizar_ral(r,dni,&pos,exito,&c);
    if (*exito==1){

        *costo = c;
        return r.arr[pos].dato;
    }else{
        *costo = c;
        *exito=0;
        return aux;}
}






#endif // RAL_H_INCLUDED
