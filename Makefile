matrix_math: mat_math.o main.o
	g++ mat_math.o main.o -o matrix_math

main.o: main.cpp
	g++ -c main.cpp

mat_math.o: mat_math.cpp
	g++ -c mat_math.cpp

clean:
	rm *.o