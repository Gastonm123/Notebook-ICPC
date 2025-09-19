const int K=9999; // en general, K = MAX_DIST+1
vector<Datos> colas[K];
int cola_actual = 0, ult_cola = -1;
// push toma la dist actual y la siguiente
#define push(d,nd,args...) colas[(cola_actual+nd-d)%K].emplace_back(nd, args)
#define pop colas[cola_actual].pop_back
#define top colas[cola_actual].back
// PUSHEAR POSICION INICIAL
for (; ; cola_actual = (cola_actual+1)%K) {
    if (ult_cola == cola) break; // dimos la vuelta
    if (colas[cola_actual].size()) ult_cola = cola;
    while (colas[cola_actual].size()) {

    }
}
