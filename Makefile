RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

.PHONY: all build clean clear server client

BIN_DIR = bin
BUILD_DIR = build
SERVER_DIR = server
CLIENT_DIR = client
KEY_DIR = key

all: server client

build:
	@echo "$(BLUE)Create Key...$(RESET)"
	@xxd -r -p key/key > key/key.bin
	@echo '.data' > key/key.s
	@echo '.global _key_bin' >> key/key.s
	@echo '.org 0x20001000' >> key/key.s
	@echo '_key_bin:' >> key/key.s
	@echo '  .space 128 - (.-_key_bin)' >> key/key.s
	@echo '  .incbin "key/key.bin"' >> key/key.s
	@as -arch arm64 -mmacosx-version-min=10.14 -o key/key_tmp.o key/key.s
	@objcopy --strip-unneeded key/key_tmp.o key/key.o

	@echo "$(BLUE)Creating directories...$(RESET)"
	@mkdir -p $(SERVER_DIR)/$(BUILD_DIR) $(CLIENT_DIR)/$(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@echo "$(BLUE)Running cmake for server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && cmake ..
	@echo "$(BLUE)Running cmake for client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && cmake ..

	@echo "$(BLUE)Building server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && $(MAKE)
	@echo "$(BLUE)Building client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && $(MAKE)

	@echo "$(GREEN)Creating symbolic links...$(RESET)"
	@ln -sf ../$(SERVER_DIR)/$(BIN_DIR)/CryptoMadness_Server $(BIN_DIR)/CryptoMadness_Server
	@ln -sf ../$(CLIENT_DIR)/$(BIN_DIR)/CryptoMadness_Client $(BIN_DIR)/CryptoMadness_Client

server:
	@echo "$(BLUE)Building server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && $(MAKE)
	@echo "$(GREEN)Creating server symbolic link...$(RESET)"
	@ln -sf ../$(SERVER_DIR)/$(BIN_DIR)/CryptoMadness_Server $(BIN_DIR)/CryptoMadness_Server

client:
	@echo "$(BLUE)Building client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && $(MAKE)
	@echo "$(GREEN)Creating client symbolic link...$(RESET)"
	@ln -sf ../$(CLIENT_DIR)/$(BIN_DIR)/CryptoMadness_Client $(BIN_DIR)/CryptoMadness_Client

clear:
	@echo "$(YELLOW)Clearing files in bin directories...$(RESET)"
	@rm -rf $(SERVER_DIR)/$(BIN_DIR)/* $(CLIENT_DIR)/$(BIN_DIR)/*
	@rm -rf $(BIN_DIR)/*
	@rm $(KEY_DIR)/key.s $(KEY_DIR)/key_tmp.o $(KEY_DIR)/key.o $(KEY_DIR)/key.bin

clean:
	@echo "$(RED)Cleaning build and bin directories...$(RESET)"
	@rm -rf $(SERVER_DIR)/$(BUILD_DIR) $(CLIENT_DIR)/$(BUILD_DIR)
	@rm -rf $(SERVER_DIR)/$(BIN_DIR) $(CLIENT_DIR)/$(BIN_DIR)
	@rm -rf $(BIN_DIR)
	@rm $(KEY_DIR)/key.s $(KEY_DIR)/key_tmp.o $(KEY_DIR)/key.o $(KEY_DIR)/key.bin