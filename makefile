win-mingw-dev:
	gcc src/*.c -o main.exe -Iinclude -lglfw3 -lopengl32 -lmingw32 -g

mac-brew:
	gcc src/*.c -o main.out -Iinclude -I/opt/homebrew/include -L/opt/homebrew/lib -framework OpenGL -framework Cocoa -framework IOKit -lglfw3 -g

