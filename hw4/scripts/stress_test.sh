cd $(dirname $0)/..

cmake . && make

tr -dc A-Za-z0-9 < /dev/urandom | head -c 104857600 > ./test.txt

# dd if=/dev/urandom of=test.bin bs=100M count=1 iflag=fullblock

./count_sequential ./test.txt abcdeXYZ > ./sequential.txt && \
./count_parallel   ./test.txt abcdeXYZ > ./parallel.txt && \
cmp ./sequential.txt ./parallel.txt
exit $?
