#include<bits/stdc++.h>

using namespace std;
#define MAX_CHAR 256


struct SuffixTreeNode
{
	struct SuffixTreeNode * child[MAX_CHAR]; 
	struct SuffixTreeNode * suffixLink;
	int start;
	int *end;

	int suffixIndex;
};

typedef struct SuffixTreeNode Node;

string text;
Node *root=NULL;

Node *lastNewNode =NULL;
Node *activeNode= NULL; 

int activeEdge=-1;
int activeLength=0;

int remainingSuffixCount=0;
int leafEnd=-1;
int *rootEnd=NULL;
int *splitEnd=NULL;
int size=-1;

Node *newNode(int start,int *end)
{
	Node *node=(Node *)malloc(sizeof(Node));

	int i;
	for(i=0;i<MAX_CHAR;i++)
	{
		node->child[i]=NULL;
	}
	node->suffixLink=root;
	node->start=start;
	node->end=end;
	node->suffixIndex=-1;

	return  node;
}

int edgeLength(Node *n)
{
	return *(n->end)-(n->start)+1;
}

int walkDown(Node * node)
{
	if(activeLength>= edgeLength(node))
	{
		activeEdge+=edgeLength(node);
		activeLength-=edgeLength(node);
		activeNode=node;

		return 1;
	}
	return 0;
}
void extendSuffixTree(int pos)
{
	leafEnd=pos;

	remainingSuffixCount++;
	lastNewNode=NULL;

	while(remainingSuffixCount>0)
	{
		if(activeLength==0)
			activeEdge=pos;

		if(activeNode->child[text[activeEdge]]==NULL)
		{
			activeNode->child[text[activeEdge]]=newNode(pos,&leafEnd);
		

			if(lastNewNode!=NULL)
			{	
			lastNewNode->suffixLink=activeNode;
			lastNewNode=NULL;
			}

		}
		else
		{
			Node *next=activeNode->child[text[activeEdge]];

			if(walkDown(next))
			{
				continue;
			}

			if(text[next->start +activeLength]==text[pos])
			{
				if(lastNewNode!=NULL && activeNode!=root)
				{
					lastNewNode->suffixLink=activeNode;
					lastNewNode=NULL;
				}
				activeLength++;

				break;
			}

			splitEnd=(int *)malloc(sizeof(int));

			*splitEnd=next->start +activeLength-1;

			Node* split=newNode(next->start,splitEnd);
			activeNode->child[text[activeEdge]]=split;

			split->child[text[pos]]=newNode(pos,&leafEnd);
			next->start+=activeLength;
			split->child[text[next->start]]=next;

			if(lastNewNode!=NULL)
			{
				lastNewNode->suffixLink=split;
			}

			lastNewNode=split;

		}
		remainingSuffixCount--;

		if(activeNode==root && activeLength >0)
		{
			activeLength--;
			activeEdge=pos-remainingSuffixCount +1;
		}
		else if(activeNode!=root)
		{
			activeNode=activeNode->suffixLink;
		}

		
	}

}

void print(int i,int j)
{
	int k;
	for(k=i;k<=j;k++)
		cout<<text[k];
}

void setSuffixIndexByDFS(Node* n,int labelHeight)
{
	if(n==NULL)
		return;

	if(n->start !=-1)
	{
		print(n->start,*(n->end));
	}
	int leaf =1;
	int i;

	for(i=0;i<MAX_CHAR;i++)
	{
		if(n->child[i]!=NULL)
		{
			if(leaf==1 && n->start!=-1)
				cout<<"{"<<n->suffixIndex<<"}"<<endl;

			leaf=0;
			setSuffixIndexByDFS(n->child[i] ,labelHeight+edgeLength(n->child[i]));
		}
	}
	if(leaf==1)
	{
		n->suffixIndex=size -labelHeight;
		cout<<"{"<<n->suffixIndex<<"}"<<endl;
	}
}

void freeSuffixTreeByPostOrder(Node* n)
{
	if (n == NULL)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->child[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->child[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}
void buildSuffixTree()
{
	size=text.length();

	int i;
	rootEnd =(int *)malloc(sizeof(int ));
	*rootEnd=-1;

	root=newNode(-1,rootEnd);

	activeNode=root;
	for(i=0;i<size;i++)
		extendSuffixTree(i);

	int labelHeight = 0;
	setSuffixIndexByDFS(root,labelHeight);

	freeSuffixTreeByPostOrder(root);
}

int main()
{
	text="abcabxabcd!";

	buildSuffixTree();
	return 0;

}