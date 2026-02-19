win-mingw-dev:
	gcc src/*.c -o main.exe -Iinclude -lglfw3 -lopengl32 -lmingw32 -g
