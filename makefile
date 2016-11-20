all: pagerank

pagerank: clean bin
	g++ src/PageRank.cpp -o bin/pagerank

bin:
	mkdir bin

clean:
	rm -rf bin

