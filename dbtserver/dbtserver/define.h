#ifndef _h_define_h_
#define _h_define_h_

#define def_header_len	1

typedef struct  
{
	string	mUser;
	string	mPass;
	string	mNick;
	int		mId = 0;
	int		mCount = 0;
	int		mWin = 0;
	int		mRun = 0;
	int		mLoginCounts = 0;

}stPlayerInfo;
typedef shared_ptr<stPlayerInfo> playerInfoPtr;

typedef shared_ptr<thread> thread_ptr;
#endif
