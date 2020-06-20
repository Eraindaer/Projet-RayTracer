#include  "ServiceConfig.h"
#include "FileUtils.h"
#include  <fstream>
#include <iostream>


ServiceConfig::ServiceConfig(std::string filename) : Service()
{
	if (FileUtils::Parse(filename, [this](const std::string&  line) {
		int index = line.find("=");
		if (index != std::string::npos)
		{
			this->_MapProperty[line.substr(0, index)] = line.substr(index + 1, line.length());
		}}
	) == false)
			std::cout << "Unable to open file in configMGr  file = " << filename << std::endl;
}

ServiceConfig::~ServiceConfig()
{
	
}

std::string ServiceConfig::GetAProperty(std::string name)
{
	auto prop = this->_MapProperty.find(name);
	if (prop == _MapProperty.end())
		return "";
	return prop->second;

}