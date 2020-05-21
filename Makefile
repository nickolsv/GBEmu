SOURCE = ./src/cpu.cpp ./src/memory.cpp ./src/ops.cpp ./src/registers.cpp
TEST = ./tests/registertests.cpp
OUT = gbEMU
TESTOUT = gbTEST
CC  = g++


$(OUT): $(SOURCE) ./src/debugmain.cpp
	$(CC) $(SOURCE) -o $@ -lm

test: $(SOURCE) $(TEST)
	$(CC) $(SOURCE) $(TEST) -o $(TESTOUT) -lm

clean:
	rm -f $(OUT)
	rm -f $(TESTOUT)