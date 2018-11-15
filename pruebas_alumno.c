#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "testing.h"

#define TAMANIO 7

int comparacion(const void* elemento_1, const void* elemento_2) {
	
	int elem1= *(int*)elemento_1;
	int elem2= *(int*)elemento_2;
	
	if(elem1 < elem2) {
		return 1;
	}else if(elem1 > elem2) {
		return -1;
	}
	return 0;
}

int comparacion_string(const void* elemento_1, const void* elemento_2) {
	return strcmp(elemento_1, elemento_2);
}

static void pruebas_heap_vacio(){
	
	heap_t* heap= heap_crear((cmp_func_t)comparacion);
	
	print_test("Creo el heap", heap != NULL);
	print_test("Prueba heap vacio, cantidad de elementos 0", heap_cantidad(heap) == 0);
	print_test("Prueba heap vacio, TRUE", heap_esta_vacio(heap));
	print_test("Prueba heap vacio, el maximo es NULL", heap_ver_max(heap) ==  NULL);
	print_test("Prueba heap vacio, no puedo desencolar", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);
	printf("\n");
}

static void pruebas_heap_encolo_y_desencolo(){
	
	heap_t* heap= heap_crear((cmp_func_t)comparacion);
	int arreglo[4]= {7, 10, 15, 25};
	
	print_test("Creo el heap", heap != NULL);
	print_test("Prueba heap encolo 7", heap_encolar(heap, &arreglo[0]));
	print_test("Prueba heap cantidad de elementos 1", heap_cantidad(heap) == 1);
	print_test("Prueba heap el maximo es 7", heap_ver_max(heap) == &arreglo[0]);
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap desencolo 7", heap_desencolar(heap) == &arreglo[0]);
	print_test("Prueba heap encolo 25", heap_encolar(heap, &arreglo[3]));
	print_test("Prueba heap desencolo 25", heap_desencolar(heap) == &arreglo[3]);
	print_test("Prueba heap encolo 10", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap desencolo 10", heap_desencolar(heap) == &arreglo[1]);
	print_test("Prueba heap encolo 15", heap_encolar(heap, &arreglo[2]));
	print_test("Prueba heap desencolo 15", heap_desencolar(heap) == &arreglo[2]);
	print_test("Prueba heap cantidad de elementos 0", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
	printf("\n");
}

static void pruebas_heap_encolo_varios_elementos(){
	
	heap_t* heap= heap_crear((cmp_func_t)comparacion);
	int arreglo[TAMANIO]= {7, 10, 15, 25, 8, 13, 35};
	bool ok= true;
	
	print_test("Creo el heap", heap != NULL);
	
	for(size_t i=0; i < TAMANIO; i++){
		ok &= heap_encolar(heap, arreglo+i);
	}
	
	print_test("Prueba heap encolo todos los elmentos del arreglo", ok);
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 7", heap_cantidad(heap) == TAMANIO);
	print_test("Prueba heap el maximo es 35", heap_ver_max(heap) == &arreglo[6]);

	heap_destruir(heap, NULL);
	printf("\n");
}

static void pruebas_heap_encolo_varios_elementos2() {
	heap_t* heap= heap_crear((cmp_func_t)comparacion);
	int arreglo[TAMANIO]= {7, 10, 15, 25, 8, 13, 35};
	
	print_test("Prueba heap encolo 10", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap encolo 35", heap_encolar(heap, &arreglo[6]));
	print_test("Prueba heap desencolo 35", heap_desencolar(heap) == &arreglo[6]);
	print_test("Prueba heap encolo 8", heap_encolar(heap, &arreglo[4]));
	print_test("Prueba heap desencolo 10", heap_desencolar(heap) == &arreglo[1]);
	print_test("Prueba heap cantidad de elementos 1", heap_cantidad(heap) == 1);

	heap_destruir(heap, NULL);
	printf("\n");
}

static void pruebas_heap_crear_array(){
	void* array[TAMANIO];
	char *clave1 = "Republica de Corea";
	char *clave2 = "Argentina";
	char *clave3 = "Colombia";
	char *clave4 = "Mexico";
	char *clave5 = "Uruguay";
	char *clave6 = "Alemania";
	char *clave7 = "Arabia Saudita";
	
	array[0]= clave1;
	array[1]= clave2;
	array[2]= clave3;
	array[3]= clave4;
	array[4]= clave5;
	array[5]= clave6;
	array[6]= clave7;
	
	heap_t* heap= heap_crear_arr(array, TAMANIO, (cmp_func_t)comparacion_string);
	
	print_test("Creo el heap", heap != NULL);
	
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 7", heap_cantidad(heap) == TAMANIO);
	print_test("Prueba heap el maximo es Uruguay", heap_ver_max(heap) == clave5);

	free(heap);
	printf("\n");
}

static void pruebas_heap_crear_array2(){
	
	int arreglo[TAMANIO]= { 7, 10, 15, 25, 8, 13, 35 };
	void* array[TAMANIO];
	
	for(size_t i= 0; i < TAMANIO; i++) {
		array[i]= arreglo+i;
	}
	
	heap_t* heap= heap_crear_arr(array, TAMANIO, (cmp_func_t)comparacion);
	
	print_test("Creo el heap", heap != NULL);
	
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 7", heap_cantidad(heap) == TAMANIO);
	print_test("Prueba heap el maximo es 35", heap_ver_max(heap) == &arreglo[6]);

	free(heap);
	printf("\n");
}

static void prueba_heapsort(){
	int arreglo[TAMANIO]= {7, 10, 15, 25, 8, 13, 35};
	void* array[TAMANIO];
	printf("\nPrueba HeapSort\nOriginal:");
	for(size_t i=0; i < TAMANIO; i++){
		array[i]= arreglo+i;
		printf("%i ", *(int*)array[i]);
	}
	heap_sort(array, TAMANIO, (cmp_func_t)comparacion);
	printf("\nOrdenado:");
	for(size_t i = 0; i < TAMANIO; i++){
		printf("%i ", *(int*)array[i]);
	}
	printf("\n");
	heap_t* heap= heap_crear_arr(array, TAMANIO, (cmp_func_t)comparacion);
	while(!heap_esta_vacio(heap)){
		printf("%i ", *(int*)heap_desencolar(heap));
	}

}

void prueba_desencolar(){
	heap_t* heap= heap_crear((cmp_func_t)comparacion);
	int arreglo[2]= {10, 35};

	for(size_t i=0; i < 2; i++){
		heap_encolar(heap, arreglo+i);
	}
	printf("\n");
	print_test("Max es 35", *(int*)heap_ver_max(heap) == 35);
	print_test("Prueba heap desencolo 35", *(int*)heap_desencolar(heap) == 35);
	print_test("Heap NO esta vacio", !heap_esta_vacio(heap));
	print_test("Max es 10", *(int*)heap_ver_max(heap) == 10);
	print_test("Prueba heap desencolo 10", *(int*)heap_desencolar(heap) == 10);
	print_test("Heap esta vacio", heap_esta_vacio(heap));
	
	heap_destruir(heap, NULL);
	
	int arreglo_dos[3]= { 7, 10, 15};
	void* array[3];
	
	for(size_t i= 0; i < 3; i++) {
		array[i]= arreglo_dos+i;
	}

	heap_sort(array, TAMANIO, (cmp_func_t)comparacion);

	printf("\nOrdenado:");
	for(size_t i = 0; i < TAMANIO; i++){
		printf("%i ", *(int*)array[i]);
	}
	printf("\n");

	heap= heap_crear_arr(array, 3, (cmp_func_t)comparacion);
	
	printf("\nArray de minimos\n");
	for(size_t i = 0; i < 3; i++){
		printf("%i ", *(int*)array[i]);
	}

	printf("\n");
	print_test("Creo el heap", heap != NULL);
	
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 7", heap_cantidad(heap) == 3);
	
	while(!heap_esta_vacio(heap)){
		printf("%i ", *(int*)heap_desencolar(heap));
	}

	free(heap);
	printf("\n");
}

void pruebas_heap_alumno() {
	pruebas_heap_vacio();
	pruebas_heap_encolo_y_desencolo();
	pruebas_heap_encolo_varios_elementos();
	pruebas_heap_encolo_varios_elementos2();
	pruebas_heap_crear_array();
	pruebas_heap_crear_array2();
	prueba_heapsort();
	prueba_desencolar();
}
