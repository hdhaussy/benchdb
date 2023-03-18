#include "bench.h"
#include <db.h>

typedef struct {
    DB* db;
} BenchData;

void* bench_init() {
    BenchData* data = malloc(sizeof(BenchData));
    *data = (BenchData) {};
    db_create(&data->db, NULL, 0);
    return data;
}

int bench_open(void* ctxt, const char* filename) {
    BenchData* data = (BenchData*) ctxt;
    return data->db->open(data->db,NULL,filename,NULL,DB_HASH,DB_CREATE,0);
}

int bench_close(void* ctxt) {
    BenchData* data = (BenchData*) ctxt;
    return data->db->close(data->db,0);
}

int bench_put(void* ctxt, UUID key, Record value) {
    BenchData* data = (BenchData*) ctxt;
    DBT k = { .data = &key, .size = sizeof(key) };
    DBT v = { .data = value.data, .size = value.len };
    return data->db->put(data->db,NULL,&k,&v,0);
}

int bench_get(void* ctxt, UUID key, Record* value) {
    BenchData* data = (BenchData*) ctxt;
    DBT k = { .flags = DB_DBT_MALLOC };
    DBT v = { .flags = DB_DBT_MALLOC };
    return data->db->get(data->db,NULL,&k,&v,0);
}

void bench_fini(void* ctxt) {
    free(ctxt);
}
