cd ../qu3e/src
g++ -std=c++11 -fPIC -c `find -name '*.cpp'`
g++ -shared -o libqu3e.so `find -name '*.o'`
rm -rf *.o
mv libqu3e.so ../../lib
cd ../../lib