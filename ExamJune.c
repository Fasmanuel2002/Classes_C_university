#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct infoMensaje{
    char NickEmisor[10];
    char NickReceptor[10];
    char texto[50];
};

struct nodoMensaje{
    struct infoMensaje infoM;
    struct nodoMensaje *siguiente;
    struct nodoMensaje *anterior;
};

struct listaMensajes{
    struct nodoMensaje *primero;
    struct nodoMensaje *ultimo; 
};

struct infoUsuario{
    char Tel[10];
    char nick[10];
};

struct nodoUsuario{
    struct infoUsuario infoU;
    struct nodoUsuario *siguiente;
    struct nodoUsuario *anterior;
    struct listaMensajes mensajes;
};

struct listaUsuarios{
    struct nodoUsuario *primero;
    struct nodoUsuario *ultimo;
};


void crearUsuario(struct listaUsuarios *lista);
struct nodoUsuario * buscarUsuario(struct nodoUsuario *primero, char comprobacionNick[10]);
void verUsuarios(struct nodoUsuario *primero);
void crearMensaje(struct listaUsuarios *lista);
int contarMensajes(struct nodoUsuario *primero);
void verMensajes(struct listaMensajes *listaMensaje);
int main(void){
    struct listaUsuarios lista;
    lista.primero = lista.ultimo = NULL;
    int opcion;
    

    do
  
    {
        
        printf("1 add usuario\n");
        printf("8 ver usuario\n");
        printf("Opcion: \n");
        scanf("%d", &opcion);
        
        switch (opcion)
        {
        case 1:
            crearUsuario(&lista);
            break;
        case 2:
            crearMensaje(&lista);
            break;
        case 7:
            verMensajes(&lista.primero->mensajes.primero);
            break;
        case 8:
            verUsuarios(lista.primero);
            break;
        default:
            break;
        }
    } while (opcion != 5);
    

}

struct nodoUsuario * buscarUsuario(struct nodoUsuario *primero, char comprobacionNick[10]){
    struct nodoUsuario *recorre = primero;

    while (recorre != NULL)
    {
        if (strcmp(recorre->infoU.nick, comprobacionNick)==0)
        {
            return recorre;
        }
        recorre = recorre->siguiente;
    }
    return NULL;
    
}
void crearUsuario(struct listaUsuarios *lista){
    struct nodoUsuario *nuevoU;
    struct nodoUsuario *comprobacion;
    char comprobacionNick[10];
    //reservo memoria
    nuevoU = (struct nodoUsuario *)malloc(sizeof(struct nodoUsuario));

    //relleno info
    printf("Nick del Usuario: ");
    scanf("%s", comprobacionNick);
    
    comprobacion = buscarUsuario(lista->primero, comprobacionNick);
    if (comprobacion != NULL)
    {
        printf("Nick Existe \n");
        return;
    }
    
    
    strcpy(nuevoU->infoU.nick, comprobacionNick);
    printf("Tel: ");
    scanf("%s", nuevoU->infoU.Tel);
    //casos (unico), ultimo
    if (lista->ultimo == NULL)
    {
        nuevoU->siguiente = NULL;
        nuevoU->anterior = NULL;
        lista->primero = nuevoU;
        lista->ultimo = nuevoU;

    }else{// existen
        nuevoU->siguiente = NULL;
        nuevoU->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevoU;
        lista->ultimo = nuevoU; 
    }
    
}
void verUsuarios(struct nodoUsuario *primero){
    struct nodoUsuario *recorre = primero;

    while (recorre != NULL)
    {
        printf("Nick: %s \n", recorre->infoU.nick);
        printf("Tel: %s \n\n\n", recorre->infoU.Tel);
        recorre = recorre->siguiente;
    }
    
}

void crearMensaje(struct listaUsuarios *lista){
    struct nodoMensaje *nuevoM;
    struct nodoUsuario *ComprobanteE;
    struct nodoUsuario *ComprobanteR;
    char comprobanteEm[10];
    char comprobanteRe[10];
    //reservamos memoria
    nuevoM = (struct nodoMensaje *)malloc(sizeof(struct nodoMensaje));
    printf("Nick del Emisor");
    scanf("%s", comprobanteEm);
    printf("Nick del Emisor");
    scanf("%s", comprobanteRe);

    ComprobanteE = buscarUsuario(lista->primero, comprobanteEm);
    if (ComprobanteE == NULL)
    {
        printf("No exite Usuario Emisor \n");
        return;
    }
    ComprobanteR = buscarUsuario(lista->primero, comprobanteRe);
     if (ComprobanteR == NULL)
    {
        printf("No exite Usuario Receptor \n");
        return;
    };
    strcpy(nuevoM->infoM.NickEmisor, comprobanteEm);
    strcpy(nuevoM->infoM.NickReceptor, comprobanteRe);
    printf("Mensaje del emisor al receptor: ");
    scanf("%s", nuevoM->infoM.texto);
    
    if (ComprobanteE->mensajes.ultimo == NULL)//listaVacia
    {   
        nuevoM->siguiente = NULL;
        nuevoM->anterior = NULL;
        ComprobanteE->mensajes.primero = nuevoM;
        ComprobanteE->mensajes.ultimo = nuevoM;
        
    }else{//si existen
        nuevoM->siguiente = NULL;
        nuevoM->anterior = ComprobanteE->mensajes.ultimo;
        ComprobanteE->mensajes.ultimo->siguiente = nuevoM;
        ComprobanteE->mensajes.ultimo = nuevoM;
    }
    
}

void verMensajes(struct listaMensajes *listaMensaje){
    struct nodoMensaje *recorre = listaMensaje->primero;

    while (recorre != NULL)
    {

        printf("Nick emisor: %s\n", recorre->infoM.NickEmisor);
        printf("Nick receptor:%s\n", recorre->infoM.NickReceptor);
        printf("Mensaje: %s \n", recorre->infoM.texto);
        recorre = recorre->siguiente;
    }
    
}
int contarMensajes(struct nodoUsuario *primero){
    return 0;
}