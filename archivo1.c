#include <stdio.h>

// Función para verificar si un DNI ya está registrado en el archivo
int dniRegistrado(FILE *archivo, int dni) {
    rewind(archivo); // Reiniciar el puntero de archivo al principio
    
    int dniLeido;
    char nombre[50];
    char apellido[50];
    
    while (fscanf(archivo, "%s %s %d", nombre, apellido, &dniLeido) != EOF) {
        if (dniLeido == dni) {
            return 1; // El DNI está registrado
        }
    }
    
    return 0; // El DNI no está registrado
}

// Función para ingresar los datos de una persona y guardarlos en el archivo
void ingresarDatos(FILE *archivo) {
    char nombre[50];
    char apellido[50];
    int dni;
    
    printf("Ingrese nombre: ");
    scanf("%s", nombre);
    
    printf("Ingrese apellido: ");
    scanf("%s", apellido);
    
    do {
        printf("Ingrese DNI: ");
        scanf("%d", &dni);
        
        if (dniRegistrado(archivo, dni)) {
            printf("El DNI ya esta registrado. Ingrese otro DNI.\n");
        }
    } while (dniRegistrado(archivo, dni)); // Repetir hasta que se ingrese un DNI no registrado
    
    fprintf(archivo, "%s %s %d\n", nombre, apellido, dni);
    
    printf("Datos guardados correctamente.\n");
}

// Función para buscar y mostrar los datos de una persona por DNI
void buscarPorDNI(FILE *archivo) {
    int dniBuscado;
    char nombre[50];
    char apellido[50];
    int dni;
    int encontrado = 0;
    
    printf("Ingrese el DNI a buscar: ");
    scanf("%d", &dniBuscado);
    
    rewind(archivo); // Reiniciar el puntero de archivo al principio
    
    while (fscanf(archivo, "%s %s %d", nombre, apellido, &dni) != EOF) {
        if (dni == dniBuscado) {
            printf("Nombre: %s\nApellido: %s\nDNI: %d\n", nombre, apellido, dni);
            encontrado = 1;
            break; // Detener la búsqueda una vez que se encuentra la persona
        }
    }
    
    if (!encontrado) {
        printf("No se encontro ninguna persona con el DNI ingresado.\n");
    }
}

int main() {
    FILE *archivo;
    int opcion;
    
    archivo = fopen("datos.txt", "a+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    
    do {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                ingresarDatos(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Por favor, ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 3);
    
    fclose(archivo);
    return 0;
}

