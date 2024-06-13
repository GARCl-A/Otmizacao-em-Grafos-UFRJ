# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Wextra

# Lista de arquivos fonte e objeto
SOURCES = $(wildcard *.cpp) $(wildcard ../utils/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
EXECUTABLE = main

# Regra padrão para compilar os objetos
all: $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para linkar os objetos e criar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) -lstdc++

# Limpeza dos arquivos objeto e executável
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean