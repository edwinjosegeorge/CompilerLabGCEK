struct stack{
  void *info;
  struct stack *next;
};

struct stack *push(struct stack *A,void *info){ //push node to top and returns to top addr
  struct stack *tmp = malloc(sizeof(struct stack));
  tmp->info = info;
  tmp->next = A;
  return tmp;
}

struct stack *pop(struct stack *A){ //pop the node from top and returns new addr
  if(A != NULL){
    struct stack *tmp = A->next;
    free(A);
    A = tmp;
  }
  return A;
}

int search(struct stack *A, void* info, int (*cmpfunc)(void*,void*)){
  /* searches for info in stack using the defintion passed as function pointer
     returns the position of search result (starts from top as 1)
     if not found, returns zero
  */
  struct stack *tmp = A;
  int pos = 1;
  while(tmp != NULL){
    if(cmpfunc(tmp->info,info))return pos;
    pos++;
    tmp = tmp->next;
  }
  return 0;
}

struct stack *delete_index(struct stack *A, int pos){
  // deletes node at position pos, returns top addr of new stack
  struct stack *tmp = A;
  if(pos == 1){
    return pop(A);
  }
  int curr = 2;
  while(curr<pos &&  tmp->next!=NULL){
    curr++;
    tmp = tmp->next;
  }
  if(curr == pos && tmp->next!=NULL){
    struct stack *tmp2 = tmp->next;
    tmp->next = tmp2->next;
    free(tmp2);
  }
  return A;
}

struct stack *delete_node(struct stack *A, struct stack *node){
  if(node == A)return pop(A);

  struct stack *tmp = A;
  while(tmp->next != NULL && tmp->next != node)tmp = tmp->next;
  if(tmp->next == node){
    struct stack *tmp2 = tmp->next;
    tmp->next = tmp2->next;
    free(tmp2);
  }
  return A;
}

void delete_stack(struct stack *A){
  while(A != NULL)A = pop(A);
}
