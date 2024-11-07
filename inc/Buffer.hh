// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_BUFFER_H_
#define _VECTORSIMGEN_BUFFER_H_

#include <memory>

#include <cstdint>
#include <memory>


namespace vsg
{
    class FixedSizeBuffer
    {
    protected:
        const size_t m_blockSize;
        std::uint8_t* m_blockData;
        std::unique_ptr<std::uint8_t> m_blockContainer;

    public:
        FixedSizeBuffer(size_t p_blockSize) noexcept
            : m_blockSize(p_blockSize), m_blockData(nullptr)
        {
            m_blockContainer.reset(new std::uint8_t[m_blockSize]);
            m_blockData = m_blockContainer.get();
        }

        ~FixedSizeBuffer() noexcept
        {

        }

        inline size_t 
        getSize() noexcept
        {
            return m_blockSize;
        }

        inline std::uint8_t* 
        getStartAddr() noexcept
        {
            return m_blockData;
        }

        inline std::uint8_t* 
        getOffsetAddr(uintptr_t p_offset) noexcept
        {
            uintptr_t startAddr = reinterpret_cast<uintptr_t>(m_blockData);
            return (reinterpret_cast<std::uint8_t*>(startAddr) + p_offset);
        }
    };

}

#endif