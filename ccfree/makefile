all: lib_ccfree.a lib_ccfree.so libftp.a libftp.so

lib_ccfree.a:_ccfree.h _ccfree.cpp
	g++ -c -o lib_ccfree.a _ccfree.cpp

lib_ccfree.so:_ccfree.h _ccfree.cpp
	g++ -fPIC -shared -o lib_ccfree.so _ccfree.cpp

libftp.a:ftplib.h ftplib.c
	gcc -c -o libftp.a ftplib.c

libftp.so:ftplib.h ftplib.c
	gcc -fPIC -shared -o libftp.so ftplib.c

clean:
	rm -f lib_ccfree.a lib_ccfree.so libftp.a libftp.so
