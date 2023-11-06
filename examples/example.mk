# copyright Michael J. Hennebry

C++C=c++
C++FLAGS=--std=c++20   # seems to be necessary for g++

run: dot
	./dot

dot: $(SRC)/dot.cc $(SRC)/../wide_temporaries.hh
	$(C++C) -o $@ -I$(SRC)/.. $(C++FLAGS) $^

syntax: $(SRC)/syntax.cc $(SRC)/../wide_temporaries.hh
	$(C++C) -o $@ -I$(SRC)/.. $(C++FLAGS) $^
