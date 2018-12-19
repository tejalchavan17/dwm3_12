#include<stdio.h>
#include<math.h>
void cluster(int n,int k,int x[],int mx[],int y[],int my[],int k1[]);
void mean(int n,int k,int k1[],int x[],int y[],int mx[],int my[]);
void print(int k,int mx[],int my[]);
int flag=0,c=0;
void main()
{
	int k,x[20],y[20],i,n,mx[20],my[20],k1[20],msg=1;
	printf("\nEnter no. of input values:");
	scanf("%d",&n);
	printf("\nEnter no. of cluster(k):");
	scanf("%d",&k);
	if(k>n)
	{
		msg=0;
		printf("\nNo. of cluster are greater then no. of input values");
	}
	if(msg==1)
	{
		for(i=0;i<n;i++)
			k1[i]=-1;
		printf("\nEnter x co-ordinates of data set:");
		for(i=0;i<n;i++)
			scanf("%d",&x[i]);
		printf("\nEnter y co-ordinates of data set:");
		for(i=0;i<n;i++)
			scanf("%d",&y[i]);
		printf("\nEnter x co-ordinate mean from data set:");
		for(i=0;i<k;i++)
			scanf("%d",&mx[i]);
		printf("\nEnter y co-ordinate mean from data set:");
		for(i=0;i<k;i++)
			scanf("%d",&my[i]);
		cluster(n,k,x,mx,y,my,k1);
	}	
}
void cluster(int n,int k,int x[],int mx[],int y[],int my[],int k1[])
{
	int i,small,a,xd,xsd,yd,ysd,xy,dxy,fk,j;
	printf("\nIteration %d:",c++);
	for(i=0;i<n;i++)
	{
		small=999;
		/*Calculating Distance*/
		for(a=0;a<k;a++)
		{
			xd=abs(x[i]-mx[a]);
			xsd=xd*xd;
			yd=abs(y[i]-my[a]);
			ysd=yd*yd;
			xy=xsd+ysd;
			dxy=sqrt(xy);
			if(dxy<small)
			{
				small=dxy;
				fk=a;
			}
		}
		if(k1[i]!=fk)
		{
			k1[i]=fk;
			flag=1;
		}
	}
	/*Print cluster*/
	for(i=0;i<k;i++)
	{
		printf("\nCluster %d:\t",i);
		for(j=0;j<n;j++)
		{
			if(k1[j]==i)
				printf("(%d,%d)\t",x[j],y[j]);
		}
	}
	/*If cluster are not same*/
	if(flag==1)
	{
		flag=0;
		mean(n,k,k1,x,y,mx,my);
	}
}
void mean(int n,int k,int k1[],int x[],int y[],int mx[],int my[])
{
	int t,count,xsum,ysum,i,xmean,ymean;
	/*Calculating mean*/
	for(t=0;t<k;t++)
	{
		count=0,xsum=0,ysum=0;
		for(i=0;i<n;i++)
		{
			if(k1[i]==t)
			{
				xsum=xsum+x[i];
				ysum=ysum+y[i];
				count++;
			}
		}
		xmean=xsum/count;
		ymean=ysum/count;
		mx[t]=xmean;
		my[t]=ymean;
	}
	print(k,mx,my);
	cluster(n,k,x,mx,y,my,k1);
}	
void print(int k,int mx[],int my[])
{
	int i,m=0;
	for(i=0;i<k;i++)
		printf("\nMean %d:(%d,%d)",m++,mx[i],my[i]);
	printf("\n");
}		

/* 
tejal@ubuntu:~/Desktop$ gcc dwm2.c -lm
tejal@ubuntu:~/Desktop$ ./a.out

Enter no. of input values:8

Enter no. of cluster(k):3

Enter x co-ordinates of data set:2 1 10 1 3 11 4 12

Enter y co-ordinates of data set:2 14 7 11 4 8 3 9

Enter x co-ordinate mean from data set:2 1 4

Enter y co-ordinate mean from data set:2 14 3

Iteration 0:
Cluster 0:	(2,2)	
Cluster 1:	(1,14)	(1,11)	
Cluster 2:	(10,7)	(3,4)	(11,8)	(4,3)	(12,9)	
Mean 0:(2,2)
Mean 1:(1,12)
Mean 2:(8,6)

Iteration 1:
Cluster 0:	(2,2)	(3,4)	(4,3)	
Cluster 1:	(1,14)	(1,11)	
Cluster 2:	(10,7)	(11,8)	(12,9)	
Mean 0:(3,3)
Mean 1:(1,12)
Mean 2:(11,8)

Iteration 2:
Cluster 0:	(2,2)	(3,4)	(4,3)	
Cluster 1:	(1,14)	(1,11)	
Cluster 2:	(10,7)	(11,8)	(12,9)	



tejal@ubuntu:~/Desktop$ gcc dwm2.c -lm
tejal@ubuntu:~/Desktop$ ./a.out

Enter no. of input values:5

Enter no. of cluster(k):6

No. of cluster are greater then no. of input values
*/
