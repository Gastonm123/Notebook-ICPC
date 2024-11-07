vector<int> g[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth
void dfs1(int x){
	wg[x]=1;
	for(int y:g[x])if(y!=dad[x]){
		dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
		wg[x]+=wg[y];
	}
}
int curpos,pos[MAXN],head[MAXN];
void hld(int x, int c){
	if(c<0)c=x;
	pos[x]=curpos++;head[x]=c;
	int mx=-1;
	for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
	if(mx>=0)hld(mx,c);
	for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
}
void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
int query(int x, int y, RMQ& rmq){
	int r=neutro; //neutro del rmq
	while(head[x]!=head[y]){
		if(dep[head[x]]>dep[head[y]])swap(x,y);
		r=oper(r,rmq.get(pos[head[y]],pos[y]+1));
		y=dad[head[y]];
	}
	if(dep[x]>dep[y])swap(x,y); // now x is lca
	r=oper(r,rmq.get(pos[x],pos[y]+1));
	return r;
}
// hacer una vez al principio hld_init() después de armar el grafo en g
// para querys pasar los dos nodos del camino y un stree que tiene en pos[x] el valor del nodo x
// for updating: rmq.set(pos[x],v);
// queries on edges: - assign values of edges to "child" node () ***
//                   - change pos[x] to pos[x]+1 in query (line 28)
// *** if(dep[u] > dep[v]) rmq.upd(pos[u], w) para cada arista (u,v)