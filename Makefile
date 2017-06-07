libpathbasic1 := libpathbasic1.hpp libpathbasic1.cpp
libpathbasic2 := libpathbasic2.hpp libpathbasic2.cpp

all: $(libpathbasic1) $(libpathbasic2)
#	g++ -std=c++11 -fPIC -I../lib/ -I../ -c libpathbasic1.cpp -o libpathbasic1.lo
#	g++ -std=c++11 -fPIC -shared -Wl,-soname,libpathbasic1.so libpathbasic1.lo -o libpathbasic1.so
#	rm *.lo
	g++ -std=c++11 -DDEBUG_PRINTF -fPIC -I../lib/ -I../ -shared $(libpathbasic1) -o libpathbasic1.so
	g++ -std=c++11 -DDEBUG_PRINTF -fPIC -I../lib/ -I../ -shared $(libpathbasic2) -o libpathbasic2.so

release: $(libpathbasic1) $(libpathbasic2)
	g++ -std=c++11 -fPIC -I../lib/ -I../ -shared $(libpathbasic1) -o libpathbasic1.so
	g++ -std=c++11 -fPIC -I../lib/ -I../ -shared $(libpathbasic2) -o libpathbasic2.so

.PHONY: clean
clean:
	rm -f *.so
	rm -f *.o

