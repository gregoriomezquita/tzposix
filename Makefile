tzposix: Makefile tzposix.c library/zonedetect.c
	gcc -o tzposix tzposix.c -Wall -Ilibrary library/zonedetect.c -lm

demo: Makefile demo.c library/zonedetect.c
	gcc -o demo demo.c -Wall -Ilibrary library/zonedetect.c -lm
	
simple: Makefile simple.c library/zonedetect.c
	gcc -o simple simple.c -Wall -Ilibrary library/zonedetect.c -lm
	

