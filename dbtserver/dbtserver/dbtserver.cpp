#include "header.h"
#include "LoginSvr.h"
#include "DBManager.h"
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) 
{
#ifdef WIN32
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
#endif // WIN32

	if (!dbmanager::Instance()->start())
		return false;

	if (loginSvr::Instance()->start(5183)){
		loginSvr::Instance()->run();
	}
	LERROR << "³ÌÐòÍË³ö";

#ifdef WIN32
	WSACleanup();
#endif // WIN32
	return 0;
}