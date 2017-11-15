#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main() {
    const char *name = "OS"; // Name of shared memory area.
    const int SIZE = 4096; // Size (in bytes) of area.
    int shm_fd; // Shared memory file descriptor.
    int *ptr; // Pointer to the shared memory area.
    int j = 0;//Marcador para saber onde começa o envio de numeros primos
    int primos[20] = {2, 3 , 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);//Abre uma área de memoria compartilhada
    ftruncate(shm_fd,SIZE);//Define tamanho maximo 
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);//

    int *marcador1 = ptr;
    ptr++;
    int *marcador2 = ptr;
    ptr++;
    
    printf("[PRODUCER]: Ready to send primes.\n");

    *marcador1 = -1;
    while(*marcador1 != 0){
        if(*marcador1 != -1 && *marcador1 != 0){
            printf("[PRODUCER]: Sending %d new primes.\n",*marcador2 );
            for(int i = 0; i < *marcador2; i++){
                *ptr = primos[j];
                ptr++;
                j++;
            }
            *marcador1 = -1;
        }
    }
    
    printf("[PRODUCER]: Finished.\n");

    return 0;
}
