SOURCE_FILE = game_client.cpp
TARGET = game_client

all:
	g++ -std=c++11 -o $(TARGET) -I/vagrant_data/DB/mysql-connector-c++-8.0.11-linux-ubuntu16.04-x86-64bit/include/ -I/vagrant_data/DB/mysql-connector-c++-8.0.11-linux-ubuntu16.04-x86-64bit/include/jdbc -L/vagrant_data/DB/mysql-connector-c++-8.0.11-linux-ubuntu16.04-x86-64bit/lib64 $(SOURCE_FILE) -lmysqlcppconn -lncurses
