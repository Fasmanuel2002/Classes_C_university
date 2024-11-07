#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fecha{
    int dia,mes,anno;
};

struct tipoInfo{
    char ID[20];
    char producto[20];
    int unidades;
    struct fecha f;
};
struct tipoNodo{
struct tipoInfo information;
struct tipoNodo *siguiente;
struct tipoNodo *anterior;
};
struct listaDoble{
struct tipoNodo *primero;
struct tipoNodo *ultimo;
};

void anadirCompra(struct listaDoble *);
void visualizarComprasUltimo(struct tipoNodo *ultimo, char buscarUsuario[20]);
void visualizarComprasDeUsuario(struct tipoNodo *ultimo, char buscarUsuario[20]);
void anadirCompraOrdenaFecha(struct listaDoble *);
int main(void){

    struct listaDoble lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    char buscarUsuario[20];

    int opcion;

    do {
        // Mostrar el menú
        printf("=== Menú ===\n");
        printf("1. anadir compra 1\n");
        printf("2. Mostrar la ultima compra del usuario\n");
        printf("3. todas las compras de un usuario 3\n");
        printf("4. Opción 4\n");
        printf("0. Salir\n");
        printf("============\n");
        printf("Seleccione una opción: ");
        
        // Leer la opción del usuario
        scanf("%d", &opcion);

        // Procesar la opción seleccionada
        switch(opcion) {
            case 1:
                printf("anadir compra\n");
                anadirCompra(&lista);
                break;
            case 2:
                printf("Opción 2.\n");
                printf("Que usuario quieres: ");
                scanf("%s", buscarUsuario);
                visualizarComprasUltimo(lista.ultimo, buscarUsuario);
                break;
            case 3:
                printf("Opción 3.\n");
                printf("Que usuario quieres: ");
                scanf("%s", buscarUsuario);
                visualizarComprasDeUsuario(lista.ultimo, buscarUsuario);
                break;
            case 4:
                printf("Ha seleccionado la Opción 4.\n");
                break;
            case 0:
                printf("Saliendo del menú...\n");
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
        }
    } while (opcion != 0);



    return 0;
}

//Añadir compra; debemos añadir al usuario, el cidgo, numero de unidades y compra
void anadirCompra(struct listaDoble *lista){
    struct tipoNodo *nuevo;
    //1. reservar memoria 
    nuevo = (struct tipoNodo *) malloc(sizeof(struct tipoNodo*));
    if (nuevo == NULL)
    {
        printf("No hay Memoria");
        return;
    }
    
    //2.  relleno informacion
    printf("Id del usuario: ");
    scanf("%s", nuevo->information.ID);
    printf("Codigo del producto: ");
    scanf("%s", nuevo->information.producto);
    printf("Numero de unidades: ");
    scanf("%d", &nuevo->information.unidades);
    printf("fecha: dia: ");
    scanf("%d", &nuevo->information.f.dia);
    printf("fecha: mes: ");
    scanf("%d", &nuevo->information.f.mes);
    printf("fecha: anno: ");
    scanf("%d", &nuevo->information.f.anno);
    //3. conecto con la lista
    if (lista->primero == NULL)//Esta vacio
    {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }else{// hay personas
        //voy a insertar por el final
        nuevo->siguiente = NULL;//el nuevo no apunta a a ningun lugar
        nuevo->anterior = lista->ultimo;// el nuevo apunta al anterior
        lista->ultimo->siguiente = nuevo;//Hagp que el ultimo apunte al nuevo
        lista->ultimo = nuevo;//el ultimo apunta al nuevo
    }
    
    
    
}

//Se introducira el identificador del usuario
// y se mostara toda la informacion de la ultima entrada que ha realizado el usuarios
void visualizarComprasUltimo(struct tipoNodo *ultimo, char buscarUsuario[20]){
    struct tipoNodo *recorre = ultimo;


    while (recorre != NULL && (strcmp(recorre->information.ID, buscarUsuario)!=0))
    {
        recorre->anterior = recorre;
    }
    if (recorre != NULL)
    {
        
        printf("ID: %s\n", recorre->information.ID);
        printf("Codigo del producto: %s\n", recorre->information.producto);
        printf("Unidades: %d\n", recorre->information.unidades);
        printf("Dia/mes/anno: %d/%d/%d \n", recorre->information.f.dia,recorre->information.f.mes, recorre->information.f.anno);
    }else{
        printf("El usuario con este id: %s no ha realizado ninguna compra", buscarUsuario);
    }
    
}

void visualizarComprasDeUsuario(struct tipoNodo *ultimo, char buscarUsuario[20]){
    struct tipoNodo *recorre = ultimo;
    if (ultimo == NULL)
    {
        printf("Usuario no existe");
        return;
    }
    

    while (recorre != NULL)
    {
        if (strcmp(recorre->information.ID, buscarUsuario)==0)
        {
            printf("ID: %s\n", recorre->information.ID);
            printf("Codigo del producto: %s\n", recorre->information.producto);
            printf("Unidades: %d\n", recorre->information.unidades);
            printf("Dia/mes/anno: %d/%d/%d \n", recorre->information.f.dia,recorre->information.f.mes, recorre->information.f.anno);
        }
        recorre = recorre->anterior; 
    }
    
    
}
void anadirCompraOrdenaFecha(struct listaDoble *lista){
    struct tipoNodo *nuevo;
    struct tipoNodo *recorre = lista->primero;
    //1. Reservo memoria
    nuevo = (struct tipoNodo *) malloc(sizeof(struct tipoNodo *));
    if (nuevo == NULL)
    {
        printf("Error\n");
        return;
    }
    

    //2. relleno memoria
    printf("Id del usuario: ");
    scanf("%s", nuevo->information.ID);
    printf("Codigo del producto: ");
    scanf("%s", nuevo->information.producto);
    printf("Numero de unidades: ");
    scanf("%d", &nuevo->information.unidades);
    printf("fecha: dia: ");
    scanf("%d", &nuevo->information.f.dia);
    printf("fecha: mes: ");
    scanf("%d", &nuevo->information.f.mes);
    printf("fecha: anno: ");
    scanf("%d", &nuevo->information.f.anno);
    //3.Conecto con la lista
    while (recorre != NULL && recorre->information.f.anno < nuevo->information.f.anno )
    {
        recorre = recorre->siguiente;
    }
    while (recorre != NULL && (recorre->information.f.mes < nuevo->information.f.mes) && (recorre->information.f.anno == nuevo->information.f.anno ))
    {
        recorre = recorre->siguiente;
    }
    while (recorre != NULL && (recorre->information.f.dia < nuevo->information.f.dia) && (recorre->information.f.mes == nuevo->information.f.mes) && (recorre->information.f.anno == nuevo->information.f.anno ))
    {
        recorre = recorre->siguiente;
    }
    
    

    //4. casos

    // 1. UNICO, 2. en el principio 3en el final 4 en el medio
    if (lista->primero == NULL) // unico
    {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }
    else if(lista->ultimo == NULL){ // final

        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;


    }else if(recorre->anterior == NULL){ // principio
        nuevo->anterior = NULL;
        nuevo->siguiente = lista->primero;
        lista->primero->anterior = nuevo;
        lista->primero = nuevo;
    }else{ // en medio
        nuevo->siguiente = recorre;
        nuevo->anterior = recorre->anterior;
        recorre->anterior = nuevo;
        recorre->anterior->siguiente = nuevo;
    }
    
}