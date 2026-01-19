/* COP 3502C Assignment 2
This program is written by: Lucas Luna */

#include <stdio.h>
#include <stdlib.h>

// Sets up the structure of the students
typedef struct node {
  int data;
  struct node *next;
} Student;

// Sets up the structure of the queue
typedef struct queue {
  Student *front;
  Student *back;
  int nodeCount;
  int k;
  int th;
} queue;

// Creates a new Student node to be added to the queue
Student *createStudent(int data) {
  Student *res = (Student *)malloc(sizeof(Student));
  res->data = data;
  res->next = res;
  return res;
}

// Ininializes the queue and its values
void init(queue *qPtr) {
  qPtr->front = NULL;
  qPtr->back = NULL;
  qPtr->nodeCount = 0;
  qPtr->k = 0;
  qPtr->th = 0;
}

// Adds a new student to the back of the queue
int enqueue(queue *qPtr, int val) {
  if (qPtr == NULL) {
    return -1;
  }

  Student *temp = createStudent(val);
  int currentSize = qPtr->nodeCount;
  qPtr->nodeCount = currentSize + 1;

  if (qPtr->front == NULL) {
    qPtr->front = temp;
    qPtr->back = temp;
    return 1;
  }

  qPtr->back->next = temp;
  temp->next = qPtr->front;
  qPtr->back = temp;

  return 1;
}

// Removes a Student from the front of the queue
int dequeue(queue *qPtr) {
  if (qPtr->front == NULL) {
    return -1;
  }

  qPtr->nodeCount--;

  if (qPtr->front == qPtr->back) {
    free(qPtr->front);
    qPtr->front = NULL;
    qPtr->back = NULL;
    return 1;
  }

  Student *temp = qPtr->front;
  qPtr->front = qPtr->front->next;
  free(temp);
  if (qPtr->back != NULL) {
    qPtr->back->next = qPtr->front;
  }
  return 1;
}

// Returns the front value of the queue
int peak(queue *qPtr) {
  if (qPtr->front != NULL) {
    return qPtr->front->data;
  } else {
    return -1;
  }
}

// Checks to see if a queue is empty
int isEmpty(queue *qPtr) {
  if (qPtr->front == NULL) {
    return 1;
  } else {
    return 0;
  }
}

// Reverses the order of values in the queue
void createReverseCircle(queue *qPtr) {

  if (qPtr == NULL || qPtr->back == qPtr->front) {
    return;
  }

  int *values = (int *)malloc(sizeof(int) * qPtr->nodeCount);
  int currentNodeIndex = 0;
  Student *curr = qPtr->front;
  for (; curr != NULL && curr != qPtr->back; curr = curr->next) {
    values[currentNodeIndex++] = curr->data;
  }
  if (curr != NULL) {
    values[currentNodeIndex] = curr->data;
  }

  int i;
  for (i = qPtr->nodeCount; i > 0; i--) {
    enqueue(qPtr, values[i - 1]);
    dequeue(qPtr);
  }
  free(values);
}

// Rearrages the queue so that the first k students are at the back
void rearrangeCircle(queue *qPtr) {
  if (qPtr == NULL || qPtr->back == qPtr->front) {
    return;
  }

  int *values = (int *)malloc(sizeof(int) * qPtr->nodeCount);
  int currentNodeIndex = 0;
  Student *curr = qPtr->front;
  for (; curr != NULL && curr != qPtr->back; curr = curr->next) {
    values[currentNodeIndex++] = curr->data;
  }
  if (curr != NULL) {
    values[currentNodeIndex] = curr->data;
  }

  int i;
  for (i = qPtr->nodeCount; i > 0; i--) {
    enqueue(qPtr, values[i - 1]);
    dequeue(qPtr);
  }
  free(values);
}

// Prints out the values in the queue
void display(queue *qPtr) {
  if (qPtr->front == NULL) {
    printf("Queue is empty\n");
    return;
  }
  Student *temp = qPtr->front;
  printf("%d ", temp->data);
  temp = temp->next;
  while (temp != qPtr->front) {
    printf("%d", temp->data);
    if (temp->next != qPtr->front) {
      printf(" ");
    }
    temp = temp->next;
  }
  printf("\n");
}

// Goes through a queue and leaves the threshold amount of values left over
int phase1(queue *qPtr) {
  Student *temp = qPtr->front;
  Student *prev = NULL;
  for (int i = 0; i < (qPtr->nodeCount - qPtr->th); i++) {
    for (int j = 1; j < qPtr->k; j++) {
      prev = temp;
      temp = temp->next;
    }

    printf("Student# %d eliminated\n", temp->data);

    if (temp == qPtr->front && temp == qPtr->back) {
      qPtr->front = NULL;
      qPtr->back = NULL;
    }

    if (temp == qPtr->front) {
      qPtr->front = temp->next;
    }
    if (temp == qPtr->back) {
      qPtr->back = prev;
    }
    prev->next = temp->next;

    free(temp);
    if (i != (qPtr->nodeCount - qPtr->th) - 1) {
      temp = prev->next;
    }
  }
  qPtr->nodeCount = qPtr->th;
  return 0;
}

// Removes the largest front value from the queues until the winner is leftover
int phase2(queue *qPtr) {
  int totalNodeCount = 0;
  int maxValIndex = 0;

  for (int i = 0; i < 10; i++) {
    totalNodeCount += qPtr[i].nodeCount;
  }
  while (totalNodeCount > 1) {
    int highestVal = -99;
    for (int i = 0; i < 10; i++) {
      if (isEmpty(&qPtr[i]) == 0) {
        if (peak(&qPtr[i]) > highestVal) {
          highestVal = peak(&qPtr[i]);
          maxValIndex = i;
        }
      }
    }
    printf("Eliminated student %d from group for garage %d\n", highestVal,
           maxValIndex + 1);
    dequeue(&qPtr[maxValIndex]);
    totalNodeCount = totalNodeCount - 1;
  }
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&qPtr[i]) == 0) {
      printf("\nStudent %d from the group for garage %d is the winner!\n",
             qPtr[i].front->data, i + 1);
    }
  }
  return 0;
}

int main(void) {
  // Alloctes memory for the 10 queues
  int groupCount, garageNumber, groupSize, skip, threshold;
  scanf("%d", &groupCount);
  queue *garagePtr = (queue *)malloc(sizeof(queue) * 10);

  // Initiallizes the queues
  for (int i = 0; i < 10; i++) {
    init(&garagePtr[i]);
  }

  // Scans in the values for the queues
  for (int i = 0; i < groupCount; i++) {
    scanf("%d %d %d %d", &garageNumber, &groupSize, &skip, &threshold);

    garagePtr[garageNumber - 1].k = skip;
    garagePtr[garageNumber - 1].th = threshold;
    for (int j = groupSize; j > 0; --j) {
      enqueue(&garagePtr[garageNumber - 1], j);
    }
  }

  // Displays the initial queues
  printf("Initial status of nonempty queues\n");
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&garagePtr[i]) == 0) {
      printf("%d ", i + 1);
      display(&garagePtr[i]);
    }
  }

  // Reverses the order of the queues then displays them
  printf("\nAfter ordering status of nonempty queues\n");
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&garagePtr[i]) == 0) {
      printf("%d ", i + 1);
      createReverseCircle(&garagePtr[i]);
      display(&garagePtr[i]);
    }
  }

  // Initiates Phase1
  printf("\nPhase1 elimination\n");
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&garagePtr[i]) == 0) {
      printf("\nGroup for Garage# %d\n", i + 1);
      phase1(&garagePtr[i]);
    }
  }

  // Initiates Phase2
  printf("\nPhase2 elimination\n");
  phase2(garagePtr);

  // Frees the memory
  for (int i = 0; i < 10; i++) {
    while (!isEmpty(&garagePtr[i])) {
      dequeue(&garagePtr[i]);
    }
  }
  free(garagePtr);

  return 0;
}