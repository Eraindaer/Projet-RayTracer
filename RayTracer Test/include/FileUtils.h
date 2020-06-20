#pragma once
#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <string>
#include <functional>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
class FileUtils
{
public:


	static bool Parse(const std::string & filePath, std::function<void(const std::string & line)> fct);
	static bool ParseJson(const std::string & filePath, std::function<void(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& obj)> fct);


private:

};

#endif // !1
