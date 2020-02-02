tzposix: Makefile tzposix.c library/zonedetect.c
	gcc -o tzposix tzposix.c -Wall -Ilibrary library/zonedetect.c -lm

