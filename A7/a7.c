#include<stdio.h>
#include<stdlib.h>
struct set_node{	//creating a structure.
	int val;
	int rank;
	struct set_node* parent;
};
struct set_node* representative(struct set_node* set,int n)
{					//This function returns representative node pointer.
	struct set_node* temp;
	if(n>set[0].val)
		return NULL;
	else
	{
		temp=set[n].parent;
		while(temp!=temp->parent)
			temp=temp->parent;
	}
	return temp;
}
int find_link(struct set_node* set,int f,int n)
{					//Finds if both the elements belong to a common set or not,by using their representative node.
	int t1,t2;
	if(f>set[0].val || n>set[0].val)
		return -1;
	else
	{
		t1=representative(set,f)->val;
		t2=representative(set,n)->val;
	}
	if(t1==t2)
		return 1;
	else
		return 0;
}
void union_set(struct set_node* set,int f,int n)
{					//does union between two sets by updating parent pointer.
	struct set_node* t1=representative(set,f);
	struct set_node* t2=representative(set,n);
	if(f>set[0].val || n>set[0].val || t1==t2)
		return;
	else if(t1->rank==t2->rank || t1->rank>t2->rank)
	{
		t2->parent=t1;
		if(t1->rank==t2->rank)
			t1->rank++;
	}
	else if(t1->rank<t2->rank)
		t1->parent=t2;
	return;
}
int main()
{
	int flag=0;
	int num=0;
	int count=0;
	char digit;
	int elements=0;
	int f=0;
	struct set_node* set;
	while(1)
	{
		digit=fgetc(stdin);
		if(digit == EOF)
			break;	
		if(digit=='N' && count==0)
		{
			flag=1;
			if(elements!=0)
				free(set);
		}
		if(digit=='?' && count==0)
			flag=2;
		if(digit=='S' && count==0)
			flag=3;
		if(digit=='U' && count==0)
			flag=4;
		if(digit=='R' && count==0)
			flag=5;
		/*if(digit=='P')
		{
			for(int i=0;i<=elements;i++)
				printf("%d %d %p\n",set[i].val,set[i].rank,set[i].parent);
		}*/
		if(digit=='\n')
		{
			if(count == 0)
				continue;
			if(flag==1)
			{
				elements=num;
				set=(struct set_node*)malloc((elements+1)*sizeof(struct set_node));
				set[0].val=elements;
				for(int i=1;i<=elements;i++)
				{		//initialization.
					set[i].parent=&set[i];
					set[i].val=i;
					set[i].rank=1;
				}
			}
			if(flag==2)
			{	
				int t=find_link(set,f,num);
				printf("%d\n",t);
			}
			if(flag==3)
			{	
				struct set_node* t=representative(set,num);
				if(t!=NULL)
					printf("%d\n",t->val);
				else
					printf("-1\n");
			}
			if(flag==4)
				union_set(set,f,num);
			if(flag==5)
			{
				if(num>elements)
					printf("-1\n");
				else
					printf("%d\n",set[num].rank);
			}
			count=0;
			num=0,f=0;
		}
		if(digit==' ')
		{			//strores first num.
			if((flag==2 || flag==4) && count!=0)
				f=num;
			num=0;
			count++;
		}
		if(digit>='0' && digit<='9')
		{			//builds num.
			num=num*10+(digit-'0');
			count++;
		}
	}
	free(set);
	return 0;
}