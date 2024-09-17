.PHONY: all build clean

BUILD_DIR = build

all:
	cd $(BUILD_DIR) && make

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f ./bin/CryptoMadness