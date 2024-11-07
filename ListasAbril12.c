#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tipoInfo{ int key;
    double value; };
struct tipoNodo{
struct tipoInfo information; 
struct tipoNodo *siguiente; 
struct tipoNodo *anterior;
};
struct listaDoble{
struct tipoNodo *primero;
struct tipoNodo *ultimo; 
};

void vizualizarInfo(struct tipoNodo *primero);
void AddNodo(struct listaDoble *lista);
struct tipoNodo * buscarNodo(struct tipoNodo *primero);
void eliminarNodo(struct listaDoble *lista);
void AddNodoOrdenado(struct listaDoble *lista);
int main(void){
    struct listaDoble lista;
    struct tipoNodo *nodoEncontrado;
    lista.primero = NULL;
    lista.ultimo = NULL;

    int opcion;
       
   
    do
    {
         
        printf("Que opcion quieres: \n");
        printf("1)Visualizar\n");
        printf("2)Anadir al final\n");
        printf("3)Buscar informacion de una ky \n");
        printf("4) Eliminar nodo\n");
        printf("5)add nodo ordenado\n");
        printf("6) Salir \n");
        scanf("%d", &opcion);

        switch (opcion){

            case 1:
                vizualizarInfo(lista.primero);
                break;
            case 2:
                AddNodo(&lista);
                break;
            
            case 3:
            nodoEncontrado = buscarNodo(lista.primero);
            if (nodoEncontrado == NULL)
            {
                printf("informacion no encontrada\n");
                
            }else{
                printf("informacion encontrada de esta key {%d}\n", nodoEncontrado->information.key);
            }
            
                break;
            case 4:
                eliminarNodo(&lista);
            
                break;
            case 5:
                AddNodoOrdenado(&lista);
                break;
        }


    } while (opcion != 6);
   
   

}

void vizualizarInfo(struct tipoNodo *primero){
    struct tipoNodo *recorre = primero;

    while(recorre != NULL){
        printf("Key: {%d}\n", recorre->information.key),
        printf("Value: {%lf}\n\n", recorre->information.value);
        recorre = recorre->siguiente;
        
       
    }
    
}

void AddNodo(struct listaDoble *lista){
    struct tipoNodo *nuevo;

    //1 Reservamos memoria
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo *));
    if (nuevo == NULL)
    {
        printf("ERROR \n");
        return;
    }
    
    //2. rellenamos informacion
    printf("Key: ");
    scanf("%d", &nuevo->information.key);
    printf("Value: ");
    scanf("%lf", &nuevo->information.value);
    //3. unimos a lists
    //4. casos
    //unico y ultimo
    if(lista->primero == NULL){//unico
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }else{//si ya tiene
        nuevo->siguiente = NULL;
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;   
    }


}

struct tipoNodo * buscarNodo(struct tipoNodo *primero){
    struct tipoNodo *recorre = primero;
    int IDkey;
    printf("Que key quieres: ");
    scanf("%d", &IDkey);

    while(recorre != NULL && recorre->information.key != IDkey){
        recorre = recorre->siguiente;
    }
    return recorre;
}

void eliminarNodo(struct listaDoble *lista){
    struct tipoNodo *nodoEliminar;
    

    nodoEliminar = buscarNodo(lista->primero);
    if (nodoEliminar == NULL)
    {
        printf("El nodo no existe");
        return;
    }
    //Casos
    //Unico, primero, ultimo, en medio
    if (nodoEliminar == NULL) // unico
    {
        lista->primero = NULL;
        lista->ultimo = NULL;
    }else if (lista->primero == nodoEliminar){//primero
        lista->primero->anterior = NULL;
        lista->primero = lista->primero->siguiente;
    }else if(lista->ultimo == nodoEliminar){//ultimo
        lista->ultimo->siguiente = NULL;
        lista->ultimo = lista->ultimo->anterior;
    }else{// en medio
        nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
        nodoEliminar ->anterior->siguiente = nodoEliminar->siguiente;

    }
    
    free(nodoEliminar);
    

}
void AddNodoOrdenado(struct listaDoble *lista){
    struct tipoNodo *nuevo;
    struct tipoNodo *recorre = lista->primero;
    

    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo *));
    if (nuevo == NULL)
    {
        printf("ERROR \n");
        return;
    }
    printf("Key: ");
    scanf("%d", &nuevo->information.key);
    printf("Value: ");
    scanf("%lf", &nuevo->information.value);
    
    
  


    
    //conectamos a lista
    while (recorre != NULL &&  (recorre->information.key < nuevo->information.key))
    {
        recorre = recorre->siguiente;
    }//recorre se queda apuntando al siguiente al nuevo si no esta y al de esa clave si esta

    if ((recorre != NULL)&& (recorre ->information.key == nuevo->information.key))
    {
        printf("Key REPETIDA\n");
        free(nuevo);
        return;
    }
    //conectamos casos

    if(lista->primero == NULL){//lista vacia
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }else if(recorre == NULL){//ultimo
        nuevo->siguiente = NULL;
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;

    }else if(recorre->anterior == NULL){// inserto al principio
        nuevo->siguiente = lista->primero;
        nuevo->anterior = NULL;
        lista->primero->anterior = nuevo;
        lista->primero = nuevo;
    }else{// en medio
        nuevo->siguiente = recorre;
        nuevo->anterior = recorre->anterior;
        recorre->anterior = nuevo;
        recorre->anterior->siguiente = nuevo;
    }

}