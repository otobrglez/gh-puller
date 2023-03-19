#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct memory {
  char * response;
  size_t size;
};

static size_t response_callback(void * data, size_t size, size_t nmemb, void * clientp) {
  size_t realsize = size * nmemb;
  struct memory * mem = (struct memory * ) clientp;

  char * ptr = realloc(mem -> response, mem -> size + realsize + 1);
  if (ptr == NULL) return 0; /* out of memory! */

  mem -> response = ptr;
  memcpy( & (mem -> response[mem -> size]), data, realsize);
  mem -> size += realsize;
  mem -> response[mem -> size] = 0;

  return realsize;
}

static size_t header_callback(char * data, size_t size, size_t nmemb, void * userdata) {
  size_t realsize = size * nmemb;
  struct memory * mem = (struct memory * ) userdata;

  char * ptr = realloc(mem -> response, mem -> size + realsize + 1);
  if (ptr == NULL) return 0; /* out of memory! */

  mem -> response = ptr;
  memcpy( & (mem -> response[mem -> size]), data, realsize);
  mem -> size += realsize;
  mem -> response[mem -> size] = 0;

  return realsize;
}

char * get(char url[]) {
  struct memory chunk = {
    0
  };
  CURL * curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "gh-puller/1.0");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void * ) & chunk);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void * ) & chunk);

    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

    CURLcode res;
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    // free(chunk.response); 
    curl_easy_cleanup(curl);
    return chunk.response;
  };

  return NULL;
}