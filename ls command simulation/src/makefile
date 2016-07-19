
all: static shared

static: staticlibmyls mylsstatic

staticlibmyls: myls.o
	ar rcs libmyls.a myls.o
	mv -f libmyls.a ../lib

mylsstatic: main
	gcc -Bstatic -L../lib -o myls_static main.o -lmyls
	mv myls_static ../bin 


shared: sharedlibmyls myls

sharedlibmyls: myls.o
	gcc -shared  -o libmyls.so myls.o
	mv -f libmyls.so ../lib

myls.o:
	gcc -c -o myls.o myls.c


myls:	main
	gcc -L../lib -o myls main.o -lmyls
	chmod a+x myls
	mv myls ../bin
main:
	gcc -Wall -c main.c -o main.o

clean:
	rm -f *.o ../lib/*.a ../lib/*.so ../bin/myls ../bin/myls_static


