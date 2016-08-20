#ifndef _h_delegate_h_
#define _h_delegate_h_
#include "Connect.h"
#include "define.h"

inline void read_cb(struct bufferevent *bev, void *ctx) {
	size_t rLen = 0;
	CConnect* conn = reinterpret_cast<CConnect*>(ctx);
	size_t recvLen = evbuffer_get_length(bufferevent_get_input(bev));
	// 收到数据大于头长度
	if (recvLen >= def_header_len) {
		string strBuf;
		strBuf.resize(def_header_len, 0);
		bufferevent_read(bev, (void*)strBuf.c_str(), def_header_len);
		rLen = strBuf[0];
		if (rLen < 0){
			LERROR << "recv error，break client." << conn->getRemoteIP();
			conn->closeConnect();
			return;
		}
		// 收到全部数据，进行处理
		if (recvLen >= rLen + def_header_len) {
			strBuf.resize(rLen, 0);
			bufferevent_read(bev, (void*)strBuf.c_str(), rLen);
			conn->dispath(strBuf);
		}
	}
}

inline void send_cb(struct bufferevent *bev, void *ctx) {

}

inline void event_cb(struct bufferevent *bev, short what, void *ctx) {
	CConnect* conn = reinterpret_cast<CConnect*>(ctx);
	if (what & BEV_EVENT_EOF) {
		LDEBUG << "remote closed." << conn->getRemoteIP();
		conn->closeConnect();
	}
	else if (what & BEV_EVENT_ERROR) {
		LERROR << "remote error." << conn->getRemoteIP();
		conn->closeConnect();
	}
	else 
		LDEBUG << "event_cb: " << what << conn->getRemoteIP();
}

#endif