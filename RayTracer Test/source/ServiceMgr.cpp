#include "ServiceMgr.h"

ServiceMgr * ServiceMgr::_Instance = nullptr;

ServiceMgr::ServiceMgr()
{

}

ServiceMgr::~ServiceMgr()
{
	for (auto it = _ServVector.begin(); it != _ServVector.end(); ++it)
		free(*it);
}

ServiceMgr * ServiceMgr::Instance()
{
	if (_Instance == nullptr)
		_Instance = new ServiceMgr();

	return _Instance;
}

void		ServiceMgr::RegisterAService(Service * serv) // obtenir l'uniformité des services un type un service
{
	_ServVector.push_back(serv);
}
