#include<stdio.h>
#include<stdlib.h>
//A BST capable of storing a linked list pointer is used in this code.
//This was chosen so that i can handle large numbers.
//Error handling and memory efficiency were dealt.
//List node.
struct node_list{
	char data;
	int length;
	struct node_list* next;
};
//tree node.
struct node{
	struct node_list* head;
	struct node* left;
	struct node* right;
	struct node* parent;
};
struct node_list* createnode_list(char n)
{
	struct node_list* p=(struct node_list*)malloc(sizeof(struct node_list));
	p->data=n;
	p->length=1;
	p->next=NULL;
	return p;
}
struct node* createnode(struct node_list* head)
{
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->head=head;
	p->left=NULL;
	p->right=NULL;
	return p;
}
//creates linked lists.
struct node_list* insertlist(char n,struct node_list* head)
{
	if(head==NULL)
		return createnode_list(n);
	if(head!=NULL)
	{	
		head->length=head->length+1;
		struct node_list* temp=head;
		struct node_list* p=createnode_list(n);
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=p;
	}
	return head;
}
//frees linked list memory.
void free_list(struct node_list* head)
{
	if(head==NULL)
		return;
	free_list(head->next);
	free(head);
}
//frees bst's memory.
void free_node(struct node* root)
{
	if(root==NULL)
		return;
	free_node(root->left);
	free_node(root->right);
	free_list(root->head);
	free(root);
}
//compares data in two pointers.
int compare(struct node_list* head,struct node_list* roothead)
{
	if(head==NULL && roothead!=NULL)
		return 1;
	if(head==NULL && roothead==NULL)
		return 2;
	if(roothead==NULL && head!=NULL)
		return 0;
	if(((head->length))>((roothead->length)))
		return 1;
	else if((head->length)==(roothead->length))
	{
		while(head!=NULL)
		{
			if(((head)->data)>((roothead)->data))
				return 1;
			if(((head)->data)<((roothead)->data))
				return 0;
			head=head->next;
			roothead=roothead->next;
		}
		return 2;
	}
	else
		return 0;
}
//creates bst .
struct node* insertbst(struct node_list* head,struct node* root,int* y)
{
	if(head==NULL)
		return root;
	if(root==NULL)
	{
		return createnode(head);
		*y=*y+1;
	}
	if(compare(head,root->head)==1)
	{
		struct node* rc=insertbst(head,root->right,y);
		root->right=rc;
		rc->parent=root;
	}	
	else if(compare(head,root->head)==0)
	{
		struct node* lc=insertbst(head,root->left,y);
		root->left=lc;
		lc->parent=root;
	}
	return root;
}
//prints preorder traversal.
void preorder(struct node* root,int* y)
{
	if(root==NULL)
		return;
	struct node_list* temp=root->head;
	if(temp==NULL)
		return;
	while(temp!=NULL)
	{
		printf("%c",temp->data);
		temp=temp->next;
	}
	*y--;
	if(*y!=1)
		printf(" ");
	preorder(root->left,y);
	preorder(root->right,y);
}
//searches for an element and returns its path if found else prints -1.
struct node_list* search(struct node* root,struct node_list* head,struct node_list* temp)
{
	if(root==NULL)
	{
		free_list(temp);
		struct node_list* p=(struct node_list*)malloc(sizeof(struct node_list));
		p->data='1';p->next=NULL;
		struct node_list* temp1=(struct node_list*)malloc(sizeof(struct node_list));
		temp=temp1;
		temp->data='-';
		temp->next=p;
		return temp;
	}
	if(compare(head,root->head)==2)
		return temp;
	if(compare(head,root->head)==1)
	{
		temp=insertlist('1',temp);
		return search(root->right,head,temp);
	}
	if(compare(head,root->head)==0)
	{
		temp=insertlist('0',temp);
		return search(root->left,head,temp);
	}
}
int main()
{
	int lengthbst=0;
	struct node* root=NULL;
	struct node_list* head=NULL;
	struct node_list* temp=NULL;
	char digit;
	int count=0;
	int flag=0;
	int outputflag=0;//flag controls weather to insert or search or print preorder.
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='N' && count==0)
		{
			flag=1;
			free_node(root);
			root=NULL;
		}
		if(digit=='S' && count==0)
			{
				flag=2;
			}
		if(digit=='P' && count==0)
		{
			flag=3;
			preorder(root,&lengthbst);
			continue;
		}
		if(digit=='\n')
		{
			count=0;
			if(flag==1)
			{
				root=insertbst(head,root,&lengthbst);
				head=NULL;
			}
			if(flag==2)
			{
				temp=search(root,head,temp);
				while(temp!=NULL)
				{
					printf("%c",temp->data);
					temp=temp->next;
				}
				printf("\n");
				free_list(temp);
				temp=NULL;
				free_list(head);
				head=NULL;
			}
		}//the built linked list is inserted into the bst.
		else if(digit==' ')
		{
			root=insertbst(head,root,&lengthbst);
			head=NULL;
			count++;
		}//linked list gets built here.
		else if(digit>='0' && digit<='9')
		{
			if(head==NULL && digit!='0'){
				head=insertlist(digit,head);
				count++;
			}
			else if(head!=NULL){
				head=insertlist(digit,head);
				count++;
			}
		}
	}
	free_node(root);
return 0;
}
