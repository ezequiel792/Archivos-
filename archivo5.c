#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona {
    char nombre[50];
    char apellido[50];
    char dni[20];
};

int i;

int compararPorNombre(const void *a, const void *b);
int compararPorDNI(const void *a, const void *b);
void mostrarDatosOrdenados(struct Persona personas[], int numPersonas);
void guardarCambios(struct Persona personas[], int numPersonas, const char *nombreArchivo);

int main() {
    FILE *archivoOriginal;
    int opcion;
    struct Persona *personas = NULL;
    int numPersonas = 0;
    int capacidad = 10; // Inicializar la capacidad

    archivoOriginal = fopen("datos5.txt", "r");
    if (archivoOriginal == NULL) {
        printf("Error al abrir el archivo original.\n");
        return 1;
    }

    personas = malloc(capacidad * sizeof(struct Persona)); // Asignar memoria inicial
    if (personas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Leer datos del archivo original y almacenarlos en memoria dinámica
    while (fscanf(archivoOriginal, "%s %s %s", personas[numPersonas].nombre, personas[numPersonas].apellido, personas[numPersonas].dni) != EOF) {
        numPersonas++;
        // Si se alcanza la capacidad actual, aumentar la capacidad
        if (numPersonas >= capacidad) {
            capacidad += 10; // Incrementar la capacidad en bloques de 10 personas
            personas = realloc(personas, capacidad * sizeof(struct Persona));
            if (personas == NULL) {
                printf("Error al asignar memoria.\n");
                return 1;
            }
        }
    }
    fclose(archivoOriginal);

    do {
        printf("\nMenu:\n");
        printf("1. Mostrar datos ordenados por nombre y apellido\n");
        printf("2. Mostrar datos ordenados por DNI\n");
        printf("3. Guardar cambios en un nuevo archivo\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                qsort(personas, numPersonas, sizeof(struct Persona), compararPorNombre);
                mostrarDatosOrdenados(personas, numPersonas);
                break;
            case 2:
                qsort(personas, numPersonas, sizeof(struct Persona), compararPorDNI);
                mostrarDatosOrdenados(personas, numPersonas);
                break;
            case 3:
                guardarCambios(personas, numPersonas, "datos_nuevos.txt");
                printf("Cambios guardados en un nuevo archivo 'datos_nuevos.txt'.\n");
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    // Liberar memoria antes de salir del programa
    free(personas);

    return 0;
}

int compararPorNombre(const void *a, const void *b) {
    const struct Persona *personaA = (const struct Persona *)a;
    const struct Persona *personaB = (const struct Persona *)b;
    int cmp = strcmp(personaA->nombre, personaB->nombre);
    if (cmp == 0) {
        return strcmp(personaA->apellido, personaB->apellido);
    }
    return cmp;
}

int compararPorDNI(const void *a, const void *b) {
    const struct Persona *personaA = (const struct Persona *)a;
    const struct Persona *personaB = (const struct Persona *)b;
    return strcmp(personaA->dni, personaB->dni);
}

void mostrarDatosOrdenados(struct Persona personas[], int numPersonas) {
    printf("Nombre\tApellido\tDNI\n");
    for (i = 0; i < numPersonas; i++) {
        printf("%s\t%s\t%s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}

void guardarCambios(struct Persona personas[], int numPersonas, const char *nombreArchivo) {
    FILE *archivoNuevo = fopen(nombreArchivo, "w");
    if (archivoNuevo == NULL) {
        printf("Error al crear el archivo nuevo.\n");
        return;
    }

    for (i = 0; i < numPersonas; i++) {
        fprintf(archivoNuevo, "%s %s %s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }

    fclose(archivoNuevo);
}

