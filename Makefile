CC = g++
CFLAGS = -O6 -Wall -pedantic `curl-config --cflags`
LIBS = `curl-config --libs` -lboost_program_options -lboost_date_time -lpthread -lrt
DEPENDFILE = Makefile.Dep
OBJECTS = Main.o Curl.o String.o PreCode.o Err.o Cache.o MassLog.o MassErrLog.o File.o Entry.o Survey.o NumCode.o

all: bkoder

bkoder: $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o bkoder

%.o: %.cpp $(DEPENDFILE)
	$(CC) -c $(CFLAGS) $<

dep:
	$(CC) $(CFLAGS) -MM *.cpp > $(DEPENDFILE)

Run: all
	./bkoder

-include $(DEPENDFILE)
