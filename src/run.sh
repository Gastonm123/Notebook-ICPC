clear
make -s $1 &&
for CASE in ./cases/$1/*; do
    ./$1 < $CASE
done
