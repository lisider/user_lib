all:${O}

${O}: ${O}.c
	gcc ${O}.c ../cJSON.c -I.. -o ${O} -lm


clean:
	find  . -executable  -delete
