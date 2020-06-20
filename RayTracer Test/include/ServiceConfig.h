#pragma once
#ifndef SERVICECONFIG_H
#define SERVICECONFIG_H

#include <map>
#include <string>
#include "Service.h"

class ServiceConfig : public Service
{
public:
	ServiceConfig(std::string FileName = "config.init" );
	~ServiceConfig();

	std::string GetAProperty(std::string name);

private:

	std::map<std::string, std::string> _MapProperty;
};

#endif // !
