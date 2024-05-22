default:
	g++ main.cpp funcs.cpp -o gopbon.exe -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static-libstdc++ -static-libgcc -static -mwindows

	