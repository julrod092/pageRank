all: pagerank

pagerank: clean bin
	mpic++ src/PageRank.cpp -o bin/pagerank

bin:
	mkdir bin

clean:
	rm -rf bin

run: bin/pagerank
	bin/pagerank ${n} ${d}
