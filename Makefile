CXX 			= clang++

CXXFLAGS 		= -Wall -Wextra

BISONFLAGS 		= -d

EXEC			= vsopc

SRC				= main.cpp \
				  driver.cpp \
				  parser.cpp \
				  lexer.cpp

OBJ	  			= $(SRC:.cpp=.o)

install-tools:

vsopc: $(EXEC)

main.o: driver.hpp parser.hpp ast.hpp

driver.o: driver.hpp parser.hpp ast.hpp

parser.o: driver.hpp parser.hpp ast.hpp

lexer.o: driver.hpp parser.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ)

parser.cpp: vsop.y
	bison $(BISONFLAGS) -o parser.cpp $^

parser.hpp: vsop.y
	bison $(BISONFLAGS) -o parser.cpp $^

lexer.cpp: vsop.lex
	flex $(LEXFLAGS) -o lexer.cpp $^

clean:
	@rm -f $(EXEC)
	@rm -f $(OBJ)
	@rm -f lexer.cpp
	@rm -f parser.cpp parser.hpp location.hh

.PHONY: clean
