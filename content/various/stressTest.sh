# mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

N=${1:-100}
g++ -O2 A.cpp -o m || exit 1
g++ -O2 brute.cpp -o b || exit 1
g++ -O2 gen.cpp -o g || exit 1
for ((i=1;i<=N;i++)); do
  ./g "$i" > test
  ./m < test > o1
  ./b < test > o2
  cmp -s o1 o2 || { echo "Mismatch on test $i"; exit 1; }
  echo "done test $i"
done
