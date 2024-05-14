# C preprocessor settings
CPPFLAGS = $(INCLUDES) -MMD -MP

# compiler & flags
cxx = g++
cxxflags = -std=c++20 -Wall -I"include" -I"include/sdl2" -I"include/headers"

# libs
libpath = -L"lib"
libs = -l"mingw32" -l"SDL2main" -l"SDL2" -l"SDL2_image" -l"SDL2_ttf"

# src & output
src = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
output = bin/game.exe

all: $(output)

$(output): $(src)
	@echo "Building executable: $@"
	@mkdir -p $(@D)
	$(cxx) $(cxxflags) $(libpath) -o $@ $^ $(libs)

run: $(output)
	@echo "Starting game..."
	@./$(output)

clean:
	@echo "Bin directory cleaned!"
	@rm -rf $(output)