// GROUP:       G5
// ID:          20150311
// Assign:      02
// Assign:      DisjointSets
// UVA:         10608
// UVA handle:  joseph_j97
// Name:        Joseph Atef Saad Ayad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int [n];
        for(int i=0;i<n;i++)
        {
            parent[i] = -1;
            num_nodes[i] = 1;
        }
    }
    void Destroy()
    {
        delete[]parent;
        delete[]num_nodes;
    }
    int Find(int i)
    {
        int p=i;
        while (parent[p]!=-1)
            p=parent[p];
        return p;
    }
    bool Union(int i, int j)
    {
        int a=Find(i), b=Find(j);
        if(a==b) return false;
        if(num_nodes[a]>=num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
        }
        return true;
    }
    int FindMax()
    {
        int maxx=-1;
        for(int i=0;i<n;i++)
            maxx=max(maxx,num_nodes[i]);
        return maxx;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int t,n,m,a,b;
    DisjointSets djs;
    cin>>t;
    while (t--)
    {
        cin>>n>>m;
        djs.Initialize(n);
        for(int i=0;i<m;i++)
        {
            cin>>a>>b;
            djs.Union(a-1,b-1);
        }
        int max = djs.FindMax();
        cout<<max<<endl;
        djs.Destroy();

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
