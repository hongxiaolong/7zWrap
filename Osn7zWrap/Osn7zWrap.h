#ifndef _7ZWRAP_H
#define _7ZWRAP_H

#define RE_OK 0
#define RE_ERROR_LOAD_7ZDLL 1
#define RE_ERROR_CREATE_OBJECT 2
#define RE_ERROR_CREATE_OBJECT_FUNC 3
#define RE_ERROR_OPEN_ARCHIVE_FILE 4
#define RE_ERROR_EXTRACT 5

typedef void (*CBDecodeSetTotal)(unsigned long long nTotal);
typedef void (*CBDecodeSetComplete)(unsigned long long nComplete);

extern "C"
{
	int Code7z(const char *Des, const char **Src, const int numSrc= 1, const char *Args = "a");

	int Decode7z(const char* DesPath, const char* Src,
		CBDecodeSetTotal Total = NULL, CBDecodeSetComplete Complete = NULL);
};

#endif //_7ZWRAP_H