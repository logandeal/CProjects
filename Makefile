stats : lab13.o libbasicplayer.a
	compile lab13.o -lbasicplayer -L. -o stats

lab13.o : lab13.c basicplayer.h
	compile -c lab13.c

clean:
	@rm -f *.o
	@rm -f stats
	@echo "All clean!"
