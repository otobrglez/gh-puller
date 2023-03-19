.PHONY: clean test

clean:
	rm -rf curl_requests curl_requests_test *.o gh-puller

curl_requests.o:
	cc -Wall -pedantic -g -c curl_requests.c -lcurl -o curl_requests.o

curl_requests_test: curl_requests.o
	cc -Wall -pedantic -D TEST curl_requests_test.c curl_requests.o -o curl_requests_test -lcurl

test: curl_requests_test
	./curl_requests_test
	