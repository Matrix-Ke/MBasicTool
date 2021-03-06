#include "Log.h"

Matrix::Platform::MXLog::MXLog()
{
}

Matrix::Platform::MXLog::~MXLog()
{
}

bool Matrix::Platform::MXLog::Open(const TCHAR *pFileName)
{
    return MFile::Open(pFileName, EOpenMode::OM_WT);
}

bool Matrix::Platform::MXLog::WriteInfo(const TCHAR *pString)
{
    //时时刻刻记得字符数组不要越界
    return MFile::Write(pString, MXStrLen(pString) + 1, 1);
}
