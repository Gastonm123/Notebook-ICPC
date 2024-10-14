#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class Key,class Val=null_type>using htable=gp_hash_table<Key,Val>;
// como unordered_map (o unordered_set si Val es vacio), pero sin metodo count