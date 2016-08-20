#ifndef _h_CSqlmyOpt_h_
#define _h_CSqlmyOpt_h_
#include "DBOptBase.h"
#include "SqlmyResult.h"

class CSqlmyOpt;
typedef std::shared_ptr<CSqlmyOpt> SqlmyOptPtr;

class CSqlmyOpt
	: public CDBOptBase
{
public:
	CSqlmyOpt();
	~CSqlmyOpt();

	virtual bool	open();
	virtual void	close();
	virtual	bool	query(const std::string& sql, DBResultPtr& ptr);
	virtual	bool	execute(const std::string& sql);

private:
	const std::string getLastError(long& errCode);
	void	clean();

private:
	MYSQL*				_connPtr;
	std::mutex			_mutex;
};

#endif
