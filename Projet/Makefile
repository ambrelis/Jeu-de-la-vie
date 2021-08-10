CC=gcc
CFLAGS = -Wall -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

vpath %.h include
vpath %.o obj
vpath %.c src



OBJ= obj/
LIB= lib/
ifeq (TEXTE,$(MODE))

main_txt : lib/libjeu.a
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS) $(CPPFLAGS)
	mkdir -p bin 
	mv -f main_txt ./bin/

$(OBJ)main_txt.o: main_txt.c grille.h io_txt.h jeu.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mkdir -p obj
	mv -f *.o ./obj/

$(OBJ)%.o: %.c %.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mv -f *.o ./obj/
	
$(LIB)libjeu.a: obj/main_txt.o obj/io_txt.o obj/jeu.o obj/grille.o
	ar -crv libjeu.a obj/main.o obj/io.o obj/jeu.o obj/grille.o
	mkdir -p lib
	ranlib libjeu.a
	mv libjeu.a lib/
else
main : lib/libjeu.a
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS) $(CPPFLAGS)
	mkdir -p bin 
	mv -f main ./bin/

$(OBJ)main.o: main.c grille.h io.h jeu.h 
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mkdir -p obj
	mv -f *.o ./obj/

$(OBJ)%.o: %.c %.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mv -f *.o ./obj/
		
$(LIB)libjeu.a: obj/main.o obj/io.o obj/jeu.o obj/grille.o
	ar -crv libjeu.a obj/main.o obj/io.o obj/jeu.o obj/grille.o
	mkdir -p lib
	ranlib libjeu.a
	mv libjeu.a lib/
endif

docs:
	doxygen Doxyfile

	
dist:
	tar -cvz $^ -f LisAmbre-GoL-Version2.tar.xz src include Makefile Doxyfile

clean :
	rm -rf obj lib bin *.tar.xz doc

