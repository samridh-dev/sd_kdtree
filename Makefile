CXX_COMPILER       = icpx
BUILD_DIR          = cmake/build
BUILD_TEST_DIR     = cmake/build_test
BIN_DIR            = bin
EXECUTABLE         = main
CMAKE_BUILD_TYPE   = Debug

ifdef fname
        TEST_ARG = -DTEST_ONLY=$(fname)
else
        TEST_ARG =
endif

.PHONY: all
all: $(BUILD_DIR)/Makefile
	@echo "Building project (tests disabled)..."
	cd $(BUILD_DIR) && cmake --build .

$(BUILD_DIR)/Makefile:
	@echo "Configuring main build (tests OFF)..."
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake \
	        -DBUILD_TESTS=OFF \
	        -DCMAKE_CXX_COMPILER=$(shell command -v $(CXX_COMPILER)) \
	        -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ../..

.PHONY: fast
fast: clean
	$(MAKE) CMAKE_BUILD_TYPE=Release all

.PHONY: run
run: all
	@echo "Running executable..."
	./$(BIN_DIR)/$(EXECUTABLE)

.PHONY: test
test: $(BUILD_TEST_DIR)/Makefile
	@echo "Building tests..."
	cd $(BUILD_TEST_DIR) && cmake --build .
	@echo "Running tests..."
	cd $(BUILD_TEST_DIR) && ctest --output-on-failure

$(BUILD_TEST_DIR)/Makefile:
	@echo "Configuring test build (tests ON)..."
	mkdir -p $(BUILD_TEST_DIR)
	cd $(BUILD_TEST_DIR) && cmake \
	        -DBUILD_TESTS=ON \
	        -DCMAKE_CXX_COMPILER=$(shell command -v $(CXX_COMPILER)) \
	        -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
	        $(TEST_ARG) ../..

.PHONY: clean
clean:
	@echo "Cleaning build directories and binaries..."
	rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR)
	find $(BIN_DIR) -type f -delete

.PHONY: rebuild
rebuild: clean all

.PHONY: rebuild_fast
rebuild_fast: clean fast.
