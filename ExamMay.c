#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct infoAsig{
    char asignatura[20];
    float nota;
    int convocatoria;

};

struct nodoAsig{
    struct infoAsig AsignaturaINF;
    struct nodoAsig *siguiente;
    struct nodoAsig *anterior;

};

struct listaAsignaturas{
    struct nodoAsig *primero;
    struct nodoAsig *ultimo;

};

struct infoAl{
    char ID[6];
    char nombre[20];
    char titulacion[10];
};

struct nodoAlumno{
    struct infoAl infoAlum;
    struct listaAsignaturas asignaturas;
    struct nodoAlumno *siguiente;
    struct nodoAlumno *anterior;

};
struct listaAlumnos{
    struct nodoAlumno *primero;
    struct nodoAlumno *ultimo; 
};
void crearListasDeListas(struct listaAlumnos *listaAlum);
void crearAlumnos(struct listaAlumnos *lista);
struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char Exp[6]);
void visualizarAlumnos(struct nodoAlumno *primero);

void crearAsignatura(struct nodoAlumno *alumno);
void visualizar(struct nodoAsig *primero);
float notaMediaExpediente(struct listaAlumnos *lista);
int main(void){
    struct listaAlumnos alumnos;
    int opcion;
    char ID[6];
    float mediatotal;
    crearListasDeListas(&alumnos);
   do {
        printf("Opciones \n");
        printf("1. añadir alumno\n");
        printf("2. añadir nota alumno\n");
        printf("3. Mostrar nota media\n");
        printf("4. Eliminar nota asignatura\n");
        printf("7. Ver alumnos\n");
        printf("8. Ver asignaturas del primer alumno\n");
        printf("5. Salir\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearAlumnos(&alumnos);
                break;
            case 2:
                
                
                printf("Ingrese el ID del alumno: ");
                scanf("%s", ID);
                struct nodoAlumno *alumno = buscarAlumno(alumnos.primero, ID);
                if (alumno == NULL) {
                    printf("No se encontró ningún alumno con ese ID.\n");
                } else {
                    crearAsignatura(alumno);
                }
                
                break;
            case 3:
               printf("La nota media del expediente es: %f\n", notaMediaExpediente(&alumnos));
                break;
            case 7:
                visualizarAlumnos(alumnos.primero);
                break;
            case 8:
                visualizar(alumnos.primero->asignaturas.primero);
                break;
            default:
                break;
        }
    } while (opcion != 5);

    return 0;
    


}
void crearListasDeListas(struct listaAlumnos *listaAlum){
   

    //inicializo la lista
    listaAlum->primero = listaAlum->ultimo = NULL; // inicializo la lista
    
        
    
    

}
void crearAlumnos(struct listaAlumnos *lista){
    struct nodoAlumno *nuevo;
    struct nodoAlumno *buscadoAlumno;
    char IDbuscar[6];
    int numeroAsig;

    nuevo = (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno ));
    if (nuevo == NULL)
    {
        printf("Errorn\n");
        return;
    }
    

    printf("Expediente del alumno: ");
    scanf("%s", IDbuscar);
    
    buscadoAlumno = buscarAlumno(lista->primero, IDbuscar);
    if (buscadoAlumno != NULL)
    {
        printf("ERROR Ya existe un alumno con este ID %s\n", IDbuscar);
        return;
    }
    

    
    strcpy(nuevo->infoAlum.ID, IDbuscar);
    printf("Nombre: ");
    scanf("%s", nuevo->infoAlum.nombre);
    printf("titulacion: ");
    scanf("%s", nuevo->infoAlum.titulacion);

    nuevo->asignaturas.primero = NULL;
    nuevo->asignaturas.ultimo = NULL;
    

    


    if(lista->ultimo == NULL) //unico
    {
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }else{// solo
        nuevo->siguiente = NULL;
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    }
    
    
}

struct nodoAlumno * buscarAlumno(struct nodoAlumno *primero, char Exp[6]){
    struct nodoAlumno *recorre = primero;

    while (recorre != NULL )
    {
        if ((strcmp(recorre->infoAlum.ID, Exp)==0))
        {
            return recorre;
        }
        
        recorre = recorre->siguiente;
    }
    return NULL;
    
}
void visualizarAlumnos(struct nodoAlumno *primero){
     struct nodoAlumno *recorre = primero;

    while (recorre != NULL)
    {
        printf("%s\n" ,recorre->infoAlum.ID);
        printf("%s\n" ,recorre->infoAlum.nombre);
        printf("%s\n" ,recorre->infoAlum.titulacion);
        printf("%s \n", recorre->asignaturas.primero->AsignaturaINF.asignatura);
        recorre = recorre->siguiente;
    }
    
    
}

// buscarAlumno
//buscarAsignatura
//anadir, y convocatoria se le debe añadir uno
void crearAsignatura(struct nodoAlumno *alumno){
    struct nodoAsig *nuevaAsignatura;
    
    char IDbuscar[6];
    
  

    nuevaAsignatura = (struct nodoAsig *)malloc(sizeof(struct nodoAsig));
    
   

    printf("Nombre de la asignatura: ");
    scanf("%s", nuevaAsignatura->AsignaturaINF.asignatura);
    printf("nota del alumno: ");
    scanf("%f", &nuevaAsignatura->AsignaturaINF.nota);
    
    if (nuevaAsignatura->AsignaturaINF.nota > 5)
    {
        printf("APROBADA\n");
    }else{
        nuevaAsignatura->AsignaturaINF.convocatoria += 1;
    }

     if (alumno->asignaturas.primero == NULL) {
        nuevaAsignatura->anterior = NULL;
        nuevaAsignatura->siguiente = NULL;
        alumno->asignaturas.primero = nuevaAsignatura;
        alumno->asignaturas.ultimo = nuevaAsignatura;
    } else {
        // Conectar la nueva asignatura al final de la lista
        nuevaAsignatura->anterior = alumno->asignaturas.ultimo;
        nuevaAsignatura->siguiente = NULL;
        alumno->asignaturas.ultimo->siguiente = nuevaAsignatura;
        alumno->asignaturas.ultimo = nuevaAsignatura;
    }
}

    
    
    
    




void visualizar(struct nodoAsig *primero){
     struct nodoAsig *recorre = primero;

    while (recorre != NULL)
    {
        printf("%s\n" ,recorre->AsignaturaINF.asignatura);
        printf("%d\n" ,recorre->AsignaturaINF.convocatoria);
        printf("%f\n" ,recorre->AsignaturaINF.nota);
        recorre = recorre->siguiente;
    }

}

float notaMediaExpediente(struct listaAlumnos *lista) {
    struct nodoAlumno *alumno = lista->primero;
    int totalAsignaturasAprobadas = 0;
    float sumaNotasAprobadas = 0.0;

    while (alumno != NULL) {
        struct nodoAsig *asignatura = alumno->asignaturas.primero;
        while (asignatura != NULL) {
            if (asignatura->AsignaturaINF.nota >= 5) {
                totalAsignaturasAprobadas++;
                sumaNotasAprobadas += asignatura->AsignaturaINF.nota;
            }
            asignatura = asignatura->siguiente;
        }
        alumno = alumno->siguiente;
    }

    if (totalAsignaturasAprobadas > 0) {
        return sumaNotasAprobadas / totalAsignaturasAprobadas;
    } else {
        return 0.0; // No hay asignaturas aprobadas, por lo que la nota media es 0
    }
}

