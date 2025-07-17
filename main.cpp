#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>

#define NUM_THREADS 7
#define QUOTE_FILE "QUOTE.txt"

sem_t *flag;
sem_t local_sem;

void* run_bot(void* id); //Forward declaration

//This initializes the QUOTE.txt file with the process ID
void initialize_quote_file() {
    FILE *file = fopen(QUOTE_FILE, "w");
    if (file == NULL) {
        perror("Failed to create QUOTE.txt");
        exit(1);
    }
    fprintf(file, "Process ID: %d\n", getpid());
    fclose(file);
}

//This initializes the unnamed semaphore
void initialize_semaphore() {
    flag = &local_sem;
    if (sem_init(flag, 0, 1) != 0) {
        perror("Semaphore initialization failed");
        exit(1);
    }
}

//This creates and starts all the threads
void create_threads(pthread_t* bots) {
    for (long i = 0; i < NUM_THREADS; i++) {
        printf("Creating thread, in main(): %ld\n", i + 1);
        if (pthread_create(&bots[i], NULL, run_bot, (void*)(intptr_t)i) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }
}

//This joins all threads once they finish
void join_threads(pthread_t* bots) {
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(bots[i], NULL);
    }
}

//This is the function that each thread runs
void* run_bot(void* id) {
    long tid = (long)(intptr_t)id;

    for (int i = 0; i < 8; i++) {
        if (tid % 2 == 0)
            sleep(2);
        else
            sleep(3);

        sem_wait(flag);

        FILE *file = fopen(QUOTE_FILE, "a");
        if (file == NULL) {
            perror("Error opening QUOTE.txt");
            sem_post(flag);
            pthread_exit(NULL);
        }

        if (tid % 2 == 0) {
            fprintf(file, "Thread ID %ld: \"Controlling complexity is the essence of computer programming.\"\n --Brian Kernighan\n", tid);
        } else {
            fprintf(file, "Thread ID %ld: \"Computer science is no more about computers than astronomy is about telescopes.\"\n --Edsger Dijkstra\n", tid);
        }

        fclose(file);

        printf("Thread %ld is running\n", tid);

        sem_post(flag);
    }

    pthread_exit(NULL);
    return NULL;
}

int main() {
    pthread_t bots[NUM_THREADS];

    initialize_quote_file();
    initialize_semaphore();
    create_threads(bots);
    join_threads(bots);
    sem_destroy(flag);

    printf("All threads completed. QUOTE.txt has been updated. Open QUOTE.txt to view! Goodbye!\n");
    return 0;
}
