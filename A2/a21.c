#include<stdio.h>
#include<stdlib.h>
//Linked list was implemented to compare two large numbers.
//Memory loss has been efficiently handled(checked using valgring command-bash).
//Error handling was done as well.
//List node.
struct node{
	char data;
	struct node* next;
};
//A number consists of list and list lengthes.
struct number{
	int length;
	struct node* head;
};
//Returns a new node.
struct node* createnode(char n)
{
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->data=n;
	p->next=NULL;
	return p;
}
//Insertion into a linked list.
struct node* insert(struct node* head,char n)
{
	//Check validity of individual digit . Abort in case of an anomaly
	if(n<'0' || n>'9')
	{
		printf("invalid input program aborted");
		exit(EXIT_FAILURE);
	}
	struct node* temp=head;
	if(head==NULL)
		return createnode(n);
	while((temp->next)!=NULL)
		temp=temp->next;
	struct node* p=createnode(n);
	temp->next=p;
	return head;
}
//This function free's all the nodes in a circular DLL
void free_list(struct node* head)
{
	while(head!=NULL)
	{
		struct node* temp=head->next;
		free(head);
		head=temp;
	}
	return;
}
//This creates a new number , or resets the number to nothing (it does so by freeing the previous list of the number)
void initialise(struct number* n1,struct number* n2)
{
	if(n1->length!=0)
		free_list(n1->head);
	n1->head=NULL;
	n1->length=0;
	if(n2->length!=0)
		free_list(n2->head);
	n2->head=NULL;
	n2->length=0;
	return;
}
//Compares the two given inputs that are in the form of linked lists.
int compare(struct number n1,struct number n2)
{
	int l1=0;
	int l2=0;
	while(n1.head!=NULL && ((n1.head)->data)=='0')
	{
		n1.head=n1.head->next;
		l1++;
	}
	while(n2.head!=NULL && ((n2.head)->data)=='0')
	{
		n2.head=n2.head->next;
		l2++;
	}
	if(n2.head==NULL)
	{
		return 1;
	}
	if(n1.head==NULL)
		return 0;
	if(((n1.length)-l1)>((n2.length)-l2))
		return 1;
	else if(((n1.length)-l1)==((n2.length)-l2))
	{
		while(n1.head!=NULL)
		{
			if(((n1.head)->data)>((n2.head)->data))
				return 1;
			if(((n1.head)->data)<((n2.head)->data))
				return 0;
			n1.head=n1.head->next;
			n2.head=n2.head->next;
		}
		return 1;
	}
	else
		return 0;

}
int main()
{
	struct number n1,n2;
	n1.length=0;
	n2.length=0;
	char digit;
	int flag=0;
	int outputflag=0;
	initialise(&n1,&n2);
	//flag controls what list is having elements insert into it (n1 or n2)
	//output_flag just ensures showing the output and freeing the previous lists
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='\n')
		{	
			if(outputflag)
			{
				int a=compare(n1,n2);
				printf("%d \n",a);
				initialise(&n1,&n2);
				flag=0;	
			}
			outputflag=0;
		}
		else if(digit==' ')
		 	flag=1;
		else
		{
			if(flag==0)
			{
				n1.head=insert(n1.head,digit);
				n1.length++;
			}
			else
			{
				n2.head=insert(n2.head,digit);
				n2.length++;
				outputflag=1;
			}
		}
	}
	//In case there is no newline at the end of last line of input , this block ensures output is displayed even then
	if(outputflag)
	{
		int a=compare(n1,n2);
		printf("%d",a);
		initialise(&n1,&n2);
	}
	return 0;
}