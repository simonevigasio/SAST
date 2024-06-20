FILE *fopen_if_not_exists(const char *file) {
  if (access(file, F_OK) == -1 && errno == ENOENT) {
    FILE *f = fopen(file, "w"); // Noncompliant

    return f;
  }

  return nullptr;
}