// GROUP:   5
// ID:      20150311
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Joseph Atef Saad
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: joseph_j97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize()
    {
        sz=1;
        n=0;
        arr=new Value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(Value v)
    {
        if(n==sz)
        {
            sz*=2;
            Value* new_arr = new Value[sz];
            for(int i=0;i<n;i++)
                new_arr[i]=arr[i];
            delete[]arr;
            arr=new_arr;
        }
        arr[n++]=v;
    }
    void RemoveLast()
    {
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;  // id of the adjacent node
    double	w;  // edge weight = distance between the two nodes
};

struct Node
{
    int x,y; // x and y coordinates of the node
    Array<Edge> adj;

    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n=_n;
        nodes = new Node[n];
        for(int i=0;i<n;i++)
            nodes[i].Initialize();
    }
    void Destroy()
    {
        for(int i;i<n;i++)
            nodes[i].Destroy();
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double a=0,b=v,s;
    for(int i=0;i<n;i++)
    {
        s=(a+b/2);
        if(s*s<v)
            a=s;
        else
            b=s;
    }
    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n,T=1;
    int x,y,a,b;
    while(cin>>n)
    {
        if(n==0)
            return 0;
        else
        {
            Graph g;
            g.Initialize(n);
            for(int i=0;i<n;i++)
            {
                cin>>x>>y;
                g.nodes[i].x=x;
                g.nodes[i].y=y;
                g.nodes[i].adj.Initialize();
            }
            for(int i=0;i<n-1;i++)
            {
                for(int j=i+1;j<n;j++)
                {
                    Edge edge;
                    x=g.nodes[i].x;
                    y=g.nodes[i].y;
                    a=g.nodes[j].x;
                    b=g.nodes[j].y;
                    edge.w=((x-a)*(x-a))+((y-b)*(y-b));
                    edge.v=i;
                    g.nodes[j].adj.AddLast(edge);
                    edge.v=j;
                    g.nodes[i].adj.AddLast(edge);
                }
            }
            int cur=0,minInd,minDist,fr=100000000;
            bool vis[n];
            int dist[n];
            memset(vis,0, sizeof(vis));
            for(int i=0;i<n;i++)
                dist[i]=100000000;
            for(int i=0;i<n;i++)
            {
                vis[cur]=1;
                minDist=100000000;
                minInd=-1;
                for(int j=0;j<g.nodes[cur].adj.n;j++)
                {
                    int k=g.nodes[cur].adj[j].v;
                    if(!vis[k])
                    {
                        if(g.nodes[cur].adj[j].w<dist[k])
                            dist[k]=g.nodes[cur].adj[j].w;
                        if(dist[k]<minDist)
                        {
                            minDist=dist[k];
                            minInd=k;
                        }
                    }
                }
                cur=minInd;
                fr=min(fr,minDist);
            }
            double output =Sqrt(fr);
            cout<<"Scenario #"<<T++<<endl;
            cout<<"Frog Distance = "<<setprecision(3)<<fixed<<output<<endl;
            for(int i=0;i<n;i++)
                g.nodes[i].adj.Destroy();
            g.Destroy();
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
