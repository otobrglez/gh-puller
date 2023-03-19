.PHONY: clean test

clean:
	rm -rf curl_requests curl_requests_test *.o gh-puller

curl_requests.o:
	cc -Wall -pedantic -g -c curl_requests.c -lcurl -o curl_requests.o

curl_requests_test: curl_requests.o
	cc -Wall -pedantic -D TEST curl_requests_test.c curl_requests.o -o curl_requests_test -lcurl

gh-puller:
	scala-cli --power package --native . -o gh-puller -f \
		--maintainer "Oto Brglez"

test: curl_requests_test
	./curl_requests_test

all: test gh-puller
	echo "Built C code and packaging ran"
