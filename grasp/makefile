# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Wextra

# Lista de arquivos fonte e objeto
SOURCES = main.cpp grasp_constructive.cpp local_search.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão para compilar os objetos
all: $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos objeto
clean:
	rm -f $(OBJECTS)

.PHONY: all clean