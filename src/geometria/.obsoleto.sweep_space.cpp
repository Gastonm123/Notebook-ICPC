void sweep_space() {
    vector<Event> eventos; // puntos, segmentos, ...
    sort(eventos);         // sort por x, y, ...
    set<Info> estado;      // mantener la informacion ordenada
    // Estado estado;     // agregar o quitar segmentos y calcular algo
    forn(i, sz(eventos)) {
        Event &e = eventos[i];
        process(e, estado); // procesar un evento cambia el estado
        ans = actualizar(ans);
} }