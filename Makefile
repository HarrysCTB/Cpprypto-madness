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

all: server client

build:
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
	@ln -sf ../$(SERVER_DIR)/$(BUILD_DIR)/CryptoMadness_Server $(BIN_DIR)/CryptoMadness_Server
	@ln -sf ../$(CLIENT_DIR)/$(BUILD_DIR)/CryptoMadness_Client $(BIN_DIR)/CryptoMadness_Client

server:
	@echo "$(BLUE)Building server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && $(MAKE)
	@echo "$(GREEN)Creating server symbolic link...$(RESET)"
	@ln -sf ../$(SERVER_DIR)/$(BUILD_DIR)/CryptoMadness_Server $(BIN_DIR)/CryptoMadness_Server

client:
	@echo "$(BLUE)Building client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && $(MAKE)
	@echo "$(GREEN)Creating client symbolic link...$(RESET)"
	@ln -sf ../$(CLIENT_DIR)/$(BUILD_DIR)/CryptoMadness_Client $(BIN_DIR)/CryptoMadness_Client

clear:
	@echo "$(YELLOW)Clearing files in bin directories...$(RESET)"
	@rm -rf $(SERVER_DIR)/$(BIN_DIR)/* $(CLIENT_DIR)/$(BIN_DIR)/*
	@rm -rf $(BIN_DIR)/*

clean:
	@echo "$(RED)Cleaning build and bin directories...$(RESET)"
	@rm -rf $(SERVER_DIR)/$(BUILD_DIR) $(CLIENT_DIR)/$(BUILD_DIR)
	@rm -rf $(SERVER_DIR)/$(BIN_DIR) $(CLIENT_DIR)/$(BIN_DIR)
	@rm -rf $(BIN_DIR)