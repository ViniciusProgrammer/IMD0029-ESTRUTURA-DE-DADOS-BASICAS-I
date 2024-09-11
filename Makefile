# Variáveis
CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS =

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Lista de arquivos-fonte
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Nome do executável
TARGET = $(BINDIR)/app

# Regras
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Regra para compilar os arquivos-objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
