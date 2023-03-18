#include "bench.h"
#include <qdbm/depot.h>
#include <stdlib.h>


typedef struct {
    DEPOT* db;
} BenchData;

void* bench_init() {
    BenchData* data = malloc(sizeof(BenchData));
    *data = (BenchData) {};
    return data;
}

int bench_open(void* ctxt, const char* filename) {
    BenchData* data = (BenchData*) ctxt;
    data->db = dpopen(filename,DP_OWRITER | DP_OCREAT,0);
    return data->db?DP_ENOERR:dpecode;
}

int bench_close(void* ctxt) {
    BenchData* data = (BenchData*) ctxt;
    int ok = dpclose(data->db);
    return ok?DP_ENOERR:dpecode;
}

int bench_put(void* ctxt, UUID key, Record value) {
    BenchData* data = (BenchData*) ctxt;
    int ok = dpput(data->db,(const char*) &key,sizeof(key),value.data,value.len,DP_DOVER);
    return ok?DP_ENOERR:dpecode;
}

int bench_get(void* ctxt, UUID key, Record* value) {
    BenchData* data = (BenchData*) ctxt;
    int len;
    value->data = dpget(data->db,(const char*) &key,sizeof(key),0,-1,&len);
    value->len = len;
    return value->data?DP_ENOERR:dpecode;
}

void bench_fini(void* ctxt) {
    free(ctxt);
}
