#include "Core.h"
#include <sys/stat.h> //获取文件状态

namespace Matrix
{
	namespace  Platform
	{
		TCHAR MatrixCore::msLogbuffer[LOG_BUFFER_SIZE];
		unsigned long MatrixCore::msMainThreadID = 0;
		void MXOutputDebugString(const TCHAR* pcString, ...)
		{
			char* pArgs;
			pArgs = (char*)&pcString + sizeof(pcString);
			_vstprintf_s(MatrixCore::msLogbuffer, LOG_BUFFER_SIZE, pcString, pArgs);
			OutputDebugString(MatrixCore::msLogbuffer);
		}
		void MXSetCurrentDirectory(TCHAR* CurDir)
		{
			SetCurrentDirectory(CurDir);
		}
		void MXInitSystem()
		{
			MatrixCore::msMainThreadID = GetCurrentThreadId();
		}
		unsigned int MXTlsAlloc()
		{
			return TlsAlloc();
		}
		void* MXGetTlsValue(unsigned int TlsSolt)
		{
			return TlsGetValue(TlsSolt);
		}
		bool MXSetTlsValue(unsigned int TlsSolt, void* TlsValue)
		{
			return TlsSetValue(TlsSolt, TlsValue);
		}
		bool MXTlsFree(unsigned int TlsSolt)
		{
			return TlsFree(TlsSolt);
		}
	}
}