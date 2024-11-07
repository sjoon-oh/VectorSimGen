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
        std::string m_type;
        size_t m_size;

        VectorTypeInfo(std::string p_type, size_t p_size)
            : m_type(p_type), m_size(p_size)
        {
            
        }
    };

    std::array<struct VectorTypeInfo, 4> g_vectorTypes{
        VectorTypeInfo{"uint8", sizeof(std::uint8_t)},
        VectorTypeInfo{"int8", sizeof(std::int8_t)},
        VectorTypeInfo{"float", sizeof(float)},
        VectorTypeInfo{"", sizeof(0)}

    };

    namespace option
    {
        std::uint32_t
        getVectorSize(std::string p_vectorTypeString)
        {
            size_t typeSize = 0;
            for (auto& typeInfo: g_vectorTypes)
            {
                if (typeInfo.m_type == p_vectorTypeString)
                {
                    typeSize = typeInfo.m_size;
                    break;
                }
            }

            return typeSize;
        }
    }


}

#endif