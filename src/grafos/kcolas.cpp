// utilidades para hacer bfs k-colas
// mas rapido que dijkstra cuando los pesos de las aristas son acotados
#define push(dist,args...) colas[dist%K].emplace_back(nd, args)
// todos los nodos en una misma cola estan a la misma distancia
// usar la cola actual hasta vaciarla