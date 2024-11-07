ll Cat(int n){
    return ((F[2*n] *FI[n+1])%M *FI[n])%M;
}