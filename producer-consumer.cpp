#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>

using namespace std;

#define MAX_BUFFER_SIZE 10
queue<int> buffer;

void* productor(void* arg) {
    int item;
    while (true) {
        if (buffer.size() < MAX_BUFFER_SIZE) {
            item = rand() % 100; // Generar un ítem aleatorio
            buffer.push(item);   // Añadir ítem al buffer
            cout << "Productor produjo: " << item << endl;
        } else {
            cout << "Buffer lleno. Productor esperando..." << endl;
        }

        sleep(1); // Simular tiempo de producción
    }
    return nullptr;
}

void* consumidor(void* arg) {
    int item;
    while (true) {
        if (!buffer.empty()) { // Verificar si el buffer no está vacío
            item = buffer.front(); // Obtener el primer ítem del buffer
            buffer.pop();
            cout << "Consumidor consumió: " << item << endl;
        } else {
            cout << "Buffer vacío. Consumidor esperando..." << endl;
        }

        sleep(2); // Simular tiempo de consumo
    }
    return nullptr;
}

int main() {
    pthread_t prodThread, consThread;

    // Crear hilos de productor y consumidor
    pthread_create(&prodThread, nullptr, productor, nullptr);
    pthread_create(&consThread, nullptr, consumidor, nullptr);

    // Esperar a que los hilos terminen (aunque en este caso no terminan)
    pthread_join(prodThread, nullptr);
    pthread_join(consThread, nullptr);

    return 0;
}