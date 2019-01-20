all:main

main: main.c  format.c
	gcc main.c cjson/cJSON.c format.c aes/aes.c -Icjson -Iinc/myprint -Iaes -o main -g -lm 

clean:
	rm main -f
