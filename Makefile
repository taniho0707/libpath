
all:
#	g++ -std=c++11 -fPIC -I../lib/ -I../ -c libpathbasic1.cpp -o libpathbasic1.lo
#	g++ -std=c++11 -fPIC -shared -Wl,-soname,libpathbasic1.so libpathbasic1.lo -o libpathbasic1.so
#	rm *.lo
	g++ -std=c++11 -fPIC -I../lib/ -I../ -shared libpath.hpp libpathbasic1.cpp -o libpathbasic1.so

.PHONY: clean
clean:
	rm *.so
	rm *.o

