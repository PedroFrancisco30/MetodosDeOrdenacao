# Compilador e flags
GO = /usr/local/go/bin/go
BINARY = app
SRC_DIR = .

# Compila o projeto gerando um executável
all:
	$(GO) build -o $(BINARY) $(SRC_DIR)

# Roda o executável gerado
run:
	./$(BINARY)

# Remove o executável gerado
clean:
	rm -f $(BINARY)