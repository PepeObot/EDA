#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define MAX_RAC 131 //131

typedef struct {
    char estado;
    Prestador dato;
}BaldeRAC;

typedef struct {
    BaldeRAC arr[MAX_RAC];
    int cantidad;
}RAC;

void inicializarRAC(RAC *rac){
    int i;
    for(i=0;i<MAX_RAC;i++){
        rac->arr[i].estado='V';
    }
    rac->cantidad=0;
}


int hashing_rac(long dni, int M){
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

void localizarRAC(RAC rac,int dni, int *pos, int *exito, float *cost){
    int i = hashing(dni,MAX_RAC);
    int j=0;
    int desplazamiento=1;
    int pLibre = -1;
    while(j < MAX_RAC){
        
        if((rac.arr[i].estado == 'L') && (pLibre == -1)){
            pLibre = i;
        }
        if(rac.arr[i].estado == 'V'){
            *cost = *cost + 1.0;
            if(pLibre == -1)
                *pos = i;
            else
                *pos = pLibre;
            *exito = 0;
            return;
        }
        if((rac.arr[i].estado == 'O') && (rac.arr[i].dato.dni == dni)){
            *cost = *cost + 1.0;
            *pos = i;
            *exito = 1;
            return;
        }
        *cost = *cost + 1.0;
        i = (i+desplazamiento) % MAX_RAL;
        desplazamiento++;
        j = j + 1;
    }
    *exito = -1;
}

int alta_rac(RAC *rac, Prestador p, int *exito, float *costo){
    int pos;
    float cos;
    if((*rac).cantidad==MAX_RAC){
        *exito -1;
        return *exito;
    }else{
    localizarRAC(*rac,p.dni,&pos,exito,costo);
    if(*exito==1){
        *exito=0; // se econtro al prestador
        return *exito;
    }
    if(*exito==-1){
        *exito=-1; // no hay espacio
        return *exito;
    }
    if (*exito==0){
        (*rac).arr[pos].dato=p;
        (*rac).arr[pos].estado='O';
        (*rac).cantidad = rac->cantidad +1;
        *exito=1; //alta exitosa
        return *exito;
    }}
}

void baja_rac(RAC *rac, Prestador p, int *exito, float *costo){
    int pos;
    localizarRAC(*rac,p.dni,&pos,exito,costo);
    if(*exito!=1)
        *exito=-1; // no se encontro al prestador
    else{
        if ((0 == strcmpi(rac->arr[pos].dato.nomyape, p.nomyape) &&
            0 == strcmpi(rac->arr[pos].dato.domicilio, p.domicilio) &&
            0 == strcmpi(rac->arr[pos].dato.servicios, p.servicios) &&
            0 == strcmpi(rac->arr[pos].dato.correo, p.correo) &&
            0 == strcmpi(rac->arr[pos].dato.telefono, p.telefono))){
                rac->arr[pos].estado='L';
                rac->cantidad = rac->cantidad -1;
                *exito=1; // baja exitosa
        }
        else
            *exito=-1; //no coinciden los datos para confirmacion
    }
}

Prestador evocar_rac(RAC *rac, long dni, int *exito, float *costo){
    Prestador aux;
    int pos;
    float c = 0;
    localizarRAC(*rac,dni,&pos,exito,&c);
    if(*exito!=1)
        *exito=-1; // no se encontro al prestador
    else{
        aux=rac->arr[pos].dato;
        *costo = c;
        *exito=1;
        return aux;
    }
    *costo = c;
}


#endif // RAC_H_INCLUDED
