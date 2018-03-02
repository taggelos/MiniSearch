CPP = g++
OUT = minisearch
DATA = document.txt
SOURCE = main.cpp postingList.cpp letterList.cpp
OBJS = main.o postingList.o letterList.o

all: $(OBJS)
	$(CPP) $(OBJS) -o $(OUT)

$(OBJS): $(SOURCE) $(HEADER)
	$(CPP) -c $(SOURCE)

run:
	./$(OUT) -i $(DATA)

val: 
	valgrind -v ./$(OUT)

clean:
	rm -f $(OBJS) $(OUT)