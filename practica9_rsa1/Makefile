# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -std=c++2a -Wall

# Nombre del ejecutable
TARGET = implementacioncifradoRSA

# Lista de archivos fuente
SRCS = main.cc rsa.cc 

# Lista de archivos objeto generados a partir de los archivos fuente
OBJS = $(SRCS:.cc=.o)

.PHONY: all clean

# Regla por defecto: compilar el ejecutable
all: $(TARGET)

# Regla de compilación del ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Regla de compilación de archivos objeto
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJS) $(TARGET)
