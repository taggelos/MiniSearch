CPP = g++ -Wall -Wextra -Wconversion -g
OUT = minisearch
DATA = document.txt
SOURCE = main.cpp functions.cpp postingList.cpp letterList.cpp
OBJS = main.o functions.o postingList.o letterList.o

all: $(OBJS)
	$(CPP) $(OBJS) -o $(OUT)

$(OBJS): $(SOURCE) $(HEADER)
	$(CPP) -c $(SOURCE)

run:
	./$(OUT) -i $(DATA)

val: 
	valgrind -v --leak-check=full --show-leak-kinds=all ./$(OUT) -i $(DATA)

clean:
	rm -f $(OBJS) $(OUT)