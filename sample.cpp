#include <string>

void f(char *password, size_t bufferSize) {
  char localToken[256];
  init(localToken, password);
  memset(password, 0, strlen(password));  // Noncompliant
  memset(localToken, 0, strlen(localToken));  // Noncompliant
  free(password);
}