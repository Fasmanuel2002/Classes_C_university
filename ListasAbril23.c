#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct usuario{
    int ID;
    int premium;
    char consulta[40];
};

struct tipoNodo{
    struct usuario information;
    struct tipoNodo *siguiente;
    struct tipoNodo *anterior;
};

struct listaDoble{
    struct tipoNodo *primero;
    struct tipoNodo *ultimo;
};


struct tipoNodo * BuscarPersona(struct tipoNodo *primero, int IDBuscar);
void AddCliente(struct listaDoble *);
int contadorConsultas(struct tipoNodo *primero);
void EliminarCliente(struct listaDoble *);
void EliminarPremium(struct listaDoble *);
struct tipoNodo *BuscarPremium(struct tipoNodo *primero);
void eliminarPersona(struct listaDoble *lista);
int main(void){
    struct listaDoble lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    int opcion;
       
   
    do
    {
         
        printf("Que opcion quieres: \n");
        printf("1)Añadir un usuario a la consulta\n");
        printf("2)Eliminar Cliente normal\n");
        printf("3)Eliminar Cliente Preimum \n");
        printf("4) Abandonar lista\n");
        printf("5)Salir \n");
        scanf("%d", &opcion);

        switch (opcion){

            case 1:
            AddCliente(&lista);
                break;
            case 2:
            EliminarCliente(&lista);
                break;
            
            case 3:
            EliminarPremium(&lista);
                break;
            case 4:
            eliminarPersona(&lista);
                break;
        }


    } while (opcion != 5);
   
   
}


struct tipoNodo * BuscarPersona(struct tipoNodo *primero, int IDBuscar){
    struct tipoNodo *recorre = primero;

    while (recorre != NULL && recorre->information.ID != IDBuscar)
    {
        recorre = recorre->siguiente;
    }
    return recorre;
    
}

int contadorConsultas(struct tipoNodo *primero){
    struct tipoNodo *recorre = primero;
    int contador = 0;
    while (recorre != NULL)
    {
       contador++;
       recorre = recorre->siguiente; 
    }
    return contador;
}

//1. Anadir Persona
//CrearCliente -> tenemos que crear 
//Tenemos que buscar que no haya nadie en la cola
//lo anadiremos al final

void AddCliente(struct listaDoble *lista){
    struct tipoNodo *nuevo;
    struct tipoNodo *UsuarioExistente;
    int IDBusqueda;
    int contador;
    //1 reservamos memoria
    nuevo = (struct tipoNodo *) malloc(sizeof(struct tipoNodo));
    //2 buscamos que no exista
    printf("Usuario: ");
    scanf("%d", &IDBusqueda);

    UsuarioExistente = BuscarPersona(lista->primero, IDBusqueda);
    if (UsuarioExistente != NULL)
    {
        printf("Usuario Existe\n");
        return;
    }
    
    //3 rellenamos informacion
    nuevo->information.ID = IDBusqueda;

    printf("Premium (0/1): ");
    scanf("%d", &nuevo->information.premium);
    printf("Por que la consulta: ");
    scanf("%s", nuevo->information.consulta);




    

    //4 Conectamos a la lista al final de la lista

    if (lista->ultimo == NULL) // la lista esta vacia
    {
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }else{//la lista tiene personas
        nuevo->siguiente = NULL;
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;

    }
    
    contador = contadorConsultas(lista->primero);

    printf("Bienvenido a nuestro servicio de atencion al cliente publico, trabajamos para atenderte lo más rapido posible, te encuentras en la posicion %d \n", contador); 

}

//2 Atender al cliente
//Debemos borrar al cliente
//y eliminarlo

void EliminarCliente(struct listaDoble *lista){
    struct tipoNodo *borrar;
    int IDborrado;
    
    borrar = lista->primero;
    IDborrado = borrar->information.ID;
    //Casos
    //1. Unico //2. si hay algo más

    if (lista->primero == lista->ultimo)//unico
    {
        lista->primero = NULL;
        lista->ultimo = NULL;
    }else{
        lista->primero = lista->primero->siguiente;
        lista->primero->anterior = NULL;
    }
    printf("El usuario %d ha sido eliminado correctamente \n" , IDborrado);
}

void EliminarPremium(struct listaDoble *lista){
    struct tipoNodo *borrar;
    struct tipoNodo *personaPremiumE;
    int IDborrado;
    
    

    

    personaPremiumE = BuscarPremium(lista->primero);
    if (personaPremiumE == NULL)
    {
        printf("No hay personas premium");
        return;
    }
    IDborrado = personaPremiumE->information.ID;
    //casos de borrado 
    //1 Unico
    //2 Ultimo
    //3 primero
    //4 en medio
    if(lista->ultimo == lista->primero){//unico
        lista->primero = NULL;
        lista->ultimo = NULL;
    }else if(lista->primero == personaPremiumE){//primero
        lista->primero = lista->primero->siguiente;
        lista->primero->anterior = NULL;


    }else if(lista->ultimo == personaPremiumE)//ultimo
    {
        lista->ultimo = lista->ultimo->anterior;
        lista->ultimo->siguiente = NULL;
    }else{//en medio
        personaPremiumE->anterior->siguiente = personaPremiumE->siguiente;
        personaPremiumE->siguiente->anterior = personaPremiumE->anterior;
    }

    printf("El usuario %d ha sido eliminado correctamente \n" , IDborrado);

    
    
    
}

struct tipoNodo *BuscarPremium(struct tipoNodo *primero){
    struct tipoNodo *recorre = primero;

    while (recorre != NULL )
    {
        if (recorre->information.premium == 1)
        {
            printf("Si hay personas");
            return recorre;
        }
        recorre = recorre->siguiente;
    }
    return NULL;
    

}

//Eliminar persona
//debemos buscar a la persona buscarPersona()
//eliminarlo

void eliminarPersona(struct listaDoble *lista){
    struct tipoNodo *personaEliminar;
    int idPersonaEliminadas;
    int  IDbuscar;
    printf("Que persona quiere abandonar la lista");
    scanf("%d", &IDbuscar);

    personaEliminar = BuscarPersona(lista->primero, IDbuscar);
    if (personaEliminar == NULL)
    {
        printf("La persona que buscas no existe \n");
        return;
    }
    idPersonaEliminadas = personaEliminar->information.ID;

    //casos de la persona
    
    //1. unico
    //2. ultimo
    //3. primero
    //4. en medio

    if (lista->primero == lista->ultimo)//unico
    {
        lista->primero = NULL;
        lista->ultimo = NULL;
    }else if(lista->ultimo == personaEliminar)//ultimo
    {
        lista->ultimo = lista->ultimo->anterior;
        lista->ultimo->siguiente = NULL;
    }else if(lista->primero == personaEliminar){//primero
        lista->primero = lista->primero->siguiente;
        lista->primero->anterior = NULL;
    }else{
        personaEliminar->anterior->siguiente = personaEliminar->siguiente;
        personaEliminar->siguiente->anterior = personaEliminar ->anterior;
    }
    printf("Sentimos no haberle podido antender cliente: %d \n", idPersonaEliminadas);
}