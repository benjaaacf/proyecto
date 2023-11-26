#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Mapa *crearMapa() {
  Mapa *mapa = (Mapa *)malloc(sizeof(Mapa));
  for (int i = 0; i < 15; i++) {
    mapa->regiones[i] = NULL;
  }
  return mapa;
}

void destruirMapa(Mapa *mapa) {
  if (mapa != NULL) {
    for (int i = 0; i < 15; i++) {
      if (mapa->regiones[i] != NULL) {
        destruirListaParques(mapa->regiones[i]);
      }
    }
    free(mapa);
  }
}

int mostrarMenuRegiones(Mapa *mapa) {
  
}

ListaParques *obtenerParquesPorRegion(Mapa *mapa, int region) {
  
}
