# 編譯器和編譯選項
CXX = g++
CXXFLAGS = -march=native -flto -funroll-loops -finline-functions -ffast-math -O3 -Iinc -std=c++11

# 目標檔案和目錄
SRC_DIR = src
OBJ_DIR = obj

# 生成的可執行文件名稱
TARGET = Legalizer

# 源碼檔案和對應的物件檔案
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES:main.cpp=$(OBJ_DIR)/main.o))

# .PHONY 表示不會生成相應的檔案
.PHONY: all clean

# 默認目標，生成可執行文件
all: $(TARGET)

# 連結所有物件檔案生成可執行檔案
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# 編譯.cpp檔案到.o檔案
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 編譯 main.cpp
$(OBJ_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

# 清理生成的檔案
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# 測試指令
run16900: $(TARGET)
	./$(TARGET) testcase/testcase1_16900.lg testcase/testcase1_16900.opt output/output_16900.txt

run5000: $(TARGET)
	./$(TARGET) testcase/testcase1_ALL0_5000.lg testcase/testcase1_ALL0_5000.opt output/output_5000.txt

run100: $(TARGET)
	./$(TARGET) testcase/testcase2_100.lg testcase/testcase2_100.opt output/output_100.txt

