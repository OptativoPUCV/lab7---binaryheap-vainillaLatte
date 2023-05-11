#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq)
{
  if(pq->size == 0)
  {
    return NULL;
  }
  return pq->heapArray->data;
}

void heap_push(Heap* pq, void* data, int p)
{
  if(pq->size == pq->capac)
  {
    pq->capac = (pq->capac * 2) + 1;
    pq->heapArray = realloc(pq->heapArray, pq->capac * sizeof(heapElem));
  }

  int i = pq->size;
  pq->heapArray[i].priority = p;
  pq->heapArray[i].data = data;
  pq->size++;

  while(i > 0 && pq->heapArray[i].priority > pq->heapArray[(i - 1)/2].priority)
  {
    heapElem tmp = pq->heapArray[i]; //Variable temporal, para guardar dato que se desea cambiar
    pq->heapArray[i] = pq->heapArray[(i - 1)/2];
    pq->heapArray[(i - 1)/2] = tmp;
    i = (i - 1)/2;
  }
}

void heap_pop(Heap* pq)
{
  int i = pq->size;
  pq->heapArray[0] = pq->heapArray[i-1];
  i--;

  int k = 0;
  while(1)
  {
   int hijoD = (2 * k) + 2;
   int hijoI = (2 * k) + 1;
   int tmp = k;
    
    if(hijoI < i && pq->heapArray[hijoI].priority > pq->heapArray[tmp].priority)
    {
      tmp = hijoI;
    }

    if(hijoD < i && pq->heapArray[hijoD].priority > pq->heapArray[tmp].priority)
    {
      tmp = hijoD;
    }

    if(tmp != k)
    {
      heapElem tmp2 = pq->heapArray[k];
      pq->heapArray[k] = pq->heapArray[tmp];
      pq->heapArray[tmp] = tmp2;
      k = tmp;
    }
    break;
  }
  pq->size = i;
}

Heap* createHeap()
{
  Heap arreglo = (Heap)malloc(sizeof(Heap));

  arreglo->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
  arreglo->size = 0;
  arreglo->capac = 3;
  return arreglo;
}