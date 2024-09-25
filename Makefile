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

all: build server client

build:
	@echo "$(BLUE)Create Key...$(RESET)"
	@xxd -r -p key/key > key/key.bin
	@as -arch arm64 -mmacosx-version-min=10.14 -o key/key_tmp.o key/key.s
	@objcopy --strip-unneeded key/key_tmp.o key/key.o

	@echo "$(BLUE)Move opcode.s in src/opcode ...$(RESET)"
	@cp $(SERVER_DIR)/script/opcode.s $(SERVER_DIR)/src/opcode/opcode.s
	@echo "$(BLUE)Create ObjFile Opcode: opcode.o ...$(RESET)"
	@as -arch arm64 -mmacosx-version-min=10.14 -o $(SERVER_DIR)/src/opcode/opcode.o $(SERVER_DIR)/src/opcode/opcode.s
	

	@echo "$(BLUE)Creating directories...$(RESET)"
	@mkdir -p $(SERVER_DIR)/$(BIN_DIR) $(SERVER_DIR)/$(BIN_DIR)/objects $(CLIENT_DIR)/$(BIN_DIR)
	@mkdir -p $(SERVER_DIR)/$(BUILD_DIR) $(CLIENT_DIR)/$(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

	@echo "$(BLUE)Running cmake for server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && cmake -DINCLUDE_OPCODE=ON ..
	@echo "$(BLUE)Building server...$(RESET)"
	@cd $(SERVER_DIR)/$(BUILD_DIR) && $(MAKE)
#@find $(SERVER_DIR)/$(BUILD_DIR)/CMakeFiles/CryptoMadness_Server.dir -name '*.o' -exec cp {} $(SERVER_DIR)/bin/objects/ \;

	@echo "$(BLUE)Running cmake for client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && cmake ..
	@echo "$(BLUE)Building client...$(RESET)"
	@cd $(CLIENT_DIR)/$(BUILD_DIR) && $(MAKE)

#if multiple compilation
#@echo "$(BLUE)Create Opcode: opcode.s ...$(RESET)"
#@cd $(SERVER_DIR)/script && ./linkOpCodeAddr.sh

#@echo "$(BLUE)Move opcode.s in src/opcode ...$(RESET)"
#@cp $(SERVER_DIR)/script/opcode.s $(SERVER_DIR)/src/opcode/opcode.s
#@echo "$(BLUE)Create ObjFile Opcode: opcode.o ...$(RESET)"
#@as -arch arm64 -mmacosx-version-min=10.14 -o $(SERVER_DIR)/src/opcode/opcode.o $(SERVER_DIR)/src/opcode/opcode.s

#@echo "$(BLUE)Linking OpCode and create finaly Binary...$(RESET)"
#@echo "$(BLUE)Running cmake for server...$(RESET)"
#@rm -rf $(SERVER_DIR)/$(BIN_DIR)/*
#@cd $(SERVER_DIR)/$(BUILD_DIR) && cmake -DINCLUDE_OPCODE=ON ..
#@echo "$(BLUE)Building server...$(RESET)"
#@cd $(SERVER_DIR)/$(BUILD_DIR) && $(MAKE)

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

	@echo "$(RED)Cleaning key$(RESET)"
	@rm $(KEY_DIR)/key_tmp.o $(KEY_DIR)/key.o $(KEY_DIR)/key.bin

	@echo "$(RED)Cleaning opcode$(RESET)"
#@rm server/script/opcode.s
	@rm server/src/opcode/opcode.o
#@rm server/src/opcode/opcode.s

clean:
	@echo "$(RED)Cleaning build and bin directories...$(RESET)"
	@rm -rf $(SERVER_DIR)/$(BUILD_DIR) $(CLIENT_DIR)/$(BUILD_DIR)
	@rm -rf $(SERVER_DIR)/$(BIN_DIR) $(CLIENT_DIR)/$(BIN_DIR)
	@rm -rf $(BIN_DIR)

	@echo "$(RED)Cleaning key$(RESET)"
	@rm $(KEY_DIR)/key_tmp.o $(KEY_DIR)/key.o $(KEY_DIR)/key.bin

	@echo "$(RED)Cleaning opcode$(RESET)"
#@rm server/script/opcode.s
	@rm server/src/opcode/opcode.o
#@rm server/src/opcode/opcode.s