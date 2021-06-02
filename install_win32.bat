@ECHO OFF
cd GLEW
mkdir lib
gcc -DGLEW_NO_GLU -O2 -w -I include -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -nostdlib -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a -o lib/glew32.dll src/glew.o -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
cd ..\
copy GLEW\lib\glew32.dll .\

gcc -w -std=c++0x -I. -I GLEW/include/ -I GLFW/include/ -I GLM/include/ -I SOIL2/include/ -o main.exe ^
./Application.cpp ./GLM/include/glm/detail/glm.cpp ./SOIL2/include/SOIL2.c ./SOIL2/include/image_DXT.c ./SOIL2/include/image_helper.c ./SOIL2/include/wfETC.c ^
-L. -lglfw3 -lglew32 -lopengl32 -lstdc++  