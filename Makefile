CC = gcc
CFLAGS = -I./ -Wall -std=c11
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = mvp_raylib.c mvp_cubo.c
OUT = mvp_raylib.exe mvp_cubo.exe

all: $(OUT)

mvp_raylib.exe: mvp_raylib.c
	$(CC) $(CFLAGS) mvp_raylib.c -o mvp_raylib.exe $(LDFLAGS)

mvp_cubo.exe: mvp_cubo.c
	$(CC) $(CFLAGS) mvp_cubo.c -o mvp_cubo.exe $(LDFLAGS)

run_raylib: mvp_raylib.exe
	./mvp_raylib.exe

run_cubo: mvp_cubo.exe
	./mvp_cubo.exe

clean:
	rm -f mvp_raylib.exe mvp_cubo.exe
