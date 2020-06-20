#include "FileUtils.h"
#include <fstream>
#include <rapidjson/error/error.h>
#include <rapidjson/error/en.h>
#include <iostream>
bool  FileUtils::Parse(const std::string & filePath, std::function<void(const std::string&)> fct )
{
	


	std::string line;
	std::ifstream myfile(filePath);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fct(line);
		}
		return true;
	}
	return false;

}

bool FileUtils::ParseJson(const std::string & filePath, std::function<void(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& obj)> fct)
{
	static std::string fileContent;
	Parse(filePath, [](const std::string & line) { fileContent = fileContent + line;  });
	rapidjson::Document doc;
	rapidjson::ParseResult ok =  doc.Parse(fileContent.c_str());

	if (!ok)
	{
		std::cout << "le document filepath n'est pas en json ou n'existe pas"  <<"\n erreur rapidejson = " << rapidjson::GetParseError_En(ok.Code()) << std::endl;
		return false;
	}
	for (auto& m : doc.GetObject())
		fct(m);
	return true;
}
