// GROUP:   5
// ID:      20150311
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Joseph Atef Saad Ayad
// UVA Username: joseph_j97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComputeKnapsack1(int N, int W);
int T1[1001][31];
int Knapsack1(int n, int w)
{
    {
        if(n==0)
            return 0;
        if(T1[n][w]>=0)
            return T1[n][w];
        int ret = ComputeKnapsack1(n-1,w);
        int cv = a[n-1].v, cw = a[n-1].w;
        if(cw<=w)
        {
            int r = ComputeKnapsack1(n-1,w-cw)+cv;
            if(r>ret)
                ret=r;
        }
        T1[n][w] = ret;
        return ret;
    }
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for(int i=0 ;i<1001;i++)
    {
        for(int j=0;j<31;j++)
        {
            T1[i][j]--;
        }
    }
    return Knapsack1(N,W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int i=0;i<1001;i++)
        for(int j=0;j<31;j++)
            T2[i][j]--;

    int ret;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=W;j++)
        {
            if(i==0)
            {
                T2[N][W]=0;
                continue;
            }
            ret = T2[N-1][W];
            int cv = a[N-1].v, cw = a[N-1].w;
            if(cw<=W)
            {
                int r = cv + T2[N-1][W-cw];
                if(r>ret)
                    ret=r;
            }
            T2[N][W]=ret;
        }
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W)// Bottom-up, use two rows only
{
    for(int i=0;i<2;i++)
        for(int j=0;j<31;j++)
            T3[i][j]--;
    int cur=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<W;j++)
        {
            if(i==0)
            {
                T3[N][W]=0;
                continue;
            }
            T3[N][W]=T3[N-1][W];
            int cv = a[i-1].v, cw = a[i-1].w;
            if(cw<=j)
            {
                int r = cv + T3[1-cur][j-cw];
                if(r>T3[cur][j])
                    T3[cur][j] = r;
            }
        }
        cur = 1-cur;
    }
    return T3[1-cur][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for (int i=0;i<31;i++)
        T4[i]--;

    for(int i=0;i<=N;i++)
    {
        for(int j=W;j>=0;j--)
        {
            if(i==0)
            {
                T4[j]=0;
                continue;
            }
            int cv = a[i-1].v, cw = a[i-1].w;
            if(cw<= j)
            {
                int r = cv+T4[j-cw];
                if(r>T4[j])
                    T4[j]=r;
            }
        }
    }
    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int T,ind=0,res;
    cin>>T;
    int *arr = new int [T];
    while(ind<T)
    {
        int *weight;
        res=0;
        int x,G;
        cin>>x;
        for(int i=0;i<x;i++)
            cin>>a[i].v>>a[i].w;
        cin>>G;
        weight = new int[G];
        for(int i=0;i<G;i++)
        {
            cin>>weight[i];
            res+=ComputeKnapsack(x,weight[i]);
        }
        arr[ind]=res;
        ind++;
        delete[]weight;
    }
    for(int i=0;i<T;i++)
    {
        cout<< arr[i]<<endl;
    }
    delete[]arr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
