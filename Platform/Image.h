#pragma once
#include "Core.h"
#include "MemoryManager.h"
#include "File.h"

namespace Matrix
{
	namespace Platform
	{
		class  MATRIX_PLATFORM_API  MImage
		{
		public:
			enum ImageFormat
			{
				IF_BMP,
				IF_TGA,
				IF_MAX
			};


			MImage();
			virtual ~MImage() = 0;
			virtual bool Load(const TCHAR* pFileName) = 0;
			virtual bool LoadFromBuffer(unsigned char* pBuffer, unsigned int uSize) = 0;
			virtual const unsigned char* GetPixel(unsigned int x, unsigned int y)const = 0;
			inline unsigned int GetBPP()const
			{
				return m_uiBPP;
			}
			inline unsigned int GetWidth()const
			{
				return m_uiWidth;
			}
			inline unsigned int GetHeight()const
			{
				return m_uiHeight;
			}
			inline const unsigned char* GetImg()const
			{
				return m_pImageData;
			}
			inline unsigned int GetImgDataSize()const
			{
				return m_uiDataSize;
			}
			inline unsigned char* GetPalette()const   // Return a pointer to VGA palette
			{
				return m_pPalette;
			}

		public:
			static TCHAR ms_ImageFormat[IF_MAX][10];
		protected:
			unsigned int m_uiWidth;
			unsigned int m_uiHeight;
			unsigned int m_uiBPP;
			unsigned char* m_pImageData;
			unsigned int m_uiDataSize;
			unsigned char* m_pData;
			unsigned char* m_pPalette;
		};

		class MATRIX_PLATFORM_API BMPImage : public MImage
		{
		public:
			BMPImage();
			~BMPImage();
			virtual bool Load(const TCHAR* pFilename);
			virtual bool LoadFromBuffer(unsigned char* pBuffer, unsigned int uSize);
			virtual const unsigned char* GetPixel(unsigned int x, unsigned int y)const;


		private:

			unsigned int m_uiEnc;

			unsigned int m_uiPlanes;
			unsigned int uiImgOffset;



			// Internal workers
			bool GetFile(const TCHAR* pFilename);
			bool ReadBmpHeader();
			bool LoadBmpRaw();
			bool LoadBmpRLE8();
			bool LoadBmpPalette();
			void FlipImg(); // Inverts image data, BMP is stored in reverse scanline order


		};


		class MATRIX_PLATFORM_API TGAImage : public MImage
		{
		public:
			TGAImage();
			~TGAImage();
			virtual bool Load(const TCHAR* pFilename);
			virtual bool LoadFromBuffer(unsigned char* pBuffer, unsigned int uiSize);
			virtual const unsigned char* GetPixel(unsigned int x, unsigned int y)const;
		private:

			unsigned char m_cEnc;


			// Internal workers
			bool ReadHeader();
			bool LoadRawData();
			bool LoadTgaRLEData();
			bool LoadTgaPalette();
			void BGRtoRGB();
			void FlipImg();
		};

		class MATRIX_PLATFORM_API DDSImage : public MImage
		{
		public:
			DDSImage()
			{

			}
			~DDSImage()
			{

			}
		};
	}
}


