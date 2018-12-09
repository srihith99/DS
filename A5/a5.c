#include<stdio.h>
#include<stdlib.h>
struct list_node{// List_node stores adjencency list pointer of a vertice.
	int val;
	struct list_node* next;
};
struct graph_node{//I created V no of graph_nodes to implement graph.
	int colour;
	int parent;
	struct list_node* head;
	struct list_node* tail;
};
void insertIntoList(struct list_node** head,struct list_node** tail,int b)
{//basic linked list insertion.
	struct list_node* p = (struct list_node*)malloc(sizeof(struct list_node));
	p->val = b;
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

int deleteHead(struct list_node** head)
{//Dequeue's the queue.
	if(*head == NULL)
		return -1;
	int answer = (*head)->val;
	struct list_node* temp = (*head)->next;
	free(*head);
	*head = temp;
	return answer;
}

void displayEdgeList(struct list_node* head)
{//to check the output.
	while(head != NULL)
	{
		printf("->%d",head->val);
		head = head->next;
	}
	printf("\n");
	return;
}
int findedge(struct list_node* head,int b)
{//finds if there is edge between two given queries.
	while(head!=NULL)
	{
		if(head->val==b)
			return 1;
		head=head->next;
	}
	return 0;
}

void BFS(struct graph_node *graph,int b)
{//does breadth first search on a source node b.
	struct list_node *queue_head=NULL,*queue_tail=NULL;
	graph[b].colour = 1;//here by colour 1 i mean grey.
	insertIntoList(&queue_head,&queue_tail,b);
	while(queue_head != NULL)
	{	
		int current = deleteHead(&queue_head);
		printf("%d ",current);
		struct list_node* temp = graph[current].head;
		while(temp != NULL)
		{
			int child = temp->val;
			if(graph[child].colour==0)//here by colour 0 i mean white.
			{
				graph[child].colour = 1;
				insertIntoList(&queue_head,&queue_tail,child);
			}
			temp = temp->next;
		}
		graph[current].colour = 2;////here by colour 2 i mean black.
	}
	printf("\n");
	return;
}

void buildShortestPath(struct graph_node *graph,int b)
{//here parent linkage is nothing but neighbour next to it in queue.
	struct list_node *queue_head=NULL,*queue_tail=NULL;
	graph[b].parent = -1;
	graph[b].colour = 1;
	insertIntoList(&queue_head,&queue_tail,b);

	
	while(queue_head != NULL)
	{	
		int current = deleteHead(&queue_head);
		struct list_node* temp = graph[current].head;
		while(temp != NULL)
		{
			int child = temp->val;
			if(graph[child].colour==0)
			{
				graph[child].colour = 1;
				graph[child].parent = current;
				insertIntoList(&queue_head,&queue_tail,child);
			}
			temp = temp->next;
		}
		graph[current].colour = 2;
	}
	
	return;	
}

void printShortestPath(struct graph_node* graph,int b,int n)
{
	if(graph[b].parent == 0)
	{
		printf("-1\n");
		return;
	}
	int a[n];
	int index = 0;
	int temp = b;
	while(temp != 0 && temp != -1)	
	{
		a[index] = temp;
		index++;
		temp = graph[temp].parent;
	}
	for(int i=index-1;i>=0;i--)
		printf("%d ",a[i]);
	printf("\n");
}

void clearGraphData(struct graph_node* graph,int v)
{
	for(int i=1;i<=v;i++)
	{
		graph[i].colour = 0;
		graph[i].parent = 0;
	}
	return;
}

int main()
{
	int flag=0;
	int num=0;
	int count=0;
	char digit;
	int vertex_count=0;
	int first_space_flag = 1;
	int f=0,s=0,q=0;
	int node1=0,node2=0;
	struct graph_node *graph;
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
		{	
			flag=3;
		}
		if(digit=='B' && count==0)
		{
			flag=4;
		}
		if(digit=='P' && count==0)
		{
			flag=5;
		}
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
					graph[i].colour = 0;
					graph[i].parent = 0;
					graph[i].head = NULL;
					graph[i].tail = NULL;
				}
			}
			if(flag==2)
			{
				insertIntoList(&graph[f].head,&graph[f].tail,num);			
			}
			if(flag==3)
			{
				int temp=findedge(graph[q].head,num);
				printf("%d\n",temp);
				q=0;
				s=0;
			}
			if(flag==4)
			{
				clearGraphData(graph,vertex_count);
				BFS(graph,num);
				clearGraphData(graph,vertex_count);
			}
			if(flag==5)
			{
				node2 = num;
				if(graph[node1].parent == -1)
					printShortestPath(graph,node2,vertex_count);
				else
				{
					clearGraphData(graph,vertex_count);
					buildShortestPath(graph,node1);
					printShortestPath(graph,node2,vertex_count);
				}
			}
			count=0;
			num=0;
			first_space_flag = 1;
		}
		if(digit==' ')
		{
			if(flag==2 && count!=0)
			{		
				if(first_space_flag == 1)
				{
					f = num;
					first_space_flag = 0;
				}
				else
				{ 	
					insertIntoList(&graph[f].head,&graph[f].tail,num);
				}
			}
			if(flag==3)
			{
				if(s==1)
					q=num;
				s++;
			}
			if(flag==5 && count!=0)
			{
				node1 = num;
			}

			num=0;
			count++;
		}
		if(digit>='0' && digit<='9')
		{			
			num=num*10+(digit-'0');
			count++;
		}
	}
}