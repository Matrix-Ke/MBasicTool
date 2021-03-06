#include "Synchronize.h"
#include "MemoryManager.h"

using namespace Matrix::Platform;
MCriticalSection gSafeOutputString;

unsigned int MSynchronize::WaitAll(MSynchronize** pSynchronize, unsigned int uiNum, bool bWaitAll, DWORD dwMilliseconds)
{
	ENGINE_ASSERT(uiNum >= 1 && uiNum <= MAXIMUM_WAIT_OBJECTS);
	static HANDLE handle[MAXIMUM_WAIT_OBJECTS];
	for (unsigned int i = 0; i < uiNum; i++)
	{
		handle[i] = (HANDLE)pSynchronize[i]->GetHandle();
	}
	DWORD dw = WaitForMultipleObjects(uiNum, handle, bWaitAll, dwMilliseconds);
	switch (dw)
	{
	case WAIT_FAILED:
		return WF_FAILED;
	case WAIT_TIMEOUT:
		return WF_TIMEOUT;
	case WAIT_OBJECT_0:
		return WF_OBJECT0;
	}
	return WF_FAILED;
}

void MSynchronize::MXSafeOutputDebugString(const TCHAR* pString, ...)
{
	MCriticalSection::Locker Temp(gSafeOutputString);
	char* pArgs;
	pArgs = (char*)&pString + sizeof(pString);
	// todo list: 了解如何设计日志系统
	_vstprintf_s(MatrixCore::msLogbuffer, LOG_BUFFER_SIZE, pString, pArgs);
	OutputDebugString(MatrixCore::msLogbuffer);
}

MXSemaphore::MXSemaphore(unsigned int uCount, unsigned int maxCount)
{
	ENGINE_ASSERT(uCount <= maxCount);
	//
	mSemaphore = CreateSemaphore(NULL, uCount, maxCount, NULL);

	mMaxCount = maxCount;
}

Matrix::Platform::MXSemaphore::~MXSemaphore()
{
	BOOL closed = CloseHandle((HANDLE)mSemaphore);
	ENGINE_ASSERT(closed);
	mSemaphore = NULL;
}

void Matrix::Platform::MXSemaphore::Enter()
{
	// WAIT_OBJECT_0, 表示等待的对象有信号（对线程来说，表示执行结束）；
	// WAIT_TIMEOUT, 表示等待指定时间内，对象一直没有信号（线程没执行完）；
	// WAIT_ABANDONED 表示对象有信号，但还是不能执行  一般是因为未获取到锁或其他原因
	//  result:
	//    WAIT_ABANDONED (0x00000080)
	//    WAIT_OBJECT_0  (0x00000000), signaled
	//    WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
	//    WAIT_FAILED    (0xFFFFFFFF), not signaled
	DWORD result = WaitForSingleObject((HANDLE)mSemaphore, INFINITE);
	ENGINE_ASSERT(result);
}

void Matrix::Platform::MXSemaphore::Leave(unsigned int uiReleaseCount)
{
	BOOL released = ReleaseSemaphore(HANDLE(mSemaphore), uiReleaseCount, NULL);
}

Matrix::Platform::MXMutex::MXMutex()
{
	mMutex = CreateMutex(NULL, FALSE, NULL);
	ENGINE_ASSERT(mMutex);
}

Matrix::Platform::MXMutex::~MXMutex()
{
	BOOL closed = CloseHandle((HANDLE)mMutex);
	ENGINE_ASSERT(closed);
	mMutex = NULL;
}

void Matrix::Platform::MXMutex::Enter()
{
	// result:
	//   WAIT_ABANDONED (0x00000080)
	//   WAIT_OBJECT_0  (0x00000000), signaled
	//   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
	//   WAIT_FAILED    (0xFFFFFFFF), not signaled
	DWORD result = WaitForSingleObject((HANDLE)mMutex, INFINITE);
	ENGINE_ASSERT(result != WAIT_FAILED);
}

void Matrix::Platform::MXMutex::Leave()
{
	BOOL released = ReleaseMutex(HANDLE(mMutex));
	ENGINE_ASSERT(released);
}

Matrix::Platform::MEvent::MEvent()
{
	mEvent = NULL;
}

Matrix::Platform::MEvent::~MEvent()
{
	if (mEvent != NULL)
	{
		CloseHandle(mEvent);
	}
}

void Matrix::Platform::MEvent::Lock()
{
	WaitForSingleObject(mEvent, INFINITE);
}

void Matrix::Platform::MEvent::unLock()
{
	PulseEvent(mEvent);
}

bool Matrix::Platform::MEvent::Create(bool bManualReset, const TCHAR* InName)
{
	mEvent = CreateEvent(NULL, bManualReset, 0, InName);
	return mEvent != NULL;
}

void Matrix::Platform::MEvent::Trigger(void)
{
	SetEvent(mEvent);
}

void Matrix::Platform::MEvent::Reset(void)
{
	ResetEvent(mEvent);
}

void Matrix::Platform::MEvent::Pulse(void)
{
	PulseEvent(mEvent);
}

bool Matrix::Platform::MEvent::Wait(DWORD WaitTime)
{
	return WaitForSingleObject(mEvent, WaitTime) == WAIT_OBJECT_0;
}

bool Matrix::Platform::MEvent::IsTrigger()
{
	return Wait(0);
}

Matrix::Platform::MXTlsValue::MXTlsValue()
{
	MCriticalSection::Locker lockgurad(mCriticalSection);
	mSlot = MXTlsAlloc();
	ENGINE_ASSERT(mSlot != 0XFFFFFFFF);
}

Matrix::Platform::MXTlsValue::~MXTlsValue()
{
	ENGINE_ASSERT(mSlot != 0XFFFFFFFF);
	for (size_t i = 0; i < mThreadValueNum; i++)
	{
		ENGINE_DELETE(pThreadValue[i]);
	}
	MXTlsFree(mSlot);
}

void Matrix::Platform::MXTlsValue::SetThreadValue(void* pValue)
{
	MCriticalSection::Locker Temp(mCriticalSection);
	pThreadValue[mThreadValueNum] = (StackMemoryManager*)pValue;
	mThreadValueNum++;
	MXSetTlsValue(mSlot, pValue);
}

void* Matrix::Platform::MXTlsValue::GetThreadValue()
{
	return MXGetTlsValue(mSlot);
}
