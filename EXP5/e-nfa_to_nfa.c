#include<stdio.h>
#include<stdlib.h>
#define epsilon 'e'

int MAX_STATE = 0;
int MAX_TRANS = 0;
int MAX_ALPHA = 0;

struct transit{
	char symbol;
	int	dest;
	struct transit* next;
};

struct state{
	struct transit* head;
};


void memory_cleaner(struct state AUTOMATA[]){
	//cleaning the memory
	struct transit *temp;
	for(int state_no=0; state_no<MAX_STATE; state_no++){
		while(AUTOMATA[state_no].head != NULL){
			temp = AUTOMATA[state_no].head;
			AUTOMATA[state_no].head = temp->next;
			free(temp);
		}
	}
}

void eclosure(struct state AUTOMATA[], int fromState, int visited[]){
	//finding eclosure

	if(visited[fromState]==1){// Already visited!
		return ;
	}
	visited[fromState] = 1;

	// Looking transitions
	struct transit *T = AUTOMATA[fromState].head;
	while(T != NULL){
		if(T->symbol==epsilon){
			eclosure(AUTOMATA, T->dest, visited);
		}
		T = T->next;
	}
}

void print_set(int arr[], int size){
	printf("{ ");
	for(int i = 0;i<size;i++)
		if(arr[i]==1)printf("%d ",i);
	printf("}");
}

void delta(struct state AUTOMATA[], int subState, char alpha, int travel[]){
	struct transit *T = AUTOMATA[subState].head;
	for(;T!=NULL;T=T->next){
		if(T->symbol == alpha){
			travel[T->dest]= 1;
		}
	}
}

void union_set(int main[], int sub[]){
	for(int i = 0; i<MAX_STATE;i++){
		if(sub[i] == 1)main[i] = 1;
	}
}

void main(){

	char symbol;
	int src, dest;
	struct transit* temp;
	int state_no, trans_no, alpha_no;

	printf("Enter the number of states:");
	scanf("%d",&MAX_STATE);

	//Create automata to hold ENFA
	struct state ENFA[MAX_STATE];
	for(state_no=0;state_no<MAX_STATE;state_no++)
		ENFA[state_no].head = NULL;

	printf("Enter the number of alphabets :");
	scanf("%d",&MAX_ALPHA);

	//saving alpha..
	char SYMBOLS[MAX_ALPHA];
	for(alpha_no=0;alpha_no<MAX_ALPHA;alpha_no++){
		printf("\t Enter alpha %d : ",alpha_no+1);
		scanf(" %c",&SYMBOLS[alpha_no]);
	}

	printf("Enter the number of transistions:");
	scanf(" %d",&MAX_TRANS);


	for(int trans_no=0;trans_no<MAX_TRANS;trans_no++){
		printf("Enter the transition %d : ",trans_no+1);
		scanf(" %d %c %d",&src, &symbol, &dest);

		temp = malloc(sizeof(struct transit));
		temp->dest   	 = dest;
		temp->symbol 	 = symbol;
		temp->next  	 = ENFA[src].head;
		ENFA[src].head = temp;
	}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	int fromClosure[MAX_STATE];
	int toClosure[MAX_STATE];
	int travel[MAX_STATE];
	int main_travel[MAX_STATE];

	for(state_no=0;state_no<MAX_STATE;state_no++){

		//mark all as not visited
		for(int s=0;s<MAX_STATE;s++){
			fromClosure[s]=0;
			toClosure[s]=0;
		}

		//eclosure of fromState
		eclosure(ENFA,state_no,fromClosure);

		for(alpha_no=0;alpha_no<MAX_ALPHA;alpha_no++){
			if(SYMBOLS[alpha_no]=='e')continue;

			for(int i=0;i<MAX_STATE;i++)main_travel[i]=0;

			for(int subState_no=0;subState_no<MAX_STATE;subState_no++){
				if(fromClosure[subState_no]==0)continue;

				for(int i=0;i<MAX_STATE;i++)travel[i]=0;
				delta(ENFA, subState_no,SYMBOLS[alpha_no],travel);

				union_set(main_travel,travel);
			}

			for(int subState_no=0;subState_no<MAX_STATE;subState_no++){
				if(main_travel[subState_no]==0)continue;

				for(int i=0;i<MAX_STATE;i++)travel[i]=0;
				eclosure(ENFA,subState_no,travel);
				union_set(toClosure,travel);
			}
			print_set(fromClosure,MAX_STATE);
			printf(" %c ",SYMBOLS[alpha_no]);
			print_set(toClosure,MAX_STATE);
			printf("\n");
		}

	}
	memory_cleaner(ENFA);
}
