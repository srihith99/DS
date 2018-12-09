#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct list_node{// List_node stores adjencency list pointer of a vertice.
	int val;
	int w;
	struct list_node* next;
};
struct graph_node{//I created V no of graph_nodes to implement graph.
	int parent;
	struct list_node* head;
	struct list_node* tail;
};
struct dijsktra_node{
	int index;
	int d;
};
void free_list(struct list_node* head)
{
	if(head==NULL)
		return;
	free_list(head->next);
	free(head);
}
void free_graph(struct graph_node* graph,int v)
{
	int i=1;
	while(i<=v)
	{
		free_list(graph[i].head);
		i++;
	}
	free(graph);
}
void swap(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void swapnode(struct dijsktra_node* a,struct dijsktra_node* b)
{
	struct dijsktra_node t=*a;
	*a=*b;
	*b=t;
}
void heapify(struct dijsktra_node* a,int n,int* position,int v)
{
	if(n==1)
		return;
	if(a[n/2].d>a[n].d)
	{
		swap(&position[a[n].index],&position[a[n/2].index]);
		swapnode(&a[n],&a[n/2]);
	}
	heapify(a,n/2,position,v);
}
void tbheapify(struct dijsktra_node* a,int n,int v,int* position)
{
	if(n>=v)
		return;
	int s=n;
    if (2*n<=v && a[2*n].d<a[n].d)
        s=2*n;
    if (2*n+1<=v && a[2*n+1].d<a[s].d)
        s=2*n+1;
    if (s!=n) 
    {
       	swap(&position[a[n].index],&position[a[s].index]);
       	swapnode(&a[n],&a[s]);
        tbheapify(a,s,v,position);
    } 
}
void buildheap(struct dijsktra_node* a,int v,int* position)
{
	for(int i=v/2;i>=1;i--)
		tbheapify(a,i,v,position);
}
struct dijsktra_node extractmin(struct dijsktra_node* a,int* v,int* position)
{
	swap(&position[a[1].index],&position[a[*v].index]);
	struct dijsktra_node temp =a[1];
	swapnode(&a[1],&a[*v]);
	*v=*v-1;
	tbheapify(a,1,*v,position);
	return temp;
}
void decreasekey(struct dijsktra_node* a,int i,int s,int* position,int v)
{
	a[i].d=s;
	heapify(a,i,position,v);
	return;
}
void insertIntoList(struct list_node** head,struct list_node** tail,int b,int m)
{//basic linked list insertion.
	struct list_node* p = (struct list_node*)malloc(sizeof(struct list_node));
	p->val = b;
	p->w=m;
	p->next = NULL;
	if(*head == NULL)
	{
		*head = p;
		*tail = p;
		return;
	}
	(*tail)->next = p;
	*tail = p;
	return;
}
void displayEdgeList(struct list_node* head)
{//to check the output.
	while(head != NULL)
	{
		printf("->%d",head->val);
		printf("(%d)",head->w);
		head = head->next;
	}
	printf("\n");
	return;
}
int findweight(struct list_node* head,int n)
{
	if(head==NULL)
		return -1;
	while(head!=NULL && head->val!=n)
		head=head->next;
	if(head!=NULL)
		return head->w;
	else
		return -1;
}
void clearGraphData(struct graph_node* graph,int v)
{
	for(int i=1;i<=v;i++)
	{
		graph[i].parent = 0;
	}
	return;
}
int* dijsktra(struct graph_node* graph,int n,int v,int flag,int d)
{ 	
	int p=v;
	struct dijsktra_node* a;
	free(a);
	a = (struct dijsktra_node*)malloc((v+1)*sizeof(struct dijsktra_node));
	int position[v+1];
	graph[n].parent=-1;
	for(int i=1;i<=v;i++)
	{
		a[i].index=i;
		a[i].d=INT_MAX;
		if(a[i].index==n)
			a[i].d=0;
		position[i]=i;
	}
	buildheap(a,v,position);
	while(v>0)
	{
		struct dijsktra_node t=extractmin(a,&v,position);
		if(flag==0 && t.d!=INT_MAX)
			printf("%d %d\n",t.index,t.d);
		if(flag==0 && t.d==INT_MAX)
			printf("%d -1\n",t.index);
		struct list_node* temp=graph[t.index].head;
		while(temp!=NULL)
		{
			if(a[position[temp->val]].d > temp->w+t.d)
			{
				a[position[temp->val]].d=temp->w+t.d;
				if(flag==1)
					graph[temp->val].parent=t.index;
				decreasekey(a,position[temp->val],a[position[temp->val]].d,position,v);
			}
			temp=temp->next;
		}
	}
	int* b=(int*)malloc((p+1)*sizeof(int));
	for(int i=1;i<=p;i++)
		b[i]=a[position[i]].d;
	return b;
}
void shortestpath(struct graph_node* graph,int f,int d,int v,int flag)
{
	int* b;
	int a[v];
	if(f==d)
	{
		printf("0 %d\n",f);
	return;
	}
	if(flag!=0)
	 	b=dijsktra(graph,f,v,1,d);
	if(graph[d].parent == 0)
	{
		printf("-1\n");
		return;
	}
	int temp = d;
	int i=0;
	while(temp != 0 && temp != -1)	
	{
		a[i]=temp;
		temp=graph[temp].parent;
		i++;
	}
	printf("%d ",b[d]);
	for(int j=i-1;j>=0;j--)
		printf("%d ",a[j]);
	printf("\n");
}
int main()
{
	int flag=0;
	int num=0;
	int count=0;
	char digit;
	int vertex_count=0;
	int first_space_flag = 1;
	int f=0,t=0,m=0,r=0;
	int node1=0;
	struct graph_node* graph;
	while(1)
	{
		digit=fgetc(stdin);
		if(digit == EOF)
			break;	
		if(digit=='N' && count==0)
		{
			flag=1;	
		}
		if(digit=='E' && count==0)
			flag=2;
		if(digit=='?' && count==0)
			flag=3;
		if(digit=='D' && count==0)
			flag=4;
		if(digit=='P' && count==0)
			flag=5;
		if(digit=='S')
		{
			for(int i=1;i<=vertex_count;i++)
			{
				printf("%d : ",i);
				displayEdgeList(graph[i].head);
			}
			printf("\n");
		}
		if(digit=='\n')
		{
			if(count == 0)
				continue;
			if(flag==1)
			{
				vertex_count = num;
				graph = (struct graph_node*)malloc( (vertex_count+1)*sizeof(struct graph_node));
				for(int i=1;i<=vertex_count;i++)
				{
					graph[i].parent = 0;
					graph[i].head = NULL;
					graph[i].tail = NULL;
				}
			}
			if(flag==2)
			{
				m=num;
				insertIntoList(&graph[f].head,&graph[f].tail,r,m);			
			}
			if(flag==3)
			{
				int a=findweight(graph[f].head,num);
				printf("%d\n",a);
			}
			if(flag==4)
			{
				clearGraphData(graph,vertex_count);
				dijsktra(graph,num,vertex_count,0,1);
				clearGraphData(graph,vertex_count);
			}
			if(flag==5)
			{
				if(graph[node1].parent == -1)
					shortestpath(graph,f,num,vertex_count,0);
				else
				{
					clearGraphData(graph,vertex_count);
					shortestpath(graph,f,num,vertex_count,1);
				}
			}
			count=0;
			num=0;
			t=0,r=0,f=0;
			first_space_flag = 1;
		}
		if(digit==' ')
		{
			t++;
			if((flag==2 || flag==3 || flag==5) && count!=0)
			{		
				if(first_space_flag == 1)
				{
					f = num;
					first_space_flag = 0;
				}
				else if(t>=4 && t%2==0)
				{ 	
					m=num;
					insertIntoList(&graph[f].head,&graph[f].tail,r,m);
				}
				else if(t>=3 && t%2==1)
					r=num;
			}
			if(flag==5 && count !=0)
				node1=num;
			num=0;
			count++;
		}
		if(digit>='0' && digit<='9')
		{			
			num=num*10+(digit-'0');
			count++;
		}
	}
	free_graph(graph,vertex_count);
}