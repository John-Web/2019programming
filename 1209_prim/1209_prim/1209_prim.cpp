#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	int **cost=new int*[n];
	for(int i=0; i<n; i++)
	{
		cost[i]=new int[n];
		for(int j=0; i<n; j++)
			if(i==j)
				cost[i][j]=0;
			else
				cost[i][j]=INT_MAX;
	}
	int head,tail,_cost;
	for(int i=0; i<m; i++)
	{
		cin>>head>>tail>>_cost;
		cost[head][tail]=cost[tail][head]=_cost;
	}
	int *lowcost=new int[n];
	int *nearpoint=new int[n];
	for(int i=0; i<n; i++)
	{
		lowcost[i]=cost[0][i];
		nearpoint[i]=0;
	}
	nearpoint[0]=-1;

	for(int edge=1; edge<n; edge++)
	{

	}
	cout << "Hello World!\n"; 
}