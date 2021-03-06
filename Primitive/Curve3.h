#pragma once
#include "Line3.h"
#include "Math/Matrix3.h"
#include "Platform/MemoryManager.h"
/*
曲线类

*/
namespace Matrix
{
    namespace Primitive
    {
        class MATRIX_PRIMITIVE_API Curve3 : public Platform::MemoryAllcManager
        {
        public:
            enum // CURVE TYPE
            {
                CT_SEGMENT,
                CT_CONTROL,
                CT_MAX
            };
            Curve3();
            virtual ~Curve3() = 0;

            virtual unsigned int GetCurveType() = 0;
            //获得FrenetFrame3个方向
            virtual void GetFrenetFrameBNT(float t, Math::Vector3 &B, Math::Vector3 &N, Math::Vector3 &T) = 0;
            //获得FixedUp3个方向
            void GetFixedUpBNT(float t, Math::Vector3 &B, Math::Vector3 &N, Math::Vector3 &T);
            //求导数
            virtual Math::Vector3 GetFirstDerivative(float t) = 0;
            virtual Math::Vector3 GetSecondDerivative(float t) = 0;
            virtual Math::Vector3 GetThirdDerivative(float t) = 0;
            //求长度
            virtual float GetLength(float t1, float t2, unsigned int uiIterations) = 0;
            //求点
            virtual Math::Vector3 GetPoint(float t) = 0;
            //求总长
            virtual float GetTotalLength(unsigned int uiIterations) = 0;
            //根据长度得到时间
            virtual float GetTime(float fLength, unsigned int iIterations = 32,
                                   float fTolerance = EPSILON_E4) = 0;
            //求曲率
            virtual float GetCurvature(float fTime) = 0;
            //求转矩
            virtual float GetTorsion(float fTime) = 0;
        };
    }
}