// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_OPTION_H_
#define _VECTORSIMGEN_OPTION_H_

#include <cstdint>
#include <array>


namespace vsg
{
    enum {
        VECTOR_TYPE_UINT8_T     = 0,
        VECTOR_TYPE_INT8_T      ,
        VECTOR_TYPE_FLOAT_T     ,
        VECTOR_TYPE_UNKNOWN
    };

    struct VectorTypeInfo
    {
        std::string m_typeStr;
        size_t m_typeSize;

        VectorTypeInfo(std::string p_typeStr, size_t p_typeSize)
            : m_typeStr(p_typeStr), m_typeSize(p_typeSize)
        {
            
        }
    };

    struct VectorFileDefaultTemplate
    {
        std::int32_t m_numVec;
        std::int32_t m_dimSize;
        std::uint8_t* m_vectors;
    };

    std::array<struct VectorTypeInfo, 4> g_vectorTypes{
        VectorTypeInfo{"uint8", sizeof(std::uint8_t)},
        VectorTypeInfo{"int8", sizeof(std::int8_t)},
        VectorTypeInfo{"float", sizeof(float)},
        VectorTypeInfo{"", sizeof(0)}

    };

    namespace option
    {
        size_t
        getVectorSize(std::string p_vectorTypeString)
        {
            size_t typeSize = 0;
            for (auto& typeInfo: g_vectorTypes)
            {
                if (typeInfo.m_typeStr == p_vectorTypeString)
                {
                    typeSize = typeInfo.m_typeSize;
                    break;
                }
            }

            return typeSize;
        }
    }


}

#endif