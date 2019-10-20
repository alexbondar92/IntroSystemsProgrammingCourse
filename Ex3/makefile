CC = gcc
OBJS = parser.o main.o escape_technion.o room.o escaper.o company.o orders.o escape_utilitis.o
EXEC = mtm_escape
DEBUG = -DNDEBUG -g 
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -I. $(DEBUG)
LIBS = -L. -lmtm -lm
TESTS = escape_utilitis_test list_test orders_test escaper_test room_test company_test escape_technion_test
O_FILES = $(TEST_PATH)orders_test.o $(TEST_PATH)escaper_test.o \
$(TEST_PATH)room_test.o $(TEST_PATH)company_test.o $(TEST_PATH)escape_technion_test.o \
 $(LIST_PATH)list_mtm1.o $(TEST_PATH)list_test.o $(OBJS)
TEST_PATH=./tests/
LIST_PATH=./list_mtm/
TEST_GCC = $(CC) $(CFLAGS) -c $(TEST_PATH)$*.c $(TEST_PATH)$@ -o $@ 

tests : $(TESTS)

$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

list_mtm1.o : $(LIST_PATH)list_mtm1.h $(LIST_PATH)list_mtm1.c
	$(CC) $(CFLAGS) -c $(LIST_PATH)list_mtm1.c -o $(LIST_PATH)$@

list_test.o : $(TEST_PATH)list_test.c $(TEST_PATH)test_utilities.h $(LIST_PATH)list_mtm.o
	$(TEST_GCC) 

list_test : $(TEST_PATH)list_test.o $(LIST_PATH)list_mtm1.o
	$(CC) $(CFLAGS) $(LIST_PATH)list_mtm1.o $(TEST_PATH)list_test.o -o $@

escape_utilitis.o: escape_utilitis.c escape_utilitis.h mtm_ex3.h
	$(CC) $(CFLAGS) -c escape_utilitis.c

escape_utilitis_test.o: $(TEST_PATH)escape_utilitis_test.c $(TEST_PATH)test_utilities.h escape_utilitis.h escape_utilitis.o
	$(TEST_GCC) 

escape_utilitis_test: $(TEST_PATH)escape_utilitis_test.o escape_utilitis.o mtm_ex3.h $(TEST_PATH)test_utilities.h
	$(CC) $(TEST_PATH)$@.o escape_utilitis.o $(CFLAGS) $(LIBS) -o $@

escaper_test.o : $(TEST_PATH)escaper_test.c $(TEST_PATH)test_utilities.h escape_utilitis.h escape_utilitis.o escaper.o
	$(TEST_GCC)

escaper_test : $(TEST_PATH)escaper_test.o escape_utilitis.o escape_utilitis.h escaper.o mtm_ex3.h $(TEST_PATH)test_utilities.h
	$(CC) $(TEST_PATH)$@.o escaper.o escape_utilitis.o $(CFLAGS) $(LIBS) -o $@

escaper.o: escaper.c escaper.h mtm_ex3.h escape_utilitis.h
	$(CC) $(CFLAGS) -c escaper.c

room.o: room.c room.h mtm_ex3.h escape_utilitis.h
	$(CC) $(CFLAGS) -c room.c

room_test.o : $(TEST_PATH)room_test.c $(TEST_PATH)test_utilities.h escape_utilitis.o room.o
	$(TEST_GCC) 

room_test : room.o $(TEST_PATH)room_test.o $(TEST_PATH)test_utilities.h escape_utilitis.h mtm_ex3.h 
	$(CC) $(TEST_PATH)$@.o room.o escape_utilitis.o $(CFLAGS) $(LIBS) -o $@


orders.o: orders.c orders.h mtm_ex3.h escape_utilitis.h
	$(CC) $(CFLAGS) -c orders.c

orders_test.o : $(TEST_PATH)orders_test.c $(TEST_PATH)test_utilities.h escape_utilitis.o orders.o
	$(TEST_GCC) 

orders_test : orders.o $(TEST_PATH)orders_test.o $(TEST_PATH)test_utilities.h escape_utilitis.h mtm_ex3.h 
	$(CC) $(TEST_PATH)$@.o orders.o escape_utilitis.o $(CFLAGS) $(LIBS) -o $@



company.o: company.c company.h mtm_ex3.h room.h escape_utilitis.h
	$(CC) $(CFLAGS) -c company.c

company_test.o : $(TEST_PATH)company_test.c $(TEST_PATH)test_utilities.h escape_utilitis.o company.o room.o
	$(TEST_GCC) 

company_test : company.o $(TEST_PATH)company_test.o $(TEST_PATH)test_utilities.h escape_utilitis.h room.h mtm_ex3.h 
	$(CC) $(TEST_PATH)$@.o company.o escape_utilitis.o room.o $(CFLAGS) $(LIBS) -o $@


escape_technion.o: escape_technion.c escape_technion.h list.h set.h mtm_ex3.h room.h orders.h escaper.h company.h escape_utilitis.h
	$(CC) $(CFLAGS) -c escape_technion.c

escape_technion_test.o : $(TEST_PATH)escape_technion_test.c $(TEST_PATH)test_utilities.h escape_utilitis.o orders.o escaper.o company.o escape_technion.o room.o
	$(TEST_GCC) 

escape_technion_test : escape_technion.o $(TEST_PATH)escape_technion_test.o $(TEST_PATH)test_utilities.h escape_utilitis.h room.h list.h set.h escaper.h company.h orders.h mtm_ex3.h 
	$(CC) $(TEST_PATH)$@.o escape_technion.o escape_utilitis.o escaper.o company.o orders.o room.o $(CFLAGS) $(LIBS) -o $@

parser.o: parser.c parser.h escape_technion.h list.h set.h mtm_ex3.h room.h orders.h escaper.h company.h escape_utilitis.h
	$(CC) $(CFLAGS) -c parser.c

main.o: main.c parser.h escape_technion.h list.h set.h mtm_ex3.h room.h orders.h escaper.h company.h escape_utilitis.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TESTS) $(O_FILES) $(EXEC) $(OBJS)