#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5        // Número de hilos
#define NUM_INCREMENTS 1000000 // Número de incrementos por hilo

int counter = 0; // Contador compartido

void* incrementar(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        counter++; // Incrementar el contador sin sincronización
    }
    return nullptr;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Crear los hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], nullptr, incrementar, nullptr);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    // Imprimir el valor final del contador
    cout << "Valor final del contador: " << counter << endl;

    return 0;
}