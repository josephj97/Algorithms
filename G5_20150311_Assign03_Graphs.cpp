// GROUP:       G5
// ID:          20150311
// Assign:      03
// Assign:      Graphs
// UVA handle:  joseph_j97
// UVA:         924
// Name:        Joseph Atef Saad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value *arr;

    void Initialize() {
        sz = 1;
        n = 0;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value *new_arr = new Value[sz];
            for (int i = 0; i < n; i++)
                new_arr[i] = arr[i];
            delete[]arr;
            arr = new_arr;
        }
        arr[n++] = v;
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

struct Node
{
    //Array that contains the adjacent nodes.
    Array<int> adj;

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

template <class Type>
struct Queue {
    int f, n;
    Type *elems;

    void Initialize(int size) {
        f = 0;
        n = 0;
        elems = new Type[size];
    }

    void Destroy() {
        delete[] elems;
    }

    void Add(Type t)
    {
        elems[n++] = t;
    }
    Type Pop()
    {
        Type temp = elems[f];
        f++;
        return temp;
    }
    Type Peek()
    {
        return elems[f];
    }
    int Num()
    {
        return n-f;
    }
};
void BFS(Graph& g, int s)
{
    Queue<int> q;
    q.Initialize(g.n);
    int* vis = new int [g.n];
    int* dst = new int [g.n];
    int* pre = new int [g.n];
    memset(vis, 0, (sizeof(int)*g.n));
    memset(pre, -1, (sizeof(int)*g.n));
    for(int i=0;i<g.n;i++)
        dst[i]=g.n;

    vis[s]=1;
    dst[s]=0;
    q.Add(s);
    int boomsize=0,boomday=0,max=-1,d=0;
    while(q.Num())
    {
        d++;
        int cur=q.Pop();
        for(int i=0;i<g.nodes[cur].adj.n;i++)
        {
            int x=g.nodes[cur].adj[i];
            if(!vis[x])
            {
                boomsize++;
                vis[x]=1;
                pre[x]=cur;
                dst[x]=dst[cur]+1;
                q.Add(x);
            }
        }
        if(max<boomsize)
        {
            max=boomsize;
            boomday=d;
        }
    }
    cout<<boomsize<<" "<<boomday<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Graph g;
    int E,T,x,n,y;
    cin>>E;
    g.Initialize(E);
    for(int i=0;i<E;i++)
    {
        cin>>x;
        for(int j=0;j<x;j++)
        {
            cin>>n;
            g.nodes->adj.AddLast(n);
        }
    }
    cin>>T;
    for(int i=0;i<T;i++)
    {
        cin >> y;
        BFS(g,y);
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
