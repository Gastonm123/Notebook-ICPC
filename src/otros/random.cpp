unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 generator(seed);
generator(); // generar un numero aleatorio entre 0 y 4294967295
default_random_engine engine;
uniform_real_distribution dist(0.0, 1.0);
dist(engine); // generar un numero entre 0 y 1 con prob uniforme