#include "bench.h"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main(int argc, char** argv) {
    if(argc <= 3) {
        printf("%s <filename> <count> <sz>\n",argv[0]);
        exit(1);
    }
    const char* filename = argv[1];
    int count = atoi(argv[2]);
    int sz = atoi(argv[3]);

    printf("filename=%s count=%d sz=%d\n",filename,count,sz);

    void* ctxt = bench_init();
    if(bench_open(ctxt, filename) != 0) {
        error(-1,0,"error in bench_open...");
    }

    Record value;
    value.data = malloc(sz);
    for(size_t i = 0; i < sz; i++) {
        value.data[i] = '*';
    }
    value.len = sz;
    
    UUID key; 
    for(int i = 0; i < count; i++) {
        key.hi = 123456789L;
        key.lo = i;
        if(bench_put(ctxt,key,value) != 0) {
            error(-1,0,"error in bench_put...");
        }
    }
    if(bench_close(ctxt) != 0) {
        error(-1,0,"error in bench_fini...");
    }
    bench_fini(ctxt);

    return 0;
}