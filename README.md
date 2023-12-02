Integrantes:
Benjamín Caballeria 21.608.700-3        
Sofía Meza 20.999.001-6
Fernanda Cadíz 21.561.209-0

Para compilar: gcc main.c list.c hashmap.c -o proyecto
Para ejecutar: ./proyecto

Funcionando: El programa esta funcionando por completo y la gran mayoria de sus implementaciones estan correctas
Con errores: Al seleccionar una region, muestra una informacion de una region distinta a la seleccionada, al seleccionar un area protegida ocurre lo mismo, ya que muestra informacion de un area protegida distinta a la seleccionada dentro de la misma region. Para la informacion ocurre lo mismo. ya seleccionada el area protegida, al elejir una de las tres opciones muestra la informacion de algun otro archivo txt que hay dentro del area protegida.
Este error creemos que se debe a que pedimos al usuario ingresar un numero entero de opcion y estamos almacenando clabes, es decir, lo que es para buscar como los nombres de las regiones (un char), por eso muestra datos de distinat region  a la seleccionada. Lo otro, es que estamos usando lo que realmente queríamos usar como valor que es el nombre de las regiones como clave del hashmap y pasando un Null como valor.

Una posible solucion es haciendo un casting de int a char de opción y poniendo opción como la clave del mapa y como valor la región.

Coevaluacion: Sofia Meza 10/10
              Benjamin Caballeria 10/10
              Fernanda Cadiz 10/10
Contribuciones:
El codigo fue desarrollado en conjunto en todo momento. hay funciones que fueron hechas por un integrante y completadas por otro y asi sucesivamente, por lo cual entre todos pudimos llevar a cabo el proyecto aportando de manera equitativa al desarrollo del programa.