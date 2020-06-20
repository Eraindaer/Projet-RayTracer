#pragma once
#ifndef SERVICEMGR_H
#define	SERVICEMGR_H
#include <vector>

class Service;

class ServiceMgr
{

public:
	~ServiceMgr();
	static ServiceMgr * Instance();
	
	void		RegisterAService(Service * serv);

	template<class typeServ> // a mettre dans un .inl 
	typeServ*	GetAService()
	{
		for (auto it = _ServVector.begin(); it != _ServVector.end(); ++it)
			if (dynamic_cast<typeServ *>(*it) != nullptr)
				return static_cast<typeServ * >(*it);
	}

private:
	ServiceMgr();
	static ServiceMgr * _Instance;
	std::vector<Service *> _ServVector;
};
#endif // !1
