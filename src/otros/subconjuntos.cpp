// iterar por mascaras O(2^n)
for(int bm=0; bm<(1<<n); bm++)
// subconjuntos de una mascara O(2^n)
for(int sbm=bm; sbm; sbm=(sbm-1)&bm)
// iterar por submascaras O(3^n)
for(int bm=0; bm<(1<<n); bm++)
    for(int sbm=bm; sbm; sbm=(sbm-1)&(bm))
// para superconjuntos (que contienen a bm),
// negar la mascara: bm=~bm