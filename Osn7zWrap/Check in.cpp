#include "Osn7zClass.h"

#define SRC "D:\\OsnTM.tmp"
#define DESPATH "D:\\TMP"
int main()
{
	const char *srcFileList[] = {SRC, "D:\\OsnInit.tmp", "D:\\OsnNewDrClient.log"};	//File list waiting 7z-compression
	C7zCompression::file7zCompress(C7zCompression::file7zName(SRC).c_str(), srcFileList, 3);//Compress
	C7zCompression::file7zDeCompress("D:\\TMP", C7zCompression::file7zName(SRC).c_str());//Decompress
	C7zCompression::fileBackup("D:\\Backup", "D:\\OsnNewDrClient.log", 20 * 1024 *1024);//File backup
	return 0;
}