#USE POWERSHELL WITH THIS MAKEFILE

# Compiler and flags
CURL_DIR = ./curl/
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.
LDFLAGS = -L$(CURL_DIR) -lcurl

# Project files
SRC = main.cpp \
	  curlService.cpp \
	  alpacaTradingService.cpp \
	  marketDataService.cpp \
	  tradingBot.cpp \
	  thresholdStrategy.cpp
OBJ_DIR = build
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)
TARGET = trading_bot.exe

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  $(LDFLAGS)

# Include dependency files
-include $(DEPS)

# Clean build files
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(TARGET) del $(TARGET)

# Phony targets
.PHONY: all clean