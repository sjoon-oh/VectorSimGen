// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_VECTORLOADER_H_
#define _VECTORSIMGEN_VECTORLOADER_H_


#include <memory>
#include <string>
#include <fstream>

#include <cstdint>

#include <vector>

#include "Logger.hh"

#define ENABLE_PRINTLOG 1


namespace vector_sim_gen
{
    class FixedSizeBuffer
    {
    protected:
        const size_t m_blockSize;
        std::uint8_t* m_blockData;
        std::unique_ptr<std::uint8_t> m_blockContainer;

    public:
        FixedSizeBuffer(size_t p_blockSize) noexcept
            : m_blockSize(p_blockSize)
        {
            m_blockContainer.reset(new std::uint8_t[m_blockSize]);
        }

        ~FixedSizeBuffer() noexcept
        {

        }

        inline const size_t getSize() noexcept
        {
            return m_blockSize;
        }

        inline const std::uint8_t* getStartAddr() noexcept
        {
            return m_blockData;
        }

        inline const std::uint8_t* getOffsetAddr(uintptr_t p_offset) noexcept
        {
            uintptr_t startAddr = reinterpret_cast<uintptr_t>(m_blockData);
            return (reinterpret_cast<std::uint8_t*>(startAddr) + p_offset);
        }
    };

    enum {
        VECTOR_TYPE_UINT8_T = 0,
        VECTOR_TYPE_FLOAT_T
    };

    class VectorLoader
    {
    protected:

        std::unique_ptr<Logger> m_logger;

        std::string m_filePath;
        std::vector<FixedSizeBuffer> m_vectorList;

        std::uint32_t m_typeSize;
        std::uint32_t m_dimensionSize;

        void printLog(bool p_enable, char* p_message) noexcept
        {
            if (p_enable)
                m_logger->getLogger()->info(p_message);
        }

        void printWarn(bool p_enable, char* p_message) noexcept
        {
            if (p_enable)
                m_logger->getLogger()->warn(p_message);
        }

    public:
        VectorLoader() noexcept
        {
            m_logger.reset(new Logger("Loader"));
            printLog(ENABLE_PRINTLOG, "Loader initialized.");
        }

        virtual ~VectorLoader() noexcept
        {

        }

        void setFilePath(const char* p_filePath) noexcept
        {
            m_filePath = p_filePath;
        }

        std::string& getFilePath() noexcept
        {
            return m_filePath;
        }

        void setVectorInfo(std::uint32_t p_vectorType, std::uint32_t p_dimensionSize)
        {
            switch (p_vectorType)
            {
                case VECTOR_TYPE_UINT8_T:
                    
            }


            m_dimensionSize = p_dimensionSize;
        }

        void readVectorFile() noexcept
        {
            // Default (Binary form)
            // <4 bytes int representing num_vectors>
            // <4 bytes int representing num_dimension>
            // <num_vectors * num_dimension * sizeof(data type) bytes raw data>

            std::fstream vectorFile(m_filePath, std::ios::binary | std::ios::in);

            if (!vectorFile) {
                printWarn(ENABLE_PRINTLOG, "Loader cannot load fiile.");
                return;
            }

            vectorFile.seekg(0, std::ios::end);
            size_t fileSize = static_cast<size_t>(vectorFile.tellg());

            // m_bufferRegion.reset(new FixedSizeBuffer(fileSize));

            // Testing it as the default (binary) type.
            std::int32_t numVectors;
            std::int32_t numDimension;

            // Return the position to the start.
            vectorFile.seekg(0, std::ios::beg);

            size_t readOffset = 0;
            while (fileSize != readOffset)
            {
                vectorFile.read(&numVectors, sizeof(std::int32_t));
                readOffset += sizeof(std::int32_t);
                
                vectorFile.read(&numDimension, sizeof(std::int32_t));
                readOffset += sizeof(std::int32_t);



                readOffset += sizeof(numDimension);

            }

// if (offset != UINT64_MAX) m_handle->seekg(offset, std::ios::beg);
// m_handle->read((char*)buffer, readSize);
// return m_handle->gcount();







        }

        
    };
}

#endif