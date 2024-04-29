#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona {
    int dni[20];
    char nombre[50];
    char apellido[50];
};

int i;

int compararPorNombre(const void *a, const void *b);

int compararPorDNI(const void *a, const void *b);

void mostrarDatosOrdenados(FILE *archivo, int orden);

void ingresarDatos(FILE *archivo);

void buscarPorDni(FILE *archivo);

void buscarPorNombreApellido(FILE *archivo);



int main() {
    FILE *archivo;
    int opcion;


    archivo = fopen("datos4.txt", "w+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Busqueda por Nombre y Apellido\n");
        printf("4. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatos(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                buscarPorNombreApellido(archivo);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 4);


    fclose(archivo);

    return 0;
}




void ingresarDatos(FILE *archivo) {
    struct Persona persona;
    char dniBuscar[20];

    printf("Ingrese el DNI: ");
    scanf("%s", dniBuscar);

    // Reinicia el puntero de archivo al principio
    rewind(archivo);

  
    while (fscanf(archivo, "%s %s %s", persona.nombre, persona.apellido, persona.dni) != EOF) {
        if (strcmp(persona.dni, dniBuscar) == 0) {
            printf("El DNI ingresado ya existe en el archivo. No se pueden ingresar datos duplicados.\n");
            return;
        }
    }

    // Si el DNI no existe, permite ingresar los datos
    strcpy(persona.dni, dniBuscar);

    printf("Ingrese el nombre: ");
    scanf("%s", persona.nombre);
    printf("Ingrese el apellido: ");
    scanf("%s", persona.apellido);

    // Escribe los datos en el archivo
    fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
    printf("Datos guardados correctamente.\n");
}



void buscarPorDNI(FILE *archivo) {
    char dniBuscar[20];
    char nombre[50], apellido[50], dni[20];
    int encontrado = 0;

    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dniBuscar);

    // Reinicia el puntero de archivo al principio
    rewind(archivo);

   
    while (fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF) {
        if (strcmp(dni, dniBuscar) == 0) {
            printf("Nombre: %s\n", nombre);
            printf("Apellido: %s\n", apellido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el DNI ingresado.\n");
    }
}


void buscarPorNombreApellido(FILE *archivo) {
    char nombreBuscar[50];
    char apellidoBuscar[50];
    char nombre[50], apellido[50], dni[20];
    int encontrado = 0;

    printf("Ingrese el nombre a buscar: ");
    scanf("%s", nombreBuscar);
    printf("Ingrese el apellido a buscar: ");
    scanf("%s", apellidoBuscar);


    rewind(archivo);

   
    while (fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF) {
        if (strcmp(nombre, nombreBuscar) == 0 && strcmp(apellido, apellidoBuscar) == 0) {
            printf("DNI: %s\n", dni);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el nombre y apellido ingresados.\n");
    }
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

	
void mostrarDatosOrdenados(FILE *archivo, int orden) {
    struct Persona personas[100]; // Suponemos un máximo de 100 personas
    int numPersonas = 0;

    rewind(archivo);

    while (fscanf(archivo, "%s %s %s", personas[numPersonas].nombre, personas[numPersonas].apellido, personas[numPersonas].dni) != EOF) {
        numPersonas++;
    }

    if (orden == 1) {
        qsort(personas, numPersonas, sizeof(struct Persona), compararPorNombre);
    } else {
        qsort(personas, numPersonas, sizeof(struct Persona), compararPorDNI);
    }

    printf("Nombre\tApellido\tDNI\n");
    for (i = 0; i < numPersonas; i++) {
        printf("%s\t%s\t%s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}





