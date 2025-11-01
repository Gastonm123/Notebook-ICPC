getline(cin, linea); // tomar toda la linea
stringstream ss(linea); // tratar una linea como stream
ss >> s; ss << s; // leer solo hasta un espacio, escribir a ss
tipo n; ss >> n; // leer de un stringstream (float, int, etc.)
int pos  = s.find_first_of("aeoiu"); // devuelve -1 si no encuentra
int next = s.find_first_of("aeoiu", pos);
// s.find_first_not_of("aeoiu"); s.find_last_of();
s.substr(pos, next-pos); // substr(pos, len)
s.c_str(); // devuelve un puntero de C
ss.str(); // devuelve el string en ss
// isspace(); islower(); isupper(); isdigit(); isalpha();
// tolower(); toupper();