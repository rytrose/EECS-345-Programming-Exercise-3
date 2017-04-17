#include <stdio.h>
#include <stdlib.h>

struct node {
  int element;
  struct node* next;
  struct node* prev;
};

struct list {
  struct node* head;
  struct node* tail;
};

struct list* new_list();
void add_to_front(int, struct list *);
void add_to_back(int , struct list *);
int remove_from_front(struct list *);
int remove_from_back(struct list *);
struct node* new_node(int);

struct list* new_list(){
  struct list* l = (struct list*) malloc(sizeof(struct list));

  l->head = NULL;
  l->tail = NULL;

  return l;
}

void add_to_front(int element, struct list *l){
  struct node* n = new_node(element);
  struct node* temp = l->head;

  if(temp == NULL){
    n->next = NULL;
    n->prev = NULL;
    l->head = n;
    l->tail = n;
    return;
  } else {
    temp->next = n;
    l->head = n;
    n->prev = temp;
  }
}

void add_to_back(int element, struct list *l){
  struct node* n = new_node(element);
  struct node* temp = l->tail;

  if(temp == NULL){
    n->next = NULL;
    n->prev = NULL;
    l->head = n;
    l->tail = n;
    return;
  } else {
    temp->prev = n;
    l->tail = n;
    n->next = temp;
  }
}

int remove_from_front(struct list *l){
  if(l->head == NULL){
    printf("No nodes in list. Returning -1 as error.\n");
    return -1;
  }

  struct node* newHead = l->head->prev;
  struct node* oldHead = l->head;
  int removedElement = l->head->element;

  if(newHead == NULL){
      // free(oldHead);
      l->head = NULL;
      l->tail = NULL;
      return removedElement;
  } else {
    l->head = newHead;
    newHead->next = NULL;
    free(oldHead);
    return removedElement;
  }
}

int remove_from_back(struct list *l){
  if(l->tail == NULL){
    printf("No nodes in list. Returning -1 as error.\n");
    return -1;
  }

  struct node* newTail = l->tail->next;
  struct node* oldTail = l->tail;
  int removedElement = l->tail->element;

  if(newTail == NULL){
      // free(oldTail);
      l->head = NULL;
      l->tail = NULL;
      return removedElement;
  } else {
    l->tail = newTail;
    newTail->prev = NULL;
    free(oldTail);
    return removedElement;
  }
}

void transfer(int a1[], int a2[], int length, void (*insertFunc)(int, struct list*), int (*removeFunc)(struct list*)){
  struct list* ls = new_list();

  printf("a1: ");

  int i;
  for(i = 0; i < length; i++){
    insertFunc(a1[i], ls);
    printf("%d ", a1[i]);
  }

  printf("\n");
  printf("a2: ");

  int j;
  for(j = 0; j < length; j++){
    a2[j] = removeFunc(ls);
    printf("%d ", a2[j]);
  }

  printf("\n");

  return;
}

struct node* new_node(int element){
  struct node* n = (struct node*) malloc(sizeof(struct node));
  n->element = element;
  n->next = NULL;
  n->prev = NULL;

  return n;
}

int main(int argc, char *argv[]){
  printf("Creating empty list...\n");
  struct list* l = new_list();
  printf("The list head is: %d\n", l->head);
  printf("Adding node to front...\n");
  add_to_front(2, l);
  printf("The element of the list head is: %d\n", l->head->element);
  add_to_front(1, l);
  printf("The element of the list head is: %d\n", l->head->element);
  printf("The element of the prev of the list head is: %d\n", l->head->prev->element);
  add_to_back(3, l);
  printf("The element of the list tail is: %d\n", l->tail->element);
  printf("Removing from front: %d\n", remove_from_front(l));
  printf("The element of the list head is now: %d\n", l->head->element);
  printf("Removing from back: %d\n", remove_from_back(l));
  printf("The element of the list tail is now: %d\n", l->tail->element);
  printf("The element of the list head is now: %d\n", l->head->element);

  int a1[4] = {1, 2, 3, 4};
  int a2_1[4];
  int a2_2[4];
  int a2_3[4];
  int a2_4[4];

  void (*insertFuncPtr)(int, struct list *);
  int (*removeFuncPtr)(struct list *);

  printf("Transfer 1: add_to_front, remove_from_front:\n");
  printf("-----\n");
  insertFuncPtr = add_to_front;
  removeFuncPtr = remove_from_front;
  transfer(a1, a2_1, 4, insertFuncPtr, removeFuncPtr);
  printf("-----\n\n");

  printf("Transfer 2: add_to_front, remove_from_back:\n");
  printf("-----\n");
  insertFuncPtr = add_to_front;
  removeFuncPtr = remove_from_back;
  transfer(a1, a2_2, 4, insertFuncPtr, removeFuncPtr);
  printf("-----\n\n");

  printf("Transfer 3: add_to_back, remove_from_front:\n");
  printf("-----\n");
  insertFuncPtr = add_to_back;
  removeFuncPtr = remove_from_front;
  transfer(a1, a2_3, 4, insertFuncPtr, removeFuncPtr);
  printf("-----\n\n");

  printf("Transfer 4: add_to_back, remove_from_back:\n");
  printf("-----\n");
  insertFuncPtr = add_to_back;
  removeFuncPtr = remove_from_back;
  transfer(a1, a2_4, 4, insertFuncPtr, removeFuncPtr);
  printf("-----\n");

  return 0;
}
