//Funciones con lista de adyacencia

/*Suponemos que tenemos un arreglo de nodo llamado lista que en la cabecera solo se encuentra
el identificador del vertice y un struct nodo, el cual tiene el vertice y el puntero siguiente*/

/*Consigna: Dados dos vertices a y b devuelva verdadero si hay una arista entre ellos,
y falso en otro caso.*/

Function incidentes (in a, in b, in lista): bool;
    Nodo actual;
    int i = 0;
    while(a <> lista[i].vertice) /*Buscamos la lista de a*/
        i++;
    end while 
    actual = lista[i].sig;
    while (actual != NULL)
        if(actual.vertice == b)
            return true;
        end if
        actual = actual.sig;
    end while
    while(b <> lista[i].vertice) /*Buscamos la lista de b*/
        i++;
    end while 
    actual = lista[i].sig;
    while (actual != NULL)
        if(actual.vertice == a)
            return true;
        end if
        actual = actual.sig;
    end while
    return false;
end


/*Consigna: Devolver el grado de salida de cada vertice del grafo.*/

Function gradoDeSalida (in lista, in grados[], in dim):int; /*grados viene con todo 0*/
    Nodo actual;
    int i = 0;
    while (i < dim)
        int grado=0;
        actual = lista[i].sig;
        while (actual <> NULL)
            grado++;
            actual = actual.sig;
        end while
        grados[i] = grado;
        i++;
    end while
    return grados[];
end


/*Consigna: Devolver el grado de entrada de cada vertice del grafo.*/
Function gradoDeEntrada(in lista, in grados[] in dim): int;
    Nodo actual;
    int i = 0;
    for(i = 0; i < dim; i++)
        int grado = 0;
        for(int j = 0; j < dim; j++)
            actual = lista[j].sig;
            while (actual <> NULL)
                if(actual.vertice == lista[i].vertice)
                    grado++;
                end if
                actual = actual.sig;
            end while
        end for
        grados[i] = grado;
    end for
    return grados[];
end



//Funciones con matriz de adyacencia

/*Consigna: Dados dos vertices i y j devuelva verdadero si hay una arista entre ellos,
y falso en otro caso.*/

Function incidencia(in i, in j, in matrix):bool;
    if(matrix[i][j] == 1 OR matrix [j][i] == 1)
        return true;
    endif
    return false;
end

/*Consigna: Devolver el grado de salida de cada vertice del grafo.*/

Function gradoDeSalida(in dimFila, in grados[] in matrix):int;
    int actual=0;
    while(actual<dimFila)
        int grado=0;
        if(matrix[actual]==1)
            grado++;
        end if
        grados[actual] = grado;
        actual++;
    end while
    return grados[];
end



//Parvas

typedef struct{
	char nombre;
	int prioridad; //parva usa este campo
}nupla;

typedef struct{
	int arr[MAX];
	int cantidad;
}parva;

void intercambio(int* x, int* y){
    int aux;
    temp = *x;
    *x = *y;
    *y = aux;
}

void hundir(parva p, int i){
	int left = 2*i;
	int right = 2*i + 1;
	if(left > p.cantidad)
		return;
	else{
		if(p.arr[left] < p.arr[i] || p.arr[right] < p.arr[i]){
			if(p.arr[left] < p.arr[right]){
				intercambio(p.arr[i], p.arr[left]);
				hundir(p, left);
			}
			else{
				intercambio(p.arr[i], p.arr[right]);
				hundir(p, right);
			}
		}
		return;
	}
}

void flotar(int arr[], int i){
	int padre = floor(i/2);

	if(i == 1 || arr[i] >= arr[padre])
		return;
	else{
		intercambio(arr[i], arr[padre]);
		flotar(arr, padre);
	}
}

bool insertar(parva p, int i){
	if(p.cantidad == MAX)
		return false;
	
	else{
		p.cantidad++;
		p.arr[p.cantidad] = i;
		flotar(p.arr, p.cantidad);
		return true;
	}
}

bool modificarPrioridad(parva p, char elemento, int nuevaPrioridad){
	int posicion;
	bool exito;

	Localizar(in elemento, out posicion, out exito)
	if(exito){
		int aux = p.arr[posicion].prioridad;
		p.arr[posicion].prioridad = nuevaPrioridad;

		//se esta trabajando una parva de minimo
		if(aux < nuevaPrioridad)
			hundir(p, posicion);
		
		else
			flotar(p, posicion);
		
		return true;
	}
	else
		return false;
}

bool eliminar(parva p){
    if(p.cantidad == 0)
        return false;
    else{
        int aux = p.arr[1];
        p.arr[1] = p.arr[p.cantidad];
        p.cantidad--;
        hundir(p, 1);
        print(aux); //tambien se podria retornar en un puntero
        return true;
    }
}


//AVL

mayorAltura(AVL a){
	nodo aux = a.raiz;
	int altura = 0;
	while(aux != NULL){
		switch(aux){
			case -1: //izquierda
				aux = aux->left;
				altura++;
			break;
			case 0: //balanceado
			//es indiferente
				aux = aux->left;
				altura++;
			case 1: //derecha
				aux = aux->right;
				altura++;
			break;
		}
	}
	return altura;
}


//ABB

void preorden(Nodo nodo){
    if(nodo == NULL)
        return;
    nodo.print();
    preorden(nodo.left);
    preorden(nodo.right);
}

void inorden(Nodo nodo){
    //Imprime arbol de manera creciente
    if(nodo==NULL)
        return;
    inorden(nodo.left);
    nodo.print();
    inorden(nodo.right);
}

void postorden(Nodo nodo){
    if(nodo==NULL)
        return;
    postorden(nodo.left);
    postorden(nodo.right);
    nodo.print();
}

void recorridoNivel(Nodo nodo){
    Queue queue;
    Nodo nodoAux;
    queue.add(nodo);

    while(!queue.isEmpty()){
        nodoAux = queue.poll();
        nodoAux.print();
        
        if(nodoAux.left != NULL)
            queue.add(nodoAux.left);

        if(nodoAux.right != NULL)
            queue.add(nodoAux.right);
    }
}



int getAltura(Nodo nodo){
    if(nodo == NULL)
        return 0;
    else{
        int alturaLeft = getAltura(nodo.left);
        int alturaRight = getAltura(nodo.right);

        if(alturaLeft > alturaRight)
            return alturaLeft + 1;
        else
            return alturaRight + 1;
    }
}


/*Ejercicio 10: Diseñar la funcion: int nodosCaminoMin(a:arbol) que dado un ABB no vacio
determine y devuelva el numero de nodos existentes en el camino mas corto desde la raiz a una hoja.*/

int nodosCaminoMin(Nodo* a) {
    if (a == NULL) {
        return 0;
    }
    if (a->izq == NULL && a->der == NULL) {
        return 1;
    }
    if (a->izq != NULL && a->der == NULL) {
        return 1 + nodosCaminoMin(a->izq);
    }
    if (a->izq == NULL && a->der != NULL) {
        return 1 + nodosCaminoMin(a->der);
    }
    int caminoIzq = nodosCaminoMin(a->izq);
    int caminoDer = nodosCaminoMin(a->der);
    return 1 + (caminoIzq < caminoDer ? caminoIzq : caminoDer);
}

/*Ejercicio 11: Implementar una funci´on booleana que, dados dos arboles binarios con igual
 cantidad y disposicion de nodos; es decir, tienen la misma forma, responda True si el primero
 es menor al segundo y False en otro caso. Diremos que un arbol binario A es menor a otro B,
 si los elementos de A son menores que los de B, en los nodos coincidentes en posicion .*/

typedef struct Nodo {
    int valor;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
} Nodo;

bool esMenor(Nodo *raizA, Nodo *raizB) {
    if (raizA == NULL && raizB == NULL) {
        return true;
    }
    if (raizA == NULL || raizB == NULL) {
        return false;
    }
    if (raizA->valor >= raizB->valor) {
        return false;
    }
    return esMenor(raizA->izquierdo, raizB->izquierdo) && esMenor(raizA->derecho, raizB->derecho);
}

/*Ejercicio 12: Desarrollar en pseudo-codigo un algoritmo que permita calcular el rango de X.*/

double encontrarMin(Nodo* raiz) {
    Nodo* actual = raiz;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual->valor;
}

double encontrarMax(Nodo* raiz) {
    Nodo* actual = raiz;
    while (actual->der != NULL) {
        actual = actual->der;
    }
    return actual->valor;
}

double calcularRango(Nodo* raiz) {
    if (raiz == NULL) {
        printf("El árbol está vacío.\n");
        return 0;
    }
    double min = encontrarMin(raiz);
    double max = encontrarMax(raiz);
    return max - min;
}



/*Ejercicio 13: Desarrollar, en pseudocodigo, una rutina que devuelva los elementos de X almacenados en el 
ABB que caigan en el intervalo [a, b].*/

void obtenerElementosEnIntervalo(Nodo *raiz, int a, int b) {
    NodoPila *pila = NULL;
    Nodo *actual = raiz;
    while (actual != NULL || !esPilaVacia(pila)) {
        while (actual != NULL) {
            push(&pila, actual);
            actual = actual->izquierdo;
        }
        actual = pop(&pila);
        if (actual->valor >= a && actual->valor <= b) {
            printf("%d ", actual->valor);
        }
        if (actual->valor > b) {
            break;
        }
        actual = actual->derecho;
    }
}

/*Ejercicio 14: Dados N elementos de un conjunto almacenado en una LSD, se pide desarrollar un algoritmo que
realice su ordenamiento, de mayor a menor, utilizando como estructura auxiliar un ABB (Treesort).*/

void ordenarLSDConTreesort(NodoLSD* lista, double* arregloOrdenado, int* size) {
    NodoABB* raiz = NULL;
    NodoLSD* actual = lista;
    while (actual != NULL) {
        raiz = insertarABB(raiz, actual->valor);
        actual = actual->siguiente;
    }
    int index = 0;
    recorrerABBInvertido(raiz, arregloOrdenado, &index);
    *size = index;
}

/*Skip list. Localizar*/

struct{
    elemento elem;
    struct NodoSL **next;
}NodoSL

struct{
    int n; /*Nivel*/
    struct NodoSL *cabecera;
}ListaSL

void LocalizarSL(ListaSL *t, NodoSL X[],NodoSL *aux, elemento e, bool exito){
    int i;
    aux=t->cabecera; /*Uso un auxiliar así la cabecera de mi lista no queda en cualquier lado y así poder mantener la estructura desde 0*/
    for (i=t->n;i<=0;i=i-1){
        while (aux->next[i]->elem < e){ /*Iteración dentro de iteración. El for encuentra el nivel más bajo, mientras que el while*/
            aux = aux->next[i]; /*busca el elemento dentro de los punteros más altos, si llegó al elemento no queda sobre el último nodo visitado*/
        }
    X[i] = aux; /*Voy guardando los punteros de los nodos anteriores en un arreglo así para la alta y baja los intercambio.*/
    }
    aux = aux->next[0] /*Acá se para en el nodo que lo supone tener al elemento, ya que mi iteración se para en el último nivel del nodo anterior al buscado*/
    if(aux->elem == e)   /*Si donde está parado, su elemento es igual al buscado true, sino false*/
        exito = true;
    else
        exito = false;
    return exito;
}
/* En resumen, llega busca por toda la estructura y llega hasta el último nivel así guardando los punteros de nivels más altos.
    Una vez llegado al último nivel sigue buscando, una vez ya no puede iterar más en el último nivel de la skip list, sale con el puntero
    apuntando al nodo del que está buscando, por eso el aux = aux->next[o], eso hace que vayas al siguiente nodo con el supuesto elemento
    siendo buscando. Si es, queda parado en ese lugar el puntero y devuelve true, caso contrario false.*/

void AltaSL(ListaSL *t, elemento e, bool exito){
    NodoSL X[t->n+1];
    int i;
    int lvl;
    NodoSL *Y;
    if(LocalizarSL(t,x[],Y,e,exito)){ /*Localiza el nodo, y lo deja apuntando*/
        exito = false;
    }
    else{                             /*Si no lo encuentra procede al alta*/
        while (lvl < t->n && random()>1/2)
            lvl++;
    }
    Y = (NodoSL*)malloc(sizeof(NodoSL));
    Y->elem = e;
    Y->next = (NodoSL **)malloc(sizeof(NodoSL*)*lvl)    /*AL arreglo le da el tamaño del nivel*/
    for(i=0;i<lvl;i++){
        Y->next[i] = X[i]->next[i]; /*Actualiza los punteros de así de los nodos inferiores, hasta el nivel dado y así todo queda apuntado*/
        X[i]->next[i] = Y;
    }
}    