#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
#define NUM_FILOSOFOS 5
pthread_mutex_t tenedores[NUM_FILOSOFOS]; //un mutex por cada tenedor

void* filosofo(void* arg){
    int id = *(int*)arg;
    while(true){
        //Pensando
        cout << "Filosofo " << id << " esta pensando ..." << endl;
        sleep(rand() % 3 + 1);//simular tiempo pensando
        //intenta tomar tenedores
        cout << "Filosofo " << id << " intenta tomar los tenedores." << endl;
        //tomar el de la izquierda
        pthread_mutex_lock(&tenedores[id]);
        cout << "Filosofo " << id << " tomo el tenedor izquierdo." << endl;
        //tomar el tenededor de la izquierda
        pthread_mutex_lock(&tenedores[(id+1) % NUM_FILOSOFOS]);
        cout << "Filosofos " << id << " tomo el tenedor derecho." << endl;
        //Comiendo
        cout << "Filosofo " << id << "esta comiendo..." << endl;
        sleep(rand() % 3 + 1);//simular tiempo de comer
        //soltar tenedores
        pthread_mutex_lock(&tenedores[(id + 1) % NUM_FILOSOFOS]);
        pthread_mutex_lock(&tenedores[id]);
        cout << "Filosfo "<< id << "solto ambos tenedores." << endl;
    }
    return nullptr;
}

int main(){
    pthread_t filosofos[NUM_FILOSOFOS];
    int id[NUM_FILOSOFOS];
    //inicializar el estado de los tenedores a libre (false)
    for (int i = 0; i < NUM_FILOSOFOS; i++){
        tenedores[i] = false;
        id[i] = i;
    }
    //crear hilo para cada filosofo
    for(int i = 0; i < NUM_FILOSOFOS; i++){
        pthread_create(&filosofos[i],nullptr,filosofo, &id[i]);
    }

    for(int i = 0; i < NUM_FILOSOFOS; i++){
        pthread_join(filosfos[i],nullptr);
    }
    return 0;
}