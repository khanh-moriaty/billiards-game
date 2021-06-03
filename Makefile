CC 				= gcc
CFLAGS 			= -w
CPPFLAGS 		= -std=c++0x -DGLEW_NO_GLU -DGLEW_STATIC -DGLEW_BUILD -O2
CINCLUDES 		= -I src/ -I dependencies/GLEW/include/ -I dependencies/GLFW/include/ -I dependencies/GLM/include/ -I dependencies/SOIL2/include/
LDFLAGS 		= -L. -lglfw3 -lopengl32 -lstdc++ -lglu32 -lgdi32 -luser32 -lkernel32

CPPSOURCES		= main.cpp src/utils/loader.cpp
CSOURCES		=
CPPDEPS			= dependencies/GLM/include/glm/detail/glm.cpp
CDEPS	 		= dependencies/SOIL2/include/SOIL2.c dependencies/SOIL2/include/image_DXT.c \
					dependencies/SOIL2/include/image_helper.c dependencies/SOIL2/include/wfETC.c
COBJECTS		= $(patsubst %.c, %.o, $(CSOURCES)) $(patsubst %.c, %.o, $(CDEPS)) 
CPPOBJECTS		= $(patsubst %.cpp, %.o, $(CPPSOURCES)) $(patsubst %.cpp, %.o, $(CPPDEPS)) 

GLEW_SOURCE		= dependencies/GLEW/src/glew.c
GLEW_INCLUDE	= -I dependencies/GLEW/include/

LIB_DIR 	= dependencies/lib
GLEW		= $(LIB_DIR)/glew.o
GLFW3		= $(LIB_DIR)/glfw3.o

TARGET		= BilliardsGame.exe

all: $(TARGET)

install: $(TARGET) clean

# Build glew
$(GLEW): $(GLEW_SOURCE)
	mkdir -p $(LIB_DIR)
	gcc $(CFLAGS) $(GLEW_INCLUDE) -o $@ -c $^

# Build objects from C sources
$(COBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< $(CINCLUDES) -o $@

# Build objects from CPP sources
$(CPPOBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< $(CINCLUDES) -o $@

# Make executable
$(TARGET): $(COBJECTS) $(CPPOBJECTS) $(GLEW)
	$(CC) -o $@ $^ $(CINCLUDES) $(LDFLAGS)

# Clean object files when done
clean:
	rm -rf $(COBJECTS) $(CPPOBJECTS)
	rm -rf $(LIB_DIR)