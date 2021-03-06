#pragma once
#ifndef USE_STL_TYPE_TRAIT
#define USE_STL_TYPE_TRAIT
#endif //USE_STL_TYPE_TRAIT
#ifndef USE_MATRIX_NEW
#define USE_MATRIX_NEW
#endif // !USE_MATRIX_NEW
#include "Platform/MemoryManager.h"

#pragma warning(disable : 4251)

#ifdef Container_EXPORTS
#define MATRIX_CONTAINER_API __declspec(dllexport)
#else
#define MATRIX_CONTAINER_API __declspec(dllimport)
#endif // Container_EXPORTS

// container 是所有容器的基类， 申请的空间会大于实际需求空间，以避免频繁释放申请。
//只有有实际需求空间的时候才会调用对应的元素的构造函数。 所以申请空间未必调用构造，释放未必调用析构函数。
namespace Matrix
{

	namespace Container
	{
		template <class KEY, class VALUE>
		class MapElement : public Platform::MemoryAllcManager
		{
		public:
			KEY Key;
			VALUE Value;
			void operator=(const MapElement<KEY, VALUE>& Element)
			{
				Key = Element.Key;
				Value = Element.Value;
			}
			MapElement()
			{
			}
			MapElement(const MapElement<KEY, VALUE>& Element)
			{
				Key = Element.Key;
				Value = Element.Value;
			}
			MapElement(const KEY& _Key, const VALUE& _Value)
			{
				Key = _Key;
				Value = _Value;
			}
			~MapElement()
			{
			}
		};
		template <class KEY, class VALUE, class N>
		void Merge(MapElement<KEY, VALUE>* pBuffer, MapElement<KEY, VALUE>* TempBuffer, unsigned int uiIndex0, unsigned int uiIndexLength0, unsigned int uiIndexLength1, N Compare)
		{

			unsigned int uiIndex1 = uiIndex0 + uiIndexLength0;

			unsigned int uiEnd0 = uiIndexLength0 + uiIndex0;
			unsigned int uiEnd1 = uiIndex1 + uiIndexLength1;

			unsigned int uiTempIndex = uiIndex0;
			while (uiIndex0 < uiEnd0 && uiIndex1 < uiEnd1)
			{
				if (Compare(pBuffer[uiIndex0], pBuffer[uiIndex1]) == 0)
				{

					TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
					uiIndex1++;
				}
				else
				{
					TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
					uiIndex0++;
				}
				uiTempIndex++;
			}

			while (uiIndex0 < uiEnd0)
			{

				TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
				uiTempIndex++;
				uiIndex0++;
			}
			while (uiIndex1 < uiEnd1)
			{
				TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
				uiTempIndex++;
				uiIndex1++;
			}
		}
		template <class KEY, class VALUE, class N>
		void MergeSort(MapElement<KEY, VALUE>* pBuffer, MapElement<KEY, VALUE>* TempBuffer, unsigned int uiBufferLength, N Compare)
		{
			unsigned int uiDetLength = 1;
			unsigned int uiNumSwap = 0;
			while (uiDetLength < uiBufferLength)
			{
				unsigned int uiLastDetLength = uiDetLength;
				uiDetLength = uiDetLength << 1;
				unsigned int i = 0;
				for (; i + uiDetLength < uiBufferLength; i = i + uiDetLength)
				{
					Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLastDetLength, Compare);
				}

				if (i < uiBufferLength)
				{
					unsigned int uiLeftLength = uiBufferLength - i;
					if (uiLeftLength > uiLastDetLength)
					{
						Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLeftLength - uiLastDetLength, Compare);
					}
					else
					{
						Merge(pBuffer, TempBuffer, i, uiLeftLength, 0, Compare);
					}
				}
				Swap(pBuffer, TempBuffer);
				uiNumSwap++;
			}
			if ((uiNumSwap % 2) != 0)
			{
				Platform::MXMemcpy(TempBuffer, pBuffer, sizeof(MapElement<KEY, VALUE>) * uiBufferLength);
			}
		}
		template <class KEY, class VALUE>
		void Merge(MapElement<KEY, VALUE>* pBuffer, MapElement<KEY, VALUE>* TempBuffer, unsigned int uiIndex0, unsigned int uiIndexLength0, unsigned int uiIndexLength1)
		{

			unsigned int uiIndex1 = uiIndex0 + uiIndexLength0;

			unsigned int uiEnd0 = uiIndexLength0 + uiIndex0;
			unsigned int uiEnd1 = uiIndex1 + uiIndexLength1;

			unsigned int uiTempIndex = uiIndex0;
			while (uiIndex0 < uiEnd0 && uiIndex1 < uiEnd1)
			{
				if (pBuffer[uiIndex0].Key > pBuffer[uiIndex1].Key)
				{

					TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
					uiIndex1++;
				}
				else
				{
					TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
					uiIndex0++;
				}
				uiTempIndex++;
			}

			while (uiIndex0 < uiEnd0)
			{

				TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
				uiTempIndex++;
				uiIndex0++;
			}
			while (uiIndex1 < uiEnd1)
			{
				TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
				uiTempIndex++;
				uiIndex1++;
			}
		}
		template <class KEY, class VALUE>
		void MergeSort(MapElement<KEY, VALUE>* pBuffer, MapElement<KEY, VALUE>* TempBuffer, unsigned int uiBufferLength)
		{
			unsigned int uiDetLength = 1;
			unsigned int uiNumSwap = 0;
			while (uiDetLength < uiBufferLength)
			{
				unsigned int uiLastDetLength = uiDetLength;
				uiDetLength = uiDetLength << 1;
				unsigned int i = 0;
				for (; i + uiDetLength < uiBufferLength; i = i + uiDetLength)
				{
					Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLastDetLength);
				}

				if (i < uiBufferLength)
				{
					unsigned int uiLeftLength = uiBufferLength - i;
					if (uiLeftLength > uiLastDetLength)
					{
						Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLeftLength - uiLastDetLength);
					}
					else
					{
						Merge(pBuffer, TempBuffer, i, uiLeftLength, 0);
					}
				}
				Swap(pBuffer, TempBuffer);
				uiNumSwap++;
			}
			if ((uiNumSwap % 2) != 0)
			{
				Platform::MXMemcpy(TempBuffer, pBuffer, sizeof(MapElement<KEY, VALUE>) * uiBufferLength);
			}
		}

		template <class T>
		void Merge(T* pBuffer, T* TempBuffer, unsigned int uiIndex0, unsigned int uiIndexLength0, unsigned int uiIndexLength1)
		{

			unsigned int uiIndex1 = uiIndex0 + uiIndexLength0;

			unsigned int uiEnd0 = uiIndexLength0 + uiIndex0;
			unsigned int uiEnd1 = uiIndex1 + uiIndexLength1;

			unsigned int uiTempIndex = uiIndex0;
			while (uiIndex0 < uiEnd0 && uiIndex1 < uiEnd1)
			{
				if (pBuffer[uiIndex0] > pBuffer[uiIndex1])
				{

					TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
					uiIndex1++;
				}
				else
				{
					TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
					uiIndex0++;
				}
				uiTempIndex++;
			}

			while (uiIndex0 < uiEnd0)
			{

				TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
				uiTempIndex++;
				uiIndex0++;
			}
			while (uiIndex1 < uiEnd1)
			{
				TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
				uiTempIndex++;
				uiIndex1++;
			}
		}
		template <class T>
		void MergeSort(T* pBuffer, T* TempBuffer, unsigned int uiBufferLength)
		{
			unsigned int uiDetLength = 1;
			unsigned int uiNumSwap = 0;
			while (uiDetLength < uiBufferLength)
			{
				unsigned int uiLastDetLength = uiDetLength;
				uiDetLength = uiDetLength << 1;
				unsigned int i = 0;
				for (; i + uiDetLength < uiBufferLength; i = i + uiDetLength)
				{
					Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLastDetLength);
				}

				if (i < uiBufferLength)
				{
					unsigned int uiLeftLength = uiBufferLength - i;
					if (uiLeftLength > uiLastDetLength)
					{
						Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLeftLength - uiLastDetLength);
					}
					else
					{
						Merge(pBuffer, TempBuffer, i, uiLeftLength, 0);
					}
				}
				Swap(pBuffer, TempBuffer);
				uiNumSwap++;
			}
			if ((uiNumSwap % 2) != 0)
			{
				Platform::MXMemcpy(TempBuffer, pBuffer, sizeof(T) * uiBufferLength);
			}
		}

		template <class T, class N>
		void Merge(T* pBuffer, T* TempBuffer, unsigned int uiIndex0, unsigned int uiIndexLength0, unsigned int uiIndexLength1, N Compare)
		{

			unsigned int uiIndex1 = uiIndex0 + uiIndexLength0;

			unsigned int uiEnd0 = uiIndexLength0 + uiIndex0;
			unsigned int uiEnd1 = uiIndex1 + uiIndexLength1;

			unsigned int uiTempIndex = uiIndex0;
			while (uiIndex0 < uiEnd0 && uiIndex1 < uiEnd1)
			{
				if (Compare(pBuffer[uiIndex0], pBuffer[uiIndex1]) == 0)
				{

					TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
					uiIndex1++;
				}
				else
				{
					TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
					uiIndex0++;
				}
				uiTempIndex++;
			}

			while (uiIndex0 < uiEnd0)
			{

				TempBuffer[uiTempIndex] = pBuffer[uiIndex0];
				uiTempIndex++;
				uiIndex0++;
			}
			while (uiIndex1 < uiEnd1)
			{
				TempBuffer[uiTempIndex] = pBuffer[uiIndex1];
				uiTempIndex++;
				uiIndex1++;
			}
		}
		template <class T, class N>
		void MergeSort(T* pBuffer, T* TempBuffer, unsigned int uiBufferLength, N Compare)
		{
			unsigned int uiDetLength = 1;
			unsigned int uiNumSwap = 0;
			while (uiDetLength < uiBufferLength)
			{
				unsigned int uiLastDetLength = uiDetLength;
				uiDetLength = uiDetLength << 1;
				unsigned int i = 0;
				for (; i + uiDetLength < uiBufferLength; i = i + uiDetLength)
				{
					Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLastDetLength, Compare);
				}

				if (i < uiBufferLength)
				{
					unsigned int uiLeftLength = uiBufferLength - i;
					if (uiLeftLength > uiLastDetLength)
					{
						Merge(pBuffer, TempBuffer, i, uiLastDetLength, uiLeftLength - uiLastDetLength, Compare);
					}
					else
					{
						Merge(pBuffer, TempBuffer, i, uiLeftLength, 0, Compare);
					}
				}
				Math::Swap(pBuffer, TempBuffer);
				uiNumSwap++;
			}
			if ((uiNumSwap % 2) != 0)
			{
				Platform::MXMemcpy(TempBuffer, pBuffer, sizeof(T) * uiBufferLength);
			}
		}
		template <class T, class MemoryManagerClass = Platform::DefaultContainerMemoryAllocator>
		class MContainer : public Platform::MemoryAllcManager
		{
		protected:
			//单纯用于申请空间
			T* New(unsigned int uiNum)
			{
				if (!uiNum)
				{
					return NULL;
				}
				T* pPtr = (T*)m_MemManagerObject.Allocate(uiNum * sizeof(T), 0, true);
				ENGINE_ASSERT(pPtr);
				if (!pPtr)
				{
					return NULL;
				}

				return pPtr;
			}

			void Delete(T*& pPtr, unsigned int uiNum)
			{
				if (!pPtr)
				{
					return;
				}
				if (uiNum > 0)
				{
					if (Platform::ValueBase<T>::NeedsDestructor)
					{
						for (unsigned int i = 0; i < uiNum; i++)
						{
							(pPtr + i)->~T();
						}
					}
				}

				m_MemManagerObject.Deallocate((char*)pPtr, 0, true);
				pPtr = NULL;
			}

		public:
			MemoryManagerClass m_MemManagerObject;
		};
	}
}
