unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
mt19937 generator(seed);
generator(); // generar un número aleatorio entre 0 y 4294967295
// existe mt19937_64 para la versión de 64 bits, que probablemente sea más rápido

/*
// también se puede hacer lo siguiente para una versión hasta 3x más rápida:
#include <ext/random>
using namespace __gnu_cxx;
unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
sfmt19937 generator(seed); // existe también sfmt19937_64
*/

uniform_int_distribution<ll> dist_int(L, R);
dist_int(generator); // generar un entero en [L, R] (cerrado-cerrado) con prob uniforme

uniform_real_distribution<double> dist_real(0.0, 1.0);
dist_real(generator); // generar un real en [0, 1) (cerrado-abierto) con prob uniforme
