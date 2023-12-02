#include "hashmap.h" // Archivo de cabecera para la tabla hash
#include "list.h"    // Archivo de cabecera para la lista
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Definir la estructura para las subcarpetas y archivos .txt
typedef struct {
  char nombre[256]; // Nombre de la subcarpeta o archivo .txt
} Item;

// Función para agregar un ítem a la lista
void agregarItemALista(List *lista, const char *nombre) {
  Item *nuevoItem = (Item *)malloc(sizeof(Item));
  snprintf(nuevoItem->nombre, sizeof(nuevoItem->nombre), "%s", nombre);
  pushFront(lista, nuevoItem);
}

// Función para obtener el nombre de un item en la lista
const char *getItemNombre(List *lista, int seleccion) {
  Item *item = list_get(lista, seleccion - 1); // Ajuste de índice
  return item->nombre;
}

// Función para mostrar el contenido de un directorio
void mostrarContenidoDirectorio(const char *ruta, HashMap *carpetasPrincipales,
                                List *subCarpetas, List *archivosTxt) {
  DIR *directorio;
  struct dirent *entrada;

  directorio = opendir(ruta);

  if (directorio == NULL) {
    perror("Error al abrir el directorio");
    exit(EXIT_FAILURE);
  }

  // Imprimir el contenido del directorio
  printf("\n-----Listado de regiones-----\n");

  int opcion = 1;

  while ((entrada = readdir(directorio)) != NULL) {
    if (strcmp(entrada->d_name, ".") != 0 &&
        strcmp(entrada->d_name, "..") != 0) {
      // Agregar cada carpeta principal a la tabla hash
      insertMap(carpetasPrincipales, entrada->d_name, NULL);
      printf("%d: %s\n", opcion, entrada->d_name);

      // Agregar la carpeta principal a la lista de subcarpetas
      agregarItemALista(subCarpetas, entrada->d_name);

      opcion++;
    }
  }

  closedir(directorio);
}

// Función para mostrar el contenido de un archivo de texto
void mostrarContenidoArchivo(const char *ruta, List *archivosTxt) {
  FILE *archivo;
  char caracter;

  archivo = fopen(ruta, "r");

  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    exit(EXIT_FAILURE);
  }

  // Agregar el archivo a la lista de archivos .txt
  agregarItemALista(archivosTxt, ruta);

  while ((caracter = fgetc(archivo)) != EOF) {
    printf("%c", caracter);
  }

  fclose(archivo);
}

// Función para explorar archivos .txt dentro de una subcarpeta
void explorarArchivosTxt(const char *ruta, List *archivosTxt) {
  DIR *directorio;
  struct dirent *entrada;

  directorio = opendir(ruta);

  if (directorio == NULL) {
    perror("Error al abrir el directorio");
    exit(EXIT_FAILURE);
  }

  int opcion = 1;

  // Mostrar los archivos .txt y permitir al usuario seleccionar uno
  printf("\n-----Tipos de informacion-----\n");

  while ((entrada = readdir(directorio)) != NULL) {
    if (strcmp(entrada->d_name, ".") != 0 &&
        strcmp(entrada->d_name, "..") != 0) {
      printf("%d: %s\n", opcion, entrada->d_name);

      // Agregar el archivo .txt a la lista de archivos .txt
      agregarItemALista(archivosTxt, entrada->d_name);

      opcion++;
    }
  }

  // Pedir al usuario que seleccione un archivo .txt
  int seleccion;
  printf("\nSeleccione un tipo de informacion: ");
  scanf("%d", &seleccion);
  printf("\n");

  // Obtener el nombre del archivo .txt seleccionado
  const char *archivoTxt = getItemNombre(archivosTxt, seleccion);

  // Construir la ruta completa del archivo .txt
  char rutaArchivoTxt[256];
  snprintf(rutaArchivoTxt, sizeof(rutaArchivoTxt), "%s/%s", ruta, archivoTxt);

  // Mostrar el contenido del archivo .txt seleccionado
  mostrarContenidoArchivo(rutaArchivoTxt, archivosTxt);

  closedir(directorio);
}

// Función para explorar subcarpetas dentro de una carpeta principal
void explorarSubCarpetas(const char *ruta, List *subCarpetas,
                         List *archivosTxt) {
  DIR *directorio;
  struct dirent *entrada;

  directorio = opendir(ruta);

  if (directorio == NULL) {
    perror("Error al abrir el directorio");
    exit(EXIT_FAILURE);
  }

  int opcion = 1;

  // Mostrar las subcarpetas y permitir al usuario seleccionar una
  printf("\n-----Listado de areas protegidas-----\n");

  while ((entrada = readdir(directorio)) != NULL) {
    if (strcmp(entrada->d_name, ".") != 0 &&
        strcmp(entrada->d_name, "..") != 0) {
      printf("%d: %s\n", opcion, entrada->d_name);

      // Agregar la subcarpeta a la lista de archivos .txt
      agregarItemALista(subCarpetas, entrada->d_name);

      opcion++;
    }
  }

  // Pedir al usuario que seleccione una subcarpeta
  int seleccion;
  printf("\nSeleccione un area protegida: ");
  scanf("%d", &seleccion);

  // Obtener el nombre de la subcarpeta seleccionada
  const char *subCarpeta = getItemNombre(subCarpetas, seleccion);

  // Construir la ruta completa de la subcarpeta
  char rutaSubCarpeta[256];
  snprintf(rutaSubCarpeta, sizeof(rutaSubCarpeta), "%s/%s", ruta, subCarpeta);

  // Explorar recursivamente la subcarpeta seleccionada
  explorarArchivosTxt(rutaSubCarpeta, archivosTxt);

  closedir(directorio);
}

// Función para explorar recursivamente carpetas y archivos
void explorarCarpetas(const char *ruta, HashMap *carpetasPrincipales,
                      List *subCarpetas, List *archivosTxt) {
  DIR *directorio;
  struct dirent *entrada;

  directorio = opendir(ruta);

  if (directorio == NULL) {
    perror("Error al abrir el directorio");
    exit(EXIT_FAILURE);
  }

  int seleccion;

  // Mostrar las carpetas principales y permitir al usuario seleccionar una
  mostrarContenidoDirectorio(ruta, carpetasPrincipales, subCarpetas,
                             archivosTxt);
  printf("\nSeleccione una region: ");
  scanf("%d", &seleccion);

  // Obtener el nombre de la carpeta principal seleccionada
  const char *carpetaPrincipal = map_get_key(carpetasPrincipales, seleccion);

  // Construir la ruta completa de la carpeta principal
  char rutaCarpetaPrincipal[256];
  snprintf(rutaCarpetaPrincipal, sizeof(rutaCarpetaPrincipal), "%s/%s", ruta,
           carpetaPrincipal);

  // Explorar recursivamente la carpeta principal seleccionada
  explorarSubCarpetas(rutaCarpetaPrincipal, subCarpetas, archivosTxt);

  closedir(directorio);
}

int main() {
  // Crear la tabla hash para las carpetas principales
  HashMap *carpetasPrincipales =
      createMap(100); // Ajusta la capacidad según sea necesario

  // Crear la lista para las subcarpetas y archivos .txt
  List *subCarpetas = createList();
  List *archivosTxt = createList();
  printf("    ______         ______                 _      __ \n");
  printf("   / ____/________/_  __/___  __  _______(_)____/ /_\n");
  printf("  / __/ / ___/ __ \\/ / / __ \\/ / / / ___/ / ___/ __/\n");
  printf(" / /___/ /__/ /_/ / / / /_/ / /_/ / /  / (__  ) /_  \n");
  printf("/_____/\\___/\\____/_/  \\____/\\____/_/  /_/____/\\__/  \n");
  printf("                                                    \n");

  const char *nuevaRuta = "regiones";

  explorarCarpetas(nuevaRuta, carpetasPrincipales, subCarpetas, archivosTxt);
  // Explorar recursivamente todas las carpetas y archivos

  // Liberar memoria de la tabla hash y las listas
  destroyMap(carpetasPrincipales); // Agrega esta línea para liberar la memoria
                                   // de la tabla hash
  cleanList(subCarpetas); // Agrega esta línea para liberar la memoria de la
                          // lista de subcarpetas
  cleanList(archivosTxt); // Agrega esta línea para liberar la memoria de la
                          // lista de archivos .txt

  return 0;
}