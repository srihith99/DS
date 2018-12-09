#include<stdio.h>
#include<stdlib.h>
//colour character stores R and B meaning its colored red and black respectively.
struct node{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
	char colour;
};
//frees all the memory occupied by tree.
void free_tree(struct node* root)
{
	if(root==NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	return;
}
//p1 and p2 are sentenal node's but there contain -1 instead of nil,but they serve the purpose.
struct node* createnode(int n)
{
	struct node* p1=(struct node*)malloc(sizeof(struct node));
	p1->data=-1;
	p1->left=NULL;
	p1->right=NULL;
	p1->parent=NULL;
	p1->colour='B';
	struct node* p2=(struct node*)malloc(sizeof(struct node));
	p2->data=-1;
	p2->left=NULL;
	p2->right=NULL;
	p2->parent=NULL;
	p2->colour='B';
	struct node* p=(struct node*)malloc(sizeof(struct node));
	p->data=n;
	p->left=p1;
	p->right=p2;
	p->parent=NULL;
	p->colour='R';
	return p;
}
//here I am freeing extra memory leaks too,by freeing those memory blocks that are replaced by a new node.
//normal bst insert but leaf nodes are sentenal nodes.
struct node* insertrbt(struct node* root,int n,struct node** t)
{
	if(root==NULL || root->data==-1)
	{
		*t=createnode(n);
		return *t;
	}
	if(root->data>n)
	{
		struct node* temp=root->left;
		struct node* lc=insertrbt(root->left,n,t);
		if(temp!=lc)
			free(temp);
		root->left=lc;
		lc->parent=root;
	}
	if(root->data<n)
	{
		struct node* temp=root->right;
		struct node* rc=insertrbt(root->right,n,t);
		if(temp!=rc)
			free(temp);
		root->right=rc;
		rc->parent=root;
	}
	return root;
}
// returns uncle pointer.
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
//left rotating about x
struct node* leftrotate(struct node* root,struct node* x)
{
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
//right rotating about x
struct node* rightrotate(struct node* root,struct node* x)
{
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
// recolours a pointer's colour.
void recolour(struct node* temp)
{
	if(temp->colour=='R')
		temp->colour='B';
	else
		temp->colour='R';
	return;
}
//balences the tree after every insertion using redblack tree properties.
struct node* fix_insert(struct node* root,struct node* temp)
{
	while(temp!=NULL && temp->parent!=NULL && temp->parent->colour!='B')
	{
		struct node* t=uncle(temp);
		if(t== NULL)
			break;
		if(t->colour=='R')
		{
			t->colour='B';
			recolour(temp->parent);
			recolour(temp->parent->parent);
			temp=temp->parent->parent;
		}		
		else if(temp->parent->data < temp->parent->parent->data)
		{
			if(temp->data > temp->parent->data)
			{	
				temp=temp->parent;
				root=leftrotate(root,temp);
			}
			else
			{
				recolour(temp->parent);
				recolour(temp->parent->parent);
				root=rightrotate(root,temp->parent->parent);
			}
		}
		else
		{
			if(temp->data < temp->parent->data)
			{	
				temp=temp->parent;
				root=rightrotate(root,temp);	
			}
			else
			{
				recolour(temp->parent);
				recolour(temp->parent->parent);
				root=leftrotate(root,temp->parent->parent);
			}
		}
	}
	root->colour='B';
	return root;
}
//prints preorder traversal.
void preorder(struct node* root)
{
	if(root==NULL || root->data==-1)
		return;
	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
}
//returns the pointer of the element that is being searched.
struct node* search(struct node* root,int n)
{
	if(root==NULL || root->data==-1)
		return NULL;
	if(root->data==n)
		return root;
	if(root->data<n)
		return search(root->right,n);
	if(root->data>n)
		return search(root->left,n);
}
//prints the entire 
struct node* searchrbt(struct node* root,int n)
{
	if(root->data==n)
		return root;
	if(root->data<n)
	{
		printf("1");
		return searchrbt(root->right,n);
	}
	if(root->data>n)
	{
		printf("0");
		return searchrbt(root->left,n);
	}
	printf("-1");
	return NULL;
}

//returns min value pointer in a tree.
struct node* min(struct node* root)
{
	if(root->data==-1)
		return NULL;
	while(root->left->data!=-1)
		root = root->left;
	return root;
}
// returns max value pointer in a tree.
struct node* max(struct node* root)
{
	if(root->data==-1)
		return NULL;
	while(root->right->data!=-1)
		root = root->right;
	return root;	
}
// returns the inorder successor to a given element.
struct node* successor(struct node* root)
{
	if(root == NULL)
		return NULL;
	/* if right subtree exists , return the minimum value in it */
	if(root->right->data!=-1)
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
// returns the inorder predecessor to a given element.
struct node* predecessor(struct node* root)
{
	if(root == NULL)
		return NULL;
	/* if left subtree exists , return maximum value in it */
	if(root->left->data!=-1)
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

struct node* fix_delete(struct node* root,struct node* r)
{
	struct node* temp=NULL;
	while(r!=root && r->colour=='B')
	{
		if(r==r->parent->left)
		{
			temp=r->parent->right;
			if(temp->colour=='R')//sibling of r is red.
			{
				temp->colour='B';
				r->parent->colour='R';
				root = leftrotate(root,r->parent);
				temp=r->parent->right;
			}
			if(temp->left->colour=='B' && temp->right->colour=='B')
			{//sibling of r is black and its children are black(temp).
				temp->colour='R';
				r=r->parent;
			}
			else if(temp->right->colour=='B')
			{//sibling of r is black(temp).temp left child is red and right child is black.
				temp->left->colour='B';
				temp->colour='R';
				root = rightrotate(root,temp);
				temp=r->parent->right;
			}
			else
			{ //temp is black ,its right child is red.
				temp->colour=r->parent->colour;
				r->parent->colour='B';
				temp->right->colour='B';
				root = leftrotate(root,r->parent);
				r=root;
			}
		}
		else
		{//left and right are reversed in above logic.
			temp=r->parent->left;
			if(temp->colour=='R')
			{
				temp->colour='B';
				r->parent->colour='R';
				root = rightrotate(root,r->parent);
				temp=r->parent->left;
			}
			if(temp->right->colour=='B' && temp->left->colour=='B')
			{
				temp->colour='R';
				r=r->parent;
			}
			else if(temp->left->colour=='B')
			{
				temp->right->colour='B';
				temp->colour='R';
				root = leftrotate(root,temp);
				temp=r->parent->left;
			}
			else
			{ 
				temp->colour=r->parent->colour;
				r->parent->colour='B';
				temp->left->colour='B';
				root = rightrotate(root,r->parent);
				r=root;
			}
		}
	}
	r->colour='B';
	return root;
}

struct node* shiftrbt(struct node* root,struct node*t1,struct node* t2)
{
	//replace tree rooted at t1 to tree rooted at t2.
	t2->parent=t1->parent;
	if(t1->parent==NULL)
		return root=t2;
	if(t1==t1->parent->left)
		t1->parent->left=t2;
	else
		t1->parent->right=t2;
	
	return root;
}
// In deleting I used predecessor to replace in two child case.
struct node* deleterbt(struct node* root,int num)
{//del points to the node to deleted,replace takes its place.
	struct node* temp=search(root,num);
	struct node* replace=NULL;
	struct node* del=temp;
	if(temp==NULL)
		return root;
	char c=temp->colour;
	if(temp->left->data==-1)
	{
		replace=temp->right;
		root=shiftrbt(root,temp,temp->right);
	}
	else if(temp->right->data==-1)
	{
		replace=temp->left;
		root=shiftrbt(root,temp,temp->left);
	}
	else
	{
		del=max(temp->left);
		c=del->colour;
		replace=del->left;
		if(del->parent==temp)
			replace->parent=del;
		else
		{
			root=shiftrbt(root,del,del->left);
			del->left=temp->left;
			del->left->parent=del;
		}
		root=shiftrbt(root,temp,del);
		del->right=temp->right;
		del->right->parent=del;
		del->colour=temp->colour;
	}
	if(c=='B')// if the deleted node was black fix it.
		root = fix_delete(root,replace);
	return root;
}

int main()
{
	int flag;
	int num=0;
	int count=0;
	char digit;
	struct node* root=NULL;
	struct node* t=NULL;
	// handling input character by character until EOF is observed
	while(1)
	{
		digit=fgetc(stdin);
		if(digit == EOF)
			break;
		if(digit=='N' && count==0)
		{
			flag=1;	
			free_tree(root);
			root=NULL;
		}
		if(digit=='+' && count==0)
			flag=2;
		if(digit=='>' && count==0)
			flag=3;
		if(digit=='-' && count==0)
			flag=4;
		if(digit=='P' && count==0)
		{
			preorder(root);
			printf("\n");
		}
		if(digit=='S' && count==0)
			flag=6;
		if(digit=='C' && count==0)
			flag=7;
		if(digit=='\n')
		{
			//In case , you see an empty line .. continue.
			if(count == 0)
				continue;
			if(flag==1 || flag==2)
			{
				t=root;
				root=insertrbt(root,num,&t);
				root=fix_insert(root,t);
			}
			if(flag==3)
			{
				struct node* temp=search(root,num);
				if(temp!=NULL)
					printf("%d",successor(temp)->data);
				else
				{
					root = insertrbt(root,num,&t);
					temp = search(root,num);
					printf("%d",successor(temp)->data);
					root = deleterbt(root,num);
				}
				printf("\n");
			}
			if(flag==4)
			{
				root=deleterbt(root,num);
			}
			if(flag==6)
			{
				struct node* t=search(root,num);
				if(t!=NULL)
				{
					searchrbt(root,num);
					if(t!=NULL)
					{
						printf(" %c",t->colour);
					}
				}
				else
					printf("-1");
				printf("\n");
			}
			if(flag==7)
			{
				struct node* t=search(root,num);
				if(t==NULL)
					printf("-1\n");
				else
				{
					if(t->left->data==-1)
						printf("L B ");
					else
						printf("%d %c ",t->left->data,t->left->colour);
					if(t->right->data==-1)
						printf("L B");
					else
						printf("%d %c",t->right->data,t->right->colour);
					printf("\n");
				}
			}	
			count = 0;
			num = 0;
		}
		if(digit==' ')
		{
			if(count>=1 && num!=0)
			{
				t=root;
				root=insertrbt(root,num,&t);
				root=fix_insert(root,t);
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