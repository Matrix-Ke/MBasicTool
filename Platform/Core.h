//====================================提供平台相关的系统调用接口，所有系统调用必须使用这里的接口=====================================
//目前只提供windows平台接口，能使用_win api的优先使用 win api。 
#pragma once
#include "PlatformMacro.h"
#include <cstdio>
#include <tchar.h>
#include <memory>
#include <intrin.h>
#include <cassert>
#include <Windows.h>
#include <direct.h>
//#pragma warning(disable:4251) //去除模板导出编译的警告
#ifdef USE_STL_TYPE_TRAIT
// stl 类型萃取
#include <type_traits>
#endif // USE_STL_TYPE_TRAIT

#ifdef Platform_EXPORTS
#define MATRIX_PLATFORM_API __declspec(dllexport)
#else
#define MATRIX_PLATFORM_API __declspec(dllimport)
#endif

#ifdef _DEBUG
// assert 的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。
//在调试结束后，可以通过在包含 #include 的语句之前插入 #define NDEBUG 来禁用 assert 调用
#define ENGINE_ASSERT(Expression) \
    {                                \
        assert(Expression);          \
    }
#else
//通过debug来控制
#define ENGINE_ASSERT(Expression)
#endif


namespace Matrix
{
	namespace  Platform
	{
#define MAX_FILE_PATH_SIZE 256

#define THREAD_CALLBACK __stdcall

		inline unsigned int SizeTypeToGUID32(USIZE_TYPE Size_Type)
		{
			return (Size_Type & 0xffffffff);
		}
		inline USIZE_TYPE GUID32ToSizeType(unsigned int uiGUID)
		{
#if _WIN64
			return (uiGUID & 0x00000000ffffffff);
#else
			return (uiGUID & 0xffffffff);
#endif
		}
		//指针地址比较
		inline int ComparePointer(void* Point1, void* Point2)
		{

			if (((USIZE_TYPE)Point1) == ((USIZE_TYPE)Point2))
			{
				return 0;
			}
			else if (((USIZE_TYPE)Point1) > ((USIZE_TYPE)Point2))
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

#define LOG_BUFFER_SIZE 65536
		//引擎核心静态变量
		class MATRIX_PLATFORM_API MatrixCore
		{
		public:
			static TCHAR msLogbuffer[LOG_BUFFER_SIZE];
			static unsigned long msMainThreadID;
		};

#ifdef USE_STL_TYPE_TRAIT
		// C++ STL的std::is_trivially_constructible模板用于检查给定类型T是否是带有参数集的平凡可构造类型。
		//如果T是平凡可构造的类型，则它返回布尔值true，否则返回false。
#define HAS_TRIVIAL_CONSTRUCTOR(T) std::is_trivially_constructible<T>::value
#define HAS_TRIVIAL_DESTRUCTOR(T) std::is_trivially_destructible<T>::value
#define HAS_TRIVIAL_ASSIGN(T) std::is_trivially_assignable<T>::value
#define HAS_TRIVIAL_COPY(T) std::is_trivially_copyable<T>::value
#define IS_POD(T) std::is_pod<T>::value
#define IS_ENUM(T) std::is_enum<T>::value
#define IS_EMPTY(T) std::is_empty<T>::value

		// POD，是Plain Old Data的缩写，普通旧数据类型，是C++中的一种数据类型概念
		template <typename T>
		struct TIsPODType
		{
			enum
			{
				Value = IS_POD(T)
			};
		};

		template <typename T>
		struct ValueBase
		{
			enum
			{
				NeedsConstructor = !HAS_TRIVIAL_CONSTRUCTOR(T) && !TIsPODType<T>::Value
			};
			enum
			{
				NeedsDestructor = !HAS_TRIVIAL_DESTRUCTOR(T) && !TIsPODType<T>::Value
			};
		};
		/*
			（1）(align-1)，表示对齐所需的对齐位，如：2字节对齐为1，4字节为11，8字节为111，16字节为1111…
			（2）(x+(align-1))，表示x补齐对齐所需数据
			（3）&~(align-1)，表示去除由于补齐造成的多余数据
			（4） (x+(align-1))&~(align-1)，表示对齐后的数据
			原文链接：https://blog.csdn.net/github_38148039/article/details/109261903
		*/
		template <class T>
		inline T MXAlign(const T Ptr, USIZE_TYPE Alignment)
		{
			return (T)(((USIZE_TYPE)Ptr + Alignment - 1) & ~(Alignment - 1));
		}
		template <class T>
		inline T MXAlign1(const T Ptr, USIZE_TYPE Alignment)
		{
			return (T)((USIZE_TYPE)Ptr + Alignment - (Ptr & (Alignment - 1)));
		}
#else
#endif

		//==================================文件流操作=================================
		inline FILE* MXFopen(const TCHAR* pFileName, const TCHAR* openMode)
		{
			FILE* pFileHandle;
			errno_t err = _tfopen_s(&pFileHandle, pFileName, openMode);
			return pFileHandle;
		}
		inline bool MXFclose(FILE* fileHandle)
		{
			return fclose(fileHandle);
		}
		inline USIZE_TYPE MXRead(void* pBuffer, unsigned int uSize, unsigned int uCount, FILE* fileHandle)
		{
			return fread(pBuffer, uSize, uCount, fileHandle);
		}
		inline USIZE_TYPE MXWrite(const void* pBuffer, unsigned int uSize, unsigned int uCount, FILE* fileHandle)
		{
			//关于fwrite和 write区别， wirte系统调用， 调用write的时候， 先将数据写到操作系统内核缓冲区， 操作系统会定期将内核缓冲区的数据写回磁盘中。
			// fwrite每次都先将数据写入一个应用缓冲区中， 然后在调用write一次性把相应数据写进内核缓冲区中。
			// ptr − This is the pointer to the array of elements to be written.
			//	size − This is the size in bytes of each element to be written.
			//	nmemb − This is the number of elements, each one with a size of size bytes.
			//	stream − This is the pointer to a FILE object that specifies an output stream.
			return fwrite(pBuffer, uSize, uCount, fileHandle);
		}
		inline TCHAR* MXGetLine(TCHAR* pBuffer, int uSize, FILE* fileHandle)
		{
			return _fgetts(pBuffer, uSize, fileHandle);
		}
		inline int MXStat(const TCHAR* pFileName, struct _stat64i32* pStat)
		{
			return _tstat(pFileName, pStat);
		}
		inline bool MXFlush(FILE* fileHandle)
		{
			return fflush(fileHandle);
		}
		inline bool MXSeek(FILE* fileHandle, long offset, int origin)
		{
			return fseek(fileHandle, offset, origin);
		}
		//输入输出
		void MATRIX_PLATFORM_API MXOutputDebugString(const TCHAR* pcString, ...);
		inline void MXSprintf(TCHAR* _DstBuf, unsigned int _SizeInBytes, const TCHAR* _Format, ...)
		{
			char* pArgs;
			pArgs = (char*)&_Format + sizeof(_Format);
			_vstprintf_s(_DstBuf, _SizeInBytes, _Format, pArgs);
		}
		inline void MXSprintf(TCHAR* _DstBuf, unsigned int _SizeInBytes, const TCHAR* _Format, va_list pArgs)
		{
			_vstprintf_s(_DstBuf, _SizeInBytes, _Format, pArgs);
		}
		inline void MXSprintf(const TCHAR* _Format, ...)
		{
			char* pArgs = (char*)(&_Format) + sizeof(_Format);
			_vtprintf(_Format, pArgs);
		}
		inline void MXScanf(TCHAR* Buf, const TCHAR* _Format, TCHAR pArgs)
		{
			_stscanf_s(Buf, _Format, pArgs);
		}

		//==========================================内存处理相关==============================================
		inline bool MXMemcpy(void* pDest, const void* pSrc, USIZE_TYPE uiCountSize, USIZE_TYPE uiDestBufferSize = 0)
		{
			if (!uiDestBufferSize)
			{
				uiDestBufferSize = uiCountSize;
			}
			return (memcpy_s(pDest, uiDestBufferSize, pSrc, uiCountSize) == 0);
		}
		inline void MXMemset(void* pDest, int iC, USIZE_TYPE uCount)
		{
			memset(pDest, iC, uCount);
		}

		//========================================字符处理相关===========================
		inline unsigned int MXStrLen(const TCHAR* pStr)
		{
			//Returns the length of the C string str. (without including the terminating null character itself).
			return (unsigned int)_tcslen(pStr);
		}
		inline void MXStrCopy(TCHAR* pDest, unsigned int uCount, const TCHAR* pSource)
		{
			//Copies the C string pointed by source into the array pointed by destination, 
			//including the ** terminating null ** character and stopping at that point 
			_tcscpy_s(pDest, uCount, pSource);
		}
		inline int MXStrCmp(const TCHAR* String1, const TCHAR* String2)
		{
			return _tcscmp(String1, String2);
		}
		inline int MXStrnCmp(const TCHAR* String1, const TCHAR* String2, unsigned int uiMaxNum)
		{
			return _tcsncmp(String1, String2, uiMaxNum);
		}
		//Converts a sequence of multibyte characters to a corresponding sequence of wide characters.
		inline void MXMbsToWcs(wchar_t* Dest, unsigned int uiSizeInWord, const char* Source, unsigned int uiSizeInByte)
		{
			mbstowcs_s(0, Dest, uiSizeInWord, Source, uiSizeInByte);
		}
		inline void MXWcsToMbs(char* Dest, unsigned int uiSizeInByte, const wchar_t* Source, unsigned int uiSizeInWord)
		{
			wcstombs_s(0, Dest, uiSizeInByte, Source, uiSizeInWord);
		}
		inline bool MXIstalnum(TCHAR c)
		{
			//测试字符是否为数字或字母
			return _istalnum(c);
		}
		inline bool MXIsSpace(int c)
		{
			return _istspace(c);
		}
		inline void MXStrcat(TCHAR* pDest, unsigned int uSizeBuffer, const TCHAR* pSource)
		{
			// Note that the second parameter is the total size of the buffer, not the remaining size
			//在实际编写代码中经常出错，记住这个第二参数是pSource的bufferSize
			_tcscat_s(pDest, uSizeBuffer, pSource);
		}
		inline TCHAR* MXStrtok(TCHAR* strToken, const TCHAR* strDelimit, TCHAR** pContext)
		{
			////Find the next token in a string.
			return _tcstok_s(strToken, strDelimit, pContext);
		}
		inline const TCHAR* MXCsrchr(const TCHAR* pString, int c)
		{
			// Scan a string for the last occurrence of a character.
			return _tcsrchr(pString, c);
		}

		//======================================获取系统信息相关=================================
		inline unsigned int MXGetCpuNum()
		{
			SYSTEM_INFO SystemInfo;
#if _WIN64
			GetNativeSystemInfo(&SystemInfo);
#else
			GetSystemInfo(&SystemInfo);
#endif
			return SystemInfo.dwNumberOfProcessors;
		}

		inline bool MXIsMainThread()
		{
			return MatrixCore::msMainThreadID == GetCurrentThreadId();
		}

		inline void MXGetCurrentDirectory(TCHAR* CurDir)
		{
			GetCurrentDirectory(MAX_FILE_PATH_SIZE, CurDir);
		}
		inline void  MXGetModuleFilePath(TCHAR* pBuffer)
		{
			GetModuleFileName(NULL, pBuffer, MAX_FILE_PATH_SIZE);
		}
		inline TCHAR* MXGetCwd(TCHAR* pBuffer)
		{
			/*
			A non-negative integer that specifies the drive (0 = default drive, 1 = A, 2 = B, and so on).
			*/
			//getdcwd(0, pBuffer, MAX_FILE_PATH_SIZE);
			//getcwd(pBuffer, MAX_FILE_PATH_SIZE);
			return _tgetcwd(pBuffer, MAX_FILE_PATH_SIZE);
		}
		inline const TCHAR* MXGetExeFolderName()
		{
#if _WIN64
			return _T("x64");
			// return (TCHAR*)_T("x64");
#else
			return _T("Win32");
#endif
		}
		inline EPLATFORM GetCurPlatform()
		{
			return EPLATFORM::EP_Windows;
		}
		inline const TCHAR* GetCurPlatformName()
		{
			// return (TCHAR*)_T("Windows");
			return _T("Windows");
		}
		void MXSetCurrentDirectory(TCHAR* CurDir);
		void MXInitSystem();

		//===========================线程同步操作相关===================================
		inline long MXlockedCompareExchange(long* pDestination, long Exchange, long Comparand)
		{
			// InterlockedCompareExchange是把目标操作数（第1参数所指向的内存中的数）与一个值（第3参数）比较，如果相等，则用另一个值（第2参数）与目标操作数（第1参数所指向的内存中的数）交换；
			// InterlockedExchange是不比较直接交换。整个操作过程是锁定内存的，其它处理器不会同时访问内存，从而实现多处理器环境下的线程互斥
			return _InterlockedCompareExchange(pDestination, Exchange, Comparand);
		}
		inline long MXlockedAdd(long* pRefCount, long Value)
		{
			return _InterlockedExchangeAdd(pRefCount, Value);
		}
		inline long MXlockedExchange(long* pRefCount, long Value)
		{
			//能以原子操作的方式交换俩个参数a, b，并返回a以前的值；因为InterlockedExchange 是原子函数，不会要求中止中断，所以交换指针的方式是安全的。
			return _InterlockedExchange(pRefCount, Value);
		}
		inline long MXlockedOr(long* pRefCount, long Value)
		{
			return _InterlockedOr(pRefCount, Value);
		}
		inline long MXlockedXor(long* pRefCount, long Value)
		{
			return _InterlockedXor(pRefCount, Value);
		}
		inline long MXAtomicRead(long* pRefCount)
		{
			return MXlockedCompareExchange(pRefCount, 0, 0);
		}
		inline long MXAtomicWrite(long* pRefCount, long Value)
		{
			return MXlockedExchange(pRefCount, Value);
		}
		inline long MXLockedIncrement(long* pRefCount)
		{
			return _InterlockedIncrement(pRefCount);
		}
		inline long MXLockedDecrement(long* pRefCount)
		{
			return _InterlockedDecrement(pRefCount);
		}

		//线程局部变量： 如果需要在一个线程内部的各个函数调用都能访问、但其它线程不能访问的变量（被称为static memory local to a thread 线程局部静态变量，这就是TLS。
		unsigned int MXTlsAlloc();

		void* MXGetTlsValue(unsigned int TlsSolt);
		bool MXSetTlsValue(unsigned int TlsSolt, void* TlsValue);
		bool MXTlsFree(unsigned int TlsSolt);

		}
	}
