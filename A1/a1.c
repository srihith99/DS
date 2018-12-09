#include<stdio.h>
#include<stdlib.h>

//Circular DLL was implemented to add large numbers .
//This was chosen because the lists need to be traversed in reverse for efficient addition and circular DLL allows for that flexibilty 
//Error Handling was done as well

//list node
struct node{
	char data;
	struct node* next;
	struct node* prev;
};

// A number consists of the list and the list length
struct number{
	struct node* sentinel;
	int length;
};


//returns a new node
struct node* createnode(char n)
{
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->data=n;
	p->next=NULL;
	p->prev=NULL;
	return p;
}

//This function free's all the nodes in a circular DLL
void free_list(struct node* sentinel)
{
	struct node* head = sentinel->next;
	while(head != sentinel)
	{
		struct node* temp = head->next;
		free(head);
		head = temp;
	}
	free(sentinel);
	return;
}

//This creates a new number , or resets the number to nothing (it does so by freeing the previous list of the number)
void initialise(struct number* n1,struct number* n2)
{
	if(n1->length != 0)
		free_list(n1->sentinel);
	n1->sentinel = createnode('s');
	n1->length = 0;

	if(n2->length != 0)
		free_list(n2->sentinel);
	n2->sentinel = createnode('s');
	n2->length = 0;

	return;
}

//Insertion into a circular DLL (Insertion is done in reverse)
//Implemented with sentinel nodes
void insert(char digit,struct node* sentinel)
{
	//Check validity of individual digit . Abort in case of an anomaly
	if(digit < '0' || digit > '9')
	{
		printf("Invalid Number - Aborting Program\n");
		exit(EXIT_FAILURE);
	}
	if(sentinel->prev==NULL && sentinel->next==NULL)
	{
		struct node* p=createnode(digit);
		sentinel->prev=p;
		p->next=sentinel;
		sentinel->next=p;
		p->prev=sentinel;
		return;
	}
	struct node* p=createnode(digit);
	sentinel->next->prev=p;
	p->next=sentinel->next;
	p->prev=sentinel;
	sentinel->next=p;
	return;
}

// prints the circular DLL
void print(struct node* sentinel)
{
	struct node* head=sentinel->next;
	while(head!=sentinel)
	{
		printf("%c",head->data);
		head=head->next;
	}
	printf("\n");
}


//Adds two numbers and returns the sum_list
struct node* add(struct number n1,struct number n2)
{
	struct node* sentinel3 = createnode('s');
	//The following block ensures sentinel1 points to the bigger list
	if(n2.length > n1.length)
	{
		struct node* t = n1.sentinel;
		n1.sentinel = n2.sentinel;
		n2.sentinel = t;
	}
	struct node* head1=n1.sentinel->next;
	struct node* head2=n2.sentinel->next;
	int carry = 0;
	while(head1!=n1.sentinel)
	{
		int temp=0;
		if(head2!=n2.sentinel)
		{
			temp = head2->data - '0';
			head2 = head2->next;
		}
		int sum = ( (head1->data - '0') + temp + carry );
		carry = sum/10;
		char c = sum%10 + '0'; 
		insert(c,sentinel3);
		head1 = head1->next;
	}
	if(carry == 1)
		insert('1',sentinel3);
	return sentinel3;
	
}

int main()
{
	char digit;
	int flag=0,output_flag=0;
	struct number n1,n2;
	n1.length = 0;
	n2.length = 0;
	initialise(&n1,&n2);
	//flag controls what list is having elements insert into it (n1 or n2)
	//output_flag just ensures showing the output and freeing the previous lists
	while((digit=fgetc(stdin))!=EOF)
	{

		if(digit=='\n')
		{
			if(output_flag)
			{
				struct node* sentinel3=add(n1,n2);
				print(sentinel3);
				free_list(sentinel3);
				initialise(&n1,&n2);
				flag = 0;
			}
			output_flag = 0;
		}
		else if(digit==' ')
			flag=1;
		else
		{
			if(flag==0)
			{
				n1.length++;
				insert(digit,n1.sentinel);
			}
			else
			{
				n2.length++;
				insert(digit,n2.sentinel);
				output_flag = 1;
			}
		}
	}
	//In case there is no newline at the end of last line of input , this block ensures output is displayed even then
	if(output_flag)
	{
		struct node* sentinel3=add(n1,n2);
		print(sentinel3);
		initialise(&n1,&n2);
		free_list(sentinel3);
	}

	return 0;
}