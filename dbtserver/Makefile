#makefile for dbtserver

TARGET_FILE=./dbtserver

CC=g++
CFLAG=
LIBNAMES=-llibmysql -llibevent
OBJS=dbtserver.o Config.o Connect.o DBManager.o Desk.o Global.o Hall.o LoginSvr.o
OBJS+=Player.o SqlmyOpt.o SqlmyResult.o

all:$(OBJS)
	$(CC) -o $(TARGET_FILE)  $@ $(LIBNAMES) 

.o:.cpp
	$(CC) $(CFLAG) $< $(LIBNAMES)


.PHONY:clean cleanall
clear:
	rm -rf ./dbtserver/*.o
cleanall:
	rm -rf ./dbtserver/*.o
	rm -f ./dbtserver