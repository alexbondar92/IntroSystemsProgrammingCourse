CCpp = g++
CC = gcc

OBJS_APP = $(OBJS_BASE)
OBJS_BASE =  EscapeRoomWrapper.o EscapeRoom.o Enigma.o ScaryRoom.o KidsRoom.o \
	Company.o
OBJS_TESTS = EscapeRoomWrapper_test.o Enigma_test.o Default_test.o \
	Company_test.o Company_Ostream_test.o
OBJS_ADT =
OBJS = $(OBJS_APP) $(OBJS_BASE) $(OBJS_ADT)

TESTS_EXE = EscapeRoomWrapper_test Enigma_test Default_test Company_test \
	Company_Ostream_test
LIST_TEST_EXE = list_test
APP_EXE =
EXE = $(TEST_EXE) $(APP_EXE)

#CHANGE TO -std=c++0x if gcc @ csl2 makes problem
COMP_FLAG_CPP = -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
TESTS = ./tests

$(APP_EXE) : $(OBJS_APP) $(OBJS_CMD)
	$(CCpp) $(COMP_FLAG_CPP) -o $@ $(OBJS_APP) $(LIB_FLAG) $(DEBUG_FLAG)

tests: $(TESTS_EXE) $(LIST_TEST_EXE)

clean:
	rm -f $(EXE) $(TESTS_EXE) $(LIST_TEST_EXE) $(OBJS) $(OBJS_TESTS)

clean_objs:
	rm -f $(OBJS)

#------Tests EXE making--------#

EscapeRoomWrapper_test: EscapeRoomWrapper_test.o EscapeRoom.o \
	EscapeRoomWrapper.o Enigma.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	EscapeRoom.o EscapeRoomWrapper.o Enigma.o $@.o $(LIB_FLAG)

Enigma_test: Enigma_test.o Enigma.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	Enigma.o $@.o $(LIB_FLAG)

Default_test: Default_test.o Enigma.o EscapeRoomWrapper.o EscapeRoom.o \
	Company.o KidsRoom.o ScaryRoom.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	Enigma.o EscapeRoomWrapper.o EscapeRoom.o Company.o KidsRoom.o ScaryRoom.o \
	$@.o $(LIB_FLAG)

Company_test: EscapeRoomWrapper.o EscapeRoom.o Enigma.o ScaryRoom.o \
	KidsRoom.o Company.o Company_test.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	EscapeRoomWrapper.o EscapeRoom.o Enigma.o ScaryRoom.o \
	KidsRoom.o Company.o $@.o $(LIB_FLAG)

Company_Ostream_test: EscapeRoomWrapper.o EscapeRoom.o Enigma.o ScaryRoom.o \
	KidsRoom.o Company.o Company_Ostream_test.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	EscapeRoomWrapper.o EscapeRoom.o Enigma.o ScaryRoom.o \
	KidsRoom.o Company.o $@.o $(LIB_FLAG)

list_test: list_test.o
	$(CCpp) -o $@ $(DEBUG_FLAG) $(COMP_FLAG_CPP) \
	$@.o $(LIB_FLAG)

#-----Objects Making-------#
# Tests objects
EscapeRoomWrapper_test.o: tests/EscapeRoomWrapper_test.cpp \
 mtmtest.h tests/../EscapeRoomWrapper.h tests/../EscapeRoom.h \
 tests/../Exceptions.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

Enigma_test.o: tests/Enigma_test.cpp mtmtest.h tests/../Enigma.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

Default_test.o: tests/Default_test.cpp tests/../EscapeRoomWrapper.h \
	tests/../EscapeRoom.h tests/../Enigma.h tests/../ScaryRoom.h \
	tests/../EscapeRoomWrapper.h tests/../KidsRoom.h tests/../Company.h \
	tests/../mtmtest.h tests/../Exceptions.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

Company_test.o: tests/Company_test.cpp tests/../mtmtest.h \
	tests/../EscapeRoomWrapper.h tests/../EscapeRoom.h tests/../Enigma.h \
	tests/../Exceptions.h tests/../KidsRoom.h tests/../EscapeRoomWrapper.h \
	tests/../ScaryRoom.h tests/../Company.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

Company_Ostream_test.o: tests/Company_Ostream_test.cpp tests/../mtmtest.h \
	tests/../KidsRoom.h tests/../EscapeRoomWrapper.h tests/../EscapeRoom.h \
	tests/../Enigma.h tests/../ScaryRoom.h tests/../EscapeRoomWrapper.h \
	tests/../Company.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

list_test.o: tests/list_test.cpp tests/../mtmtest.h tests/../list.h \
	tests/../../OriginalFiles/Exceptions.h
	$(CCpp) $(COMP_FLAG_CPP) -c $(TESTS)/$*.cpp

# App Objects
EscapeRoom.o: EscapeRoom.c EscapeRoom.h
	$(CC) $(COMP_FLAG) -c $*.c

Enigma.o: Enigma.cpp Enigma.h
	$(CCpp) $(COMP_FLAG_CPP) -c $*.cpp

EscapeRoomWrapper.o: EscapeRoomWrapper.cpp EscapeRoomWrapper.h \
	 EscapeRoom.h Enigma.h Exceptions.h
	 $(CCpp) $(COMP_FLAG_CPP) -c $*.cpp

KidsRoom.o: KidsRoom.cpp KidsRoom.h EscapeRoomWrapper.h EscapeRoom.h \
	Enigma.h Exceptions.h
	$(CCpp) $(COMP_FLAG_CPP) -c $*.cpp

ScaryRoom.o: ScaryRoom.cpp ScaryRoom.h EscapeRoomWrapper.h EscapeRoom.h \
	Enigma.h Exceptions.h
	$(CCpp) $(COMP_FLAG_CPP) -c $*.cpp

Company.o: Company.cpp EscapeRoomWrapper.h EscapeRoom.h Enigma.h \
	 Company.h Exceptions.h ScaryRoom.h KidsRoom.h
	$(CCpp) $(COMP_FLAG_CPP) -c $*.cpp
