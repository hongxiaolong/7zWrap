//************************************************
//************************************************
//2013.5.20	
//Author: xiaolonginfo@github.com
//https://github.com/xiaolonginfo/7zWrap.git
//http://www.7-zip.org
//Osn7zWrap for file compression/decompression.							
//Modify 7z source code for 7z code/decode lib.
//7z.dll	Osn7zWrap.lib	Osn7zWrap.h
//************************************************
//************************************************

#ifndef _OSN_7ZCLASS_H_
#define _OSN_7ZCLASS_H_
#include <windows.h>
#include  <io.h>
#include <direct.h>
#include <string>
#include <sys\stat.h> 
#include "Osn7zWrap.h"
#pragma comment(lib,"Osn7zWrap.lib")

class C7zCompression
{
public:
	inline static int file7zCompress(const char *desFile, const char **srcFile, const int numSrc= 1, const char *Args = "a")
	{
		int ret= ERROR_INVALID_FUNCTION;
		ret = Code7z(desFile, srcFile, numSrc, Args);
		return ret;
	}
	inline static int file7zDeCompress(const char * desPath, const char *src7zFile, 
		CBDecodeSetTotal total = NULL, CBDecodeSetComplete complete = NULL)
	{
		int ret= ERROR_INVALID_FUNCTION;
		ret = Decode7z(desPath, src7zFile, total, complete);
		return ret;
	}

public:
	inline static std::string file7zName(const char *file)
	{
		std::string name(file);
		name.append(".7z");
		return name;
	}
	inline static unsigned long fileSize(const char *file)
	{
		struct _stat info;  
		_stat(file, &info);  
		int size = info.st_size;
		return size;
	}
	static std::string UUNameFromSystemTime(const char *file);
	static int fileMove(const char *path, const char *file);
	static int fileBackup(const char *path, const char *file, const unsigned long size);
};

//Get an unique file name from system time
std::string C7zCompression::UUNameFromSystemTime(const char *file)
{
	//Get System Time
	char	retTime[MAX_PATH];
	SYSTEMTIME	currentTime;
	GetLocalTime(&currentTime);
	sprintf_s(retTime, "-%.4d%.2d%.2d-%.2d%.2d%.2d\0",
		currentTime.wYear,currentTime.wMonth,currentTime.wDay,
		currentTime.wHour,currentTime.wMinute, currentTime.wSecond);
	std::string name(file);
	std::string extension;
	std::string::size_type pos = name.rfind(".");
	extension.assign(name, pos, name.size() - pos);
	name.assign(name.begin(), name.begin() + pos);
	name.append(retTime);
	name.append(extension);
	return name;
}

//Move file to path
int C7zCompression::fileMove(const char *path, const char *file)
{
	if (_access(path, 0))
	{
		int status = _mkdir(path);
		if (status)
			return ERROR_CANNOT_MAKE;
	}
	std::string ret(file);
	std::string::size_type pos = ret.find_last_of("\\");
	std::string newFile(path);
	newFile.append(ret, pos, ret.size() - pos);
	if (0 == MoveFileA(file, newFile.c_str()))
		return ERROR_INVALID_FUNCTION;//Failed move file
	return ERROR_SUCCESS;
}

//Backup: 1.Compress file exceeds limit size to 7z format; 2.Move file.7z to a new path; 3.delete old file.
int C7zCompression::fileBackup(const char *path, const char *file, const unsigned long size)
{
	if (fileSize(file) >= size)
	{
		if (_access(path, 0))
		{
			int status = _mkdir(path);
			if (status)
				return ERROR_CANNOT_MAKE;
		}
		const char *srcFile[] = {file};
		std::string desFile(file7zName(UUNameFromSystemTime(file).c_str()).c_str());
		if (file7zCompress(desFile.c_str(), srcFile))
			return ERROR_INVALID_FUNCTION;
		if (fileMove(path, desFile.c_str()))
			return ERROR_INVALID_FUNCTION;
		remove(file);//delete
	}
	return ERROR_SUCCESS;
}	

#endif