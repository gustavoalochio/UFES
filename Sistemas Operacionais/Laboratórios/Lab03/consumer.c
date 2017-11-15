#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main() {
    const char *name = "OS"; // Name of shared memory area.
    const int SIZE = 4096; // Size (in bytes) of area.
    int shm_fd; // Shared memory file descriptor.
    int *ptr; // Pointer to the shared memory area.
    int num;
    shm_fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int *marcador1 = ptr;
    ptr++;
    int *marcador2 = ptr;
    ptr++;

    while(1){
        printf("[CLIENT]: Amount of primes to request: ");
        scanf("%d",&num);
        if(num == 0){
            *marcador1 = 0;
            break;
        }

        *marcador2 = num;
        *marcador1 = 1;

        for(int i = 0; i < num;i++){
            printf("%d ",*ptr);
            ptr++;
        }
        printf("\n");

    }

    printf("[PRODUCER]: Finished.\n");
    // Remove the shared memory segment.
    shm_unlink(name);
    
    return 0;
}