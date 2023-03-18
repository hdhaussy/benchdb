#include "bench.h"
#include <gdbm.h>

typedef struct {
    GDBM_FILE db;
} BenchData;

void* bench_init() {
    BenchData* data = malloc(sizeof(BenchData));
    *data = (BenchData) {};
    return data;
}

int bench_open(void* ctxt, const char* filename) {
    BenchData* data = (BenchData*) ctxt;
    data->db = gdbm_open(filename,0,GDBM_NEWDB,0664,NULL);
    return data->db?GDBM_NO_ERROR:gdbm_errno;
}

int bench_close(void* ctxt) {
    BenchData* data = (BenchData*) ctxt;
    return gdbm_close(data->db);
}

int bench_put(void* ctxt, UUID key, Record value) {
    BenchData* data = (BenchData*) ctxt;
    datum k;
    datum v;
    k.dptr = (char*) &key;
    k.dsize = sizeof(key);
    v.dptr = value.data;
    v.dsize = value.len;
    return gdbm_store(data->db,k,v,GDBM_REPLACE);
}

int bench_get(void* ctxt, UUID key, Record* value) {
    BenchData* data = (BenchData*) ctxt;
    datum k;
    datum v;
    k.dptr = (char*) &key;
    k.dsize = sizeof(key);
    v = gdbm_fetch(data->db,k);
    value->data = v.dptr;
    value->len = v.dsize;
    return v.dptr?GDBM_NO_ERROR:gdbm_errno;
}

void bench_fini(void* ctxt) {
    free(ctxt);
}
