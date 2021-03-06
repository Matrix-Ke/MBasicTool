#include "Platform/File.h"
#include "Container/String.h"


using namespace Matrix;

int main()
{
	using namespace Platform;
	using namespace Container;

	//{} 花括号默认初始化为0
	TCHAR moudlefile[MAX_FILE_PATH_SIZE] = {};

	MXGetModuleFilePath(moudlefile);
	//for (unsigned i = 0; i < MAX_FILE_PATH_SIZE; i++)
	//{
	//	MXSprintf(_T("print: %d =  %x end\n"), i, dir[i]);
	//}
	MFileName  tempName(moudlefile);
	MString  workDir("");
	tempName.GetPath(workDir);

	MString    filePath = workDir + MString("/../../BasicTool/Sample/00_StringTest/FileDemo.txt");
	MXSprintf(_T("print: %s \n"), filePath.GetBuffer());
	MFile   jsonFile(filePath.GetBuffer());
	unsigned int  size = jsonFile.GetFileSize();
	MString  Buffer(size);
	jsonFile.Read(Buffer.GetBuffer(), sizeof(TCHAR), size);

	MXSprintf(_T("jsonfile Content: %s \n"), Buffer.GetBuffer());

	return 0;
}