ES_SOURCES = $(wildcard */*.strl)
CC = C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc
LIB = ../lib
libpacemaker.c: $(ES_SOURCES)
	esterel $(ES_SOURCES) -B libpacemaker

simul.c: $(ES_SOURCES)
	esterel -simul $(ES_SOURCES) -B simul

simul: simul.c simul.h
	$(CC) simul.c -L $(LIB) -lcsimul