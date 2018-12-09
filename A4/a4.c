/*  -> The bst accepts long long integers 
	-> All queries N,S,P,+,-,<,> are supported
	-> In case of deletion , if the node to be deleted has 2 children , it is replaced by it's inorder succesor
	-> All constructed trees are destroyed(freed) after use i.e There are no memory leaks . This has been
	   checked using valgrind
*/	
#include<stdio.h>
#include<stdlib.h>

/* parent pointers are also stored , because it is used in determining succesor/predecessor */
struct node{
	long long int data;
	struct node* left;
	struct node* right;
	struct node* parent;
};
/* creates a node for tree */
struct node* createnode(long long int n)
{
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->data=n;
	p->left=NULL;
	p->right=NULL;
	p->parent=NULL;
	return p;
}
/* insert a number into bst */
struct node* insertbst(struct node* root,long long int n)
{
	if(root==NULL)
		return createnode(n);
	if(root->data>n)
	{
		struct node* lc=insertbst(root->left,n);
		root->left=lc;
		lc->parent=root;
	}
	if(root->data<n)
	{
		struct node* rc=insertbst(root->right,n);
		root->right=rc;
		rc->parent=root;
	}
	return root;
}
/* preorder traversal of bst*/
void preorder(struct node* root)
{
	//printf("hi");
	if(root==NULL)
		return;
	printf("%lld ",root->data);
	preorder(root->left);
	preorder(root->right);
}
/* determines if a given number is present in a bst */
struct node* search(struct node* root,long long int n)
{
	if(root==NULL)
		return NULL;
	if(root->data==n)
		return root;
	if(root->data<n)
		return search(root->right,n);
	if(root->data>n)
		return search(root->left,n);
}
/* this function returns the path of a number in a bst */
struct node* searchbst(struct node* root,long long int n)
{
	if(search(root,n)!=NULL)
	{
		if(root->data==n)
			return root;
		if(root->data<n)
		{
			printf("1");
			return searchbst(root->right,n);
		}
		if(root->data>n)
		{
			printf("0");
			return searchbst(root->left,n);
		}
	}
	printf("-1");
}
/* minimum value in a bst */
struct node* min(struct node* root)
{
	if(root==NULL)
		return NULL;
	while(root->left!=NULL)
		root = root->left;
	return root;
}
/* inorder succesor in a bst */
struct node* successor(struct node* root)
{
	if(root == NULL)
		return NULL;
	/* if right subtree exists , return the minimum value in it */
	if(root->right != NULL)
		return min(root->right);
	/* if not , look for an ancestor whose left subtree consists of our node */
	struct node* temp = root;
	while(temp!=NULL && temp->parent!=NULL && temp->parent->left != temp)
		temp = temp->parent;
	/* if no succesor exists , return a node with value -1 */
	if(temp->parent == NULL)
		return createnode(-1);
	return temp->parent;
}
/* maximum value in a tree */
struct node* max(struct node* root)
{
	if(root==NULL)
		return NULL;
	while(root->right!=NULL)
		root = root->right;
	return root;	
}
/* inorder predecessor in a bst */
struct node* predecessor(struct node* root)
{
	if(root == NULL)
		return NULL;
	/* if left subtree exists , return maximum value in it */
	if(root->left != NULL)
		return max(root->left);
	/* if not , look for an ancestor whose right subtree consists of our node */
	struct node* temp = root;
	while(temp!=NULL && temp->parent!=NULL && temp->parent->right != temp)
		temp = temp->parent;
	/* if no predecessor exists , return a node with value -1 */
	if(temp->parent == NULL)
		return createnode(-1);
	return temp->parent;
}
/* deletion of a value from bst */
struct node* deletebst(struct node* root,long long int num)
{
	if(root==NULL)
		return root;
	if(num < root->data)
	{
		root->left = deletebst(root->left,num);
		return root;
	}
	if(num > root->data)
	{
		root->right = deletebst(root->right,num);
		return root;
	}
	/* This is where actual deletion happens */
	if(num == root->data)
	{
	
		//If the node to be deleted is a leaf , simply delete it
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			return NULL;
		}
		//If the node to be deleted has just one child , just pass the child up to the function that invoked the current function
		if(root->left == NULL)
		{
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		if(root->right == NULL)
		{
			struct node* temp = root->left;
			free(root);
			return temp;
		}
		// In case of two children , replace root with the inorder successor(minimum of right tree here , since right tree obviously exists)
		struct node* successor_node = min(root->right);
		root->data = successor_node->data;
		root->right = deletebst(root->right,successor_node->data);
		return root;
	}
}
/* procedure to free the entire tree */
void free_tree(struct node* root)
{
	if(root==NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	return;
}
struct node* uncle(struct node* temp)
{
	if(temp->parent==NULL)
		return NULL;
	else
	{
		temp=temp->parent;
		if(temp->parent!=NULL)
		{	
			if(temp->data<temp->parent->data)
			{
				if(temp->parent->right!=NULL)
					return temp->parent->right;
				else
					return NULL;
			}
			if(temp->data>temp->parent->data)
			{
				if(temp->parent->left!=NULL)
					return temp->parent->left;
				else
					return NULL;
			}	
		}
		else
			return NULL;
	}
}
struct node* leftrotate(struct node* root,struct node* x)
{//left rotating about x
	if(x->right!=NULL)
	{
		struct node* y=x->right;
		x->right=y->left;
		if(y->left!=NULL)
			y->left->parent=x;
		y->parent=x->parent;
		if(x->parent==NULL)
			root=y;
		else if(x==x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
		y->left=x;
		x->parent=y;
	}
	return root;
}
struct node* rightrotate(struct node* root,struct node* x)
{//right rotating about x
	if(x->left!=NULL)
	{
		struct node* y=x->left;
		x->left=y->right;
		if(y->right!=NULL)
			y->right->parent=x;
		y->parent=x->parent;
		if(x->parent==NULL)
			root=y;
		else if(x==x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
		y->right=x;
		x->parent=y;
	}
	return root;
}
int main()
{
	int flag;
	long long int num=0;
	int count=0;
	char digit;
	struct node* root=NULL;
	// handling input character by character until EOF is observed
	while(1)
	{
		digit=fgetc(stdin);
		if(digit == EOF)
			break;
		if((digit=='B' || digit=='N') && count==0)
		{	
			flag=1;
			//freeing the previous tree
			free_tree(root);
			root=NULL;
		}
		if(digit=='S' && count==0)
			flag=2;
		if(digit=='P' && count==0)
		{
			preorder(root);
			printf("\n");
			char extra_newline = fgetc(stdin);	
			continue;
		}
		if(digit=='>' && count==0)
			flag=3;
		if(digit=='<' && count==0)
			flag=6;
		if(digit=='+' && count==0)
			flag=4;
		if(digit=='-' && count==0)
			flag=5;
		if(digit=='C' && count==0)
			flag=7;
		if(digit=='U' && count==0)
			flag=8;
		if(digit=='L' && count==0)
			flag=9;
		if(digit=='R' && count==0)
			flag=10;
		if(digit=='\n')
		{
			//In case , you see an empty line .. continue.
			if(count == 0)
				continue;
			count = 0;
			if(flag==1)
			 	root=insertbst(root,num);	
			if(flag==4)
				root=insertbst(root,num);
			if(flag==5)
				root=deletebst(root,num);
			if(flag==3)
			{
				struct node* temp = search(root,num);
				if(temp!=NULL)
					printf("%lld",successor(temp)->data);
				else
				{
					root = insertbst(root,num);
					temp = search(root,num);
					printf("%lld",successor(temp)->data);
					root = deletebst(root,num);
				}

				printf("\n");
			}
			if(flag==6)
			{
				struct node* temp = search(root,num);
				if(temp!=NULL)
					printf("%lld",predecessor(temp)->data);
				else
				{
					root = insertbst(root,num);
					temp = search(root,num);
					printf("%lld",predecessor(temp)->data);
					root = deletebst(root,num);
				}
				printf("\n");
			}
			if(flag==2)
			{	
				if(root->data!=num)
					searchbst(root,num);
				printf("\n");	
			}
			if(flag==7)
			{
				struct node* t=search(root,num);
				if(t==NULL)
					printf("-1\n");
				else
				{
					if(t->left==NULL)
						printf("NIL ");
					else
						printf("%lld ",t->left->data);
					if(t->right==NULL)
						printf("NIL");
					else
						printf("%lld",t->right->data);
					printf("\n");
				}
			}	
			if(flag==8)
			{
				struct node* temp=search(root,num);
				if(uncle(temp)!=NULL)
					printf("%lld\n",uncle(temp)->data);
				else
					printf("-1\n");
			}
			if(flag==9)
			{
				struct node* temp=search(root,num);
				root=leftrotate(root,temp);
			}
			if(flag==10)
			{
				struct node* temp=search(root,num);
				root=rightrotate(root,temp);
			}
			num = 0;
		}
		if(digit==' ')
		{
			if(count>=1 && num!=0)
			{
				root=insertbst(root,num);
				num=0;
			}
			count++;
		}
		if(digit>='0' && digit<='9')
		{
			count++;
			num=num*10+(digit-'0');
		}
	}
	free_tree(root);
}