#makefile for dbtserver

TARGET_FILE=dbtsvr

CC=g++
CFLAG=-c -std=c++11
INCLUDE=-I/usr/include/mysql
LIBNAMES=-lmysqlclient -levent -lpthread -ldl
OBJS=dbtserver.o Config.o Connect.o DBManager.o Desk.o Global.o Hall.o
OBJS+=Player.o SqlmyOpt.o SqlmyResult.o DBTRule.o LoginSvr.o

$(TARGET_FILE):$(OBJS)
	$(CC) -o $(TARGET_FILE) $^ $(LIBNAMES) 

$(OBJS):./dbtserver/*.cpp
	$(CC) $(CFLAG) $^ $(INCLUDE) $(LIBNAMES)


.PHONY:clean cleanall
clean:
	rm -rf $(OBJS)
cleanall:
	rm -rf $(OBJS)
	rm -f $(TARGET_FILE)
