#include "Service.h"
#include "ServiceMgr.h"

Service::Service()
{
	ServiceMgr::Instance()->RegisterAService(this);

}

Service::~Service()
{

}

void Service::Init()
{

}