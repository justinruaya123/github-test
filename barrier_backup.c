#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_pagod_nako[3];
int counter = 3;

void a() {
  while (1) {
    sem_wait(&sem_pagod_nako[0]);

    sem_wait(&sem_pagod_nako[1]);
    counter--;
    fprintf(stderr, "A");
    if(counter == 0) {
      sem_post(&sem_pagod_nako[2]);
    }
    sem_post(&sem_pagod_nako[1]);
  }
}

void b() {
  while (1) {
    sem_wait(&sem_pagod_nako[0]);

    sem_wait(&sem_pagod_nako[1]);
    counter--;
    fprintf(stderr, "B");
    if(counter == 0) {
      sem_post(&sem_pagod_nako[2]);
    }
    sem_post(&sem_pagod_nako[1]);
  }
}

void c() {
  while (1) {
    sem_wait(&sem_pagod_nako[0]);

    sem_wait(&sem_pagod_nako[1]);
    counter--;
    fprintf(stderr, "C");
    if(counter == 0) {
      sem_post(&sem_pagod_nako[2]);
    }
    sem_post(&sem_pagod_nako[1]);
  }
}

int main() {
  pthread_t ta, tb, tc;
  sem_init(&sem_pagod_nako[0], 0, 3);
  sem_init(&sem_pagod_nako[1], 0, 1);
  sem_init(&sem_pagod_nako[2], 0, 0);
  pthread_create(&ta, NULL, (void *) a, NULL);
  pthread_create(&tb, NULL, (void *) b, NULL);
  pthread_create(&tc, NULL, (void *) c, NULL);

  while (1) {
    sem_wait(&sem_pagod_nako[2]);
    counter = 3;
    fprintf(stderr, " ");
    sem_post(&sem_pagod_nako[0]);
    sem_post(&sem_pagod_nako[0]);
    sem_post(&sem_pagod_nako[0]);
  }
  sem_destroy(&sem_pagod_nako[0]);
  sem_destroy(&sem_pagod_nako[1]);
  sem_destroy(&sem_pagod_nako[2]);
  return 0;
}
