EXES = insert_db insert_gdbm insert_qdbm

all: $(EXES)

clean:
	rm -f *.o
	rm -f $(EXES)

insert_gdbm: insert.o bench_gdbm.o
	$(CC) $? -lgdbm -o $@

insert_qdbm: insert.o bench_qdbm.o
	$(CC) $? -lqdbm -o $@

insert_db: insert.o bench_db.o
	$(CC) $? -ldb -o $@
