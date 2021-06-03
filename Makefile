CC 			= gcc
CFLAGS 		= -Wall
CPPFLAGS 	= -std=c++0x
CINCLUDES 	= -I src/ -I dependencies/GLEW/include/ -I dependencies/GLFW/include/ -I dependencies/GLM/include/ -I dependencies/SOIL2/include/
LDFLAGS 	= -L. -lglfw3 -lglew32 -lopengl32 -lstdc++
CPPSOURCES	= main.cpp src/utils/loader.cpp
CSOURCES	=
CPPDEPS		= dependencies/GLM/include/glm/detail/glm.cpp
CDEPS	 	= dependencies/SOIL2/include/SOIL2.c dependencies/SOIL2/include/image_DXT.c \
				dependencies/SOIL2/include/image_helper.c dependencies/SOIL2/include/wfETC.c
COBJECTS	= $(patsubst %.c, %.o, $(CSOURCES)) $(patsubst %.c, %.o, $(CDEPS)) 
CPPOBJECTS	= $(patsubst %.cpp, %.o, $(CPPSOURCES)) $(patsubst %.cpp, %.o, $(CPPDEPS)) 
TARGET		= BilliardsGame.exe

all: $(TARGET) clean

# Build objects from C sources
$(COBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< $(LDFLAGS) -o $@

# Build objects from CPP sources
$(CPPOBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< $(LDFLAGS) $(CINCLUDES) -o $@

# Make executable
$(TARGET): $(COBJECTS) $(CPPOBJECTS)
	$(CC) -o $@ $^ $(CINCLUDES) $(LDFLAGS)

# Clean object files when done
clean:
	rm $(COBJECTS) $(CPPOBJECTS)