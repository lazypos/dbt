#ifndef _h_delegate_h_
#define _h_delegate_h_
#include "Connect.h"
#include "define.h"

inline void read_cb(struct bufferevent *bev, void *ctx) {
	int rLen = 0;
	int *pLen = &rLen;
	CConnect* conn = reinterpret_cast<CConnect*>(ctx);
	size_t recvLen = evbuffer_get_length(bufferevent_get_input(bev));
	// �յ����ݴ���ͷ����
	if (recvLen >= def_header_len) {
		string strBuf;
		strBuf.resize(def_header_len, 0);
		bufferevent_read(bev, (void*)strBuf.c_str(), def_header_len);
		pLen = reinterpret_cast<int*>(const_cast<char*>(strBuf.c_str()));
		if (rLen < 0){
			LERROR << "�յ��������ݣ��Ͽ��ͻ������ӡ�" << conn->getRemoteIP();
			conn->closeConnect();
			return;
		}
		// �յ�ȫ�����ݣ����д���
		if (recvLen == rLen + 4) {
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