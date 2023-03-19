#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "curl_requests.h"

#ifdef TEST
int main() {
  printf("%s\n", get("https://api.github.com/users/otobrglez/events"));
  printf("This is main. Done.\n");
  return 0;
};
#endif
