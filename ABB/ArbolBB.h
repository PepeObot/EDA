#ifndef ARBOLBB_H_INCLUDED
#define ARBOLBB_H_INCLUDED
typedef struct Nodo{
    Prestador vipd;
    struct Nodo *siguiente;
    }nodo;

typedef struct{
    Nodo *raiz;
    Nodo *hd;
    Nodo *hi;
}Arbol;


void init(Arbol *a)
{
    (*a).raiz = NULL;
    (*a).hd = NULL;
    (*a).hi = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int isempty(Arbol a) //La lista no tiene elementos
{
    if (a.raiz==NULL) return 1;
    else return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int isfull(Arbol a) //El parámetro es innecesario en el caso de una lista dinámica
{
    nodo *prueba;
    prueba = (nodo*)malloc(sizeof(nodo));
    if (prueba==NULL) return 1;
    else
    {
        free((void*)prueba);
        return 0;
    }
}

void localizar_abb(Arbol *a,int id,int *exito){
    while(!isempty(a)){


    }

}

#endif // ARBOLBB_H_INCLUDED
