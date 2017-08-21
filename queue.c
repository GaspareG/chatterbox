/*
 * chatterbox Progetto del corso di LSO 2017 
 *
 * Dipartimento di Informatica Università di Pisa
 * Docenti: Prencipe, Torquati
 * 
 */

#ifndef QUEUE_C_
#define QUEUE_C_

#include <pthread.h>
#include <queue.h>
#include <stdlib.h>
#include <string.h>

queue_t* create_queue(int size) {
  queue_t* q = (queue_t*)malloc(sizeof(queue_t));
  memset(q, 0, sizeof(queue_t));
  q->size = size;
  q->data = (int*) malloc(size * sizeof(int));
  q->front = 0;
  q->back = 0;
  pthread_mutex_init(&(q->mtx), NULL);
  return q;
}


int push_queue(queue_t* q, int value)
{
  int ret = -1;
  pthread_mutex_lock(&(q->mtx));  
  if ( q->front != (q->back+1)%(q->size) )
  {
    q->data[q->back] = value;
    q->back = (q->back + 1) % q->size;
    ret = value;
  }
  pthread_mutex_unlock(&(q->mtx));  
  return ret;
}

int pop_queue(queue_t* q) {
  int ret = -1;
  pthread_mutex_lock(&(q->mtx));
  if(q->front != q->back)
  {
    ret = q->data[q->front];
    q->front = (q->front + 1) % q->size;
  }
  pthread_mutex_unlock(&(q->mtx));  
  return ret;
}

void delete_queue(queue_t* q) {
  pthread_mutex_lock(&(q->mtx));  
  pthread_mutex_destroy(&(q->mtx));  
  free(q->data);
  free(q);
}

    

#endif /* QUEUE_C_ */
