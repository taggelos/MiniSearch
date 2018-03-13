CPP = g++ -Wall -Wextra -Wconversion -g -lm
OUT = minisearch
DATA = Entertainment.txt
OBJS = main.o fileUtil.o trieUtil.o wordList.o postingList.o heap.o trie.o

$(OUT): $(OBJS)
	$(CPP) $^ -o $@

%.o: %.cpp %.h
	$(CPP) -c $<

%.o: %.cpp
	$(CPP) -c $<

run:
	./$(OUT) -i $(DATA)

val: 
	valgrind -v --leak-check=full --show-leak-kinds=all ./$(OUT) -i $(DATA)

clean:
	rm -f $(OBJS) $(OUT)
