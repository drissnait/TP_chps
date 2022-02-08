CC=gcc

pagerank : pagerank.c
	$(CC) pagerank.c -o pagerank -lm
	gnuplot "plot.gp" > plot.png 
	
	
	
