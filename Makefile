HIGHREADER_BIN := bdhighreader.bin

all : $(HIGHREADER_BIN)

$(HIGHREADER_BIN) : bdhighreader.cc
	$(CXX) -o $@ $^

test :
	./$(HIGHREADER_BIN) test_heroes.prg

