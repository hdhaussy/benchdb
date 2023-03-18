#ifndef __include_bench_h
#define __include_bench_h

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int64_t hi;
    int64_t lo;
} UUID;

typedef struct {
    size_t len;
    char* data;
} Record;

void* bench_init();
int bench_open(void* ctxt, const char* filename);
int bench_close(void* ctxt);
int bench_put(void* ctxt, UUID key, Record value);
int bench_get(void* ctxt, UUID key, Record* value);
void bench_fini(void* ctxt);

#endif // #ifndef __include_bench_h