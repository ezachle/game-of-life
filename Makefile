GameOfLife:
	gcc -o main main.c life.c -I/usr/local/include -L/usr/local/lib64 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g

clean:
	rm main

