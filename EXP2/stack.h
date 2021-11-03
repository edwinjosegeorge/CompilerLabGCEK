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
