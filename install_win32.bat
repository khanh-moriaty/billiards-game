@ECHO OFF
cd dependencies\GLEW
mkdir lib
gcc -DGLEW_NO_GLU -O2 -w -I include -DGLEW_BUILD -o src\glew.o -c src\glew.c
gcc -nostdlib -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib\libglew32.dll.a -o lib\glew32.dll src\glew.o -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
cd ..\..\
copy dependencies\GLEW\lib\glew32.dll .\glew32.dll
copy dependencies\GLFW\lib\glfw3_x86.dll .\glfw3.dll

gcc -w -std=c++0x -o main.exe ^
-I. -I dependencies\GLEW\include\ -I dependencies\GLFW\include\ -I dependencies\GLM\include\ -I dependencies\SOIL2\include\ ^
.\main.cpp .\dependencies\GLM\include\glm\detail\glm.cpp .\dependencies\SOIL2\include\SOIL2.c ^
.\dependencies\SOIL2\include\image_DXT.c .\dependencies\SOIL2\include\image_helper.c .\dependencies\SOIL2\include\wfETC.c ^
-L. -lglfw3 -lglew32 -lopengl32 -lstdc++