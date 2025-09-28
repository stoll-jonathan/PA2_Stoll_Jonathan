threaded_sum: threaded_sum.o
	gcc threaded_sum.o -o threaded_sum

threaded_sum.o: threaded_sum.c
	gcc -c threaded_sum.c -Wall

clean_csv:
	rm *.csv

clean:
	rm *.o threaded_sum a.out