#include "heap.h"

#define TAMANIO_MINIMO 20 

struct heap{
	void** datos;
	size_t capacidad;
	size_t cantidad;
	cmp_func_t cmp;
};


heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	heap->datos = calloc(TAMANIO_MINIMO, sizeof(void*));
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	heap->cantidad = 0;
	heap->capacidad = TAMANIO_MINIMO;
	heap->cmp = cmp;
	return heap;
}

void heap_swap(void** datos, size_t posicion_padre, size_t posicion){
	void* auxiliar = datos[posicion_padre];

	datos[posicion_padre] = datos[posicion];
	datos[posicion] = auxiliar;
}

void heap_downheap(void** datos, size_t tamanio, size_t posicion, cmp_func_t cmp){
	if(posicion >= tamanio) return;

	size_t hijo_izq = 2*posicion+1;
	size_t hijo_der = 2*posicion+2;
	size_t maximo = posicion;

	if(hijo_izq < tamanio){
		if(cmp(datos[maximo], datos[hijo_izq]) < 0)
			maximo = hijo_izq;
	}

	if(hijo_der < tamanio){
		if(cmp(datos[maximo], datos[hijo_der]) < 0)
			maximo = hijo_der;
	}

	if(maximo != posicion){
		heap_swap(datos, posicion, maximo);
		return heap_downheap(datos, tamanio, maximo, cmp);
	}
	return;
}

void heapify(void** arreglo, size_t tamanio, cmp_func_t cmp){
	for(int i = tamanio/2; i >= 0; i--){
		heap_downheap(arreglo, tamanio, i, cmp);
	}
}

void heap_upheap(void** datos, size_t posicion, cmp_func_t cmp){
	if(posicion == 0) return;

	size_t padre = (posicion-1)/2;
	if(cmp(datos[padre], datos[posicion]) < 0){
		heap_swap(datos, padre, posicion);
		return heap_upheap(datos, padre, cmp);
	}
	return;
}

bool heap_encolar(heap_t *heap, void *elem){
	//Agregar funcion de redimension

	heap->datos[heap->cantidad] = elem;
	heap_upheap(heap->datos, heap->cantidad, heap->cmp);
	heap->cantidad++;

	return true;
}

void* heap_desencolar(heap_t* heap){
	if(heap_esta_vacio(heap)) return NULL;

	void* dato = heap->datos[0];
	heap_swap(heap->datos, 0, heap->cantidad-1);
	heap->cantidad--;
	heap_downheap(heap->datos, heap->cantidad, 0, heap->cmp);
	//Agregar funcion de redimension
	return dato;
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad == 0;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;

	return heap->datos[0];
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cant, cmp);

	for(int i = cant-1; i > 0; i--){
		heap_swap(elementos, 0, i);
		heap_downheap(elementos, i, 0, cmp);
	}
}


heap_t* heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	//heap_sort(arreglo, n, cmp);
	heapify(arreglo, n, cmp);
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->datos = arreglo;
	heap->cantidad = n;
	heap->capacidad = n;
	heap->cmp = cmp;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while(!heap_esta_vacio(heap)){
		void* dato = heap_desencolar(heap);
		if(destruir_elemento != NULL) destruir_elemento(dato);
	}
	free(heap->datos);
	free(heap);
}