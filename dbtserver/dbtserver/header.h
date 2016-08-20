#ifndef _h_header_h_
#define _h_header_h_
#include <string>
#include <map>
#include <list>
#include <mutex>
#include <memory>
#include <chrono>
#include <set>
#include <thread>
#include <unordered_map>

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif // WIN32

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <mysql.h>

#include "easylogging++.h"
using namespace std;

#endif // !_h_header_h_

