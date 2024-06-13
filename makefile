# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Wextra

# Diretórios
SUBDIRS = grasp ils

# Lista de arquivos fonte e objeto
SOURCES = $(wildcard *.cpp)
UTILS_SOURCES = $(wildcard utils/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o) $(UTILS_SOURCES:.cpp=.o)

# Nome do executável
EXECUTABLE = main

# Regra padrão para compilar os objetos
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

.PHONY: all clean $(SUBDIRS)