TARGET = levchmak

CXX = g++
MKDIR = mkdir -p

CXXFLAGS = -Wall -pedantic -Wextra -std=c++14

LDFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCE_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)


.PHONY: all
all: compile doc
	@echo "Finished..."


.PHONY: compile
compile: $(TARGET)
	@echo "Compile..."


.PHONY: run
run: $(TARGET)
	./$(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@


doc: Doxyfile $(HEADERS)
	doxygen Doxyfile


.PHONY: clean
clean:
	rm -rf $(TARGET) $(TARGET).zip doc/ .archive/ $(BUILD_DIR)/ 2>/dev/null


build/Bomb.o: src/Bomb.cpp src/Bomb.h src/GameObject.h src/Vector2D.h \
 src/TextureManager.h src/ErrorHandler.h src/Game.h src/TransformObject.h
 
build/Enemy.o: src/Enemy.cpp src/Enemy.h src/GameObject.h src/TransformObject.h \
 src/Vector2D.h src/TextureManager.h src/ErrorHandler.h src/Game.h \
 src/Player.h src/KeyboardController.h src/Bomb.h src/Flame.h src/Map.h \
 src/MapObject.h src/CollisionManager.h src/Bonus.h \
 src/RandomNumberGenerator.h
 
build/EnemyGhost.o: src/EnemyGhost.cpp src/EnemyGhost.h src/Enemy.h \
 src/GameObject.h src/TransformObject.h src/Vector2D.h \
 src/TextureManager.h src/ErrorHandler.h src/Game.h src/Player.h \
 src/KeyboardController.h src/Bomb.h src/Flame.h src/Map.h \
 src/MapObject.h src/CollisionManager.h src/Bonus.h \
 src/RandomNumberGenerator.h
 
build/EnemyOvapi.o: src/EnemyOvapi.cpp src/EnemyOvapi.h src/TextureManager.h \
 src/ErrorHandler.h src/Game.h src/GameObject.h src/Vector2D.h src/Map.h \
 src/MapObject.h src/TransformObject.h src/Enemy.h src/Player.h \
 src/KeyboardController.h src/Bomb.h src/Flame.h src/CollisionManager.h \
 src/Bonus.h src/RandomNumberGenerator.h
 
build/ErrorHandler.o: src/ErrorHandler.cpp src/ErrorHandler.h

build/Game.o: src/Game.cpp src/Game.h src/GameObject.h src/ErrorHandler.h \
 src/Player.h src/TextureManager.h src/TransformObject.h src/Vector2D.h \
 src/KeyboardController.h src/Bomb.h src/Flame.h src/Map.h \
 src/MapObject.h src/CollisionManager.h src/Bonus.h \
 src/RandomNumberGenerator.h src/CircleCollision.h src/Enemy.h \
 src/EnemyOvapi.h src/EnemyGhost.h src/UiLabel.h
 
build/main.o: src/main.cpp src/Game.h src/GameObject.h src/Player.h \
 src/TextureManager.h src/ErrorHandler.h src/TransformObject.h \
 src/Vector2D.h src/KeyboardController.h src/Bomb.h src/Flame.h src/Map.h \
 src/MapObject.h src/CollisionManager.h src/Bonus.h \
 src/RandomNumberGenerator.h
 
build/Map.o: src/Map.cpp src/Map.h src/MapObject.h src/GameObject.h \
 src/TextureManager.h src/ErrorHandler.h src/Game.h
 
build/Player.o: src/Player.cpp src/Player.h src/GameObject.h \
 src/TextureManager.h src/ErrorHandler.h src/Game.h src/TransformObject.h \
 src/Vector2D.h src/KeyboardController.h src/Bomb.h src/Flame.h src/Map.h \
 src/MapObject.h src/CollisionManager.h src/Bonus.h \
 src/RandomNumberGenerator.h
 
build/TextureManager.o: src/TextureManager.cpp src/TextureManager.h \
 src/ErrorHandler.h src/Game.h src/GameObject.h src/Map.h src/MapObject.h
 
build/Vector2D.o: src/Vector2D.cpp src/Vector2D.h
