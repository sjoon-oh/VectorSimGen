// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_VECTOR_QUERY_LOADER_H_
#define _VECTORSIMGEN_VECTOR_QUERY_LOADER_H_


#include <memory>
#include <string>
#include <fstream>

#include <cstdint>

#include <vector>
#include <map>

#include "Buffer.hh"
#include "VectorOptions.hh"
#include "Logger.hh"

#define ENABLE_PRINTLOG 1


namespace vsg
{
    class VectorBaseLoader
    {
    protected:

        std::unique_ptr<Logger> m_logger;

        std::string m_filePath;
        std::vector<std::unique_ptr<FixedSizeBuffer>> m_vectorList;
        
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
        VectorBaseLoader() noexcept
        {
            m_logger.reset(new Logger("BaseLoader"));
            printLog(ENABLE_PRINTLOG, "BaseLoader initialized.");
        }

        virtual ~VectorBaseLoader() noexcept
        {

        }

        void 
        setFilePath(const char* p_filePath) noexcept
        {
            m_filePath = p_filePath;
        }

        std::string& 
        getFilePath() noexcept
        {
            return m_filePath;
        }

        void 
        setVectorInfo(std::uint32_t p_typeSize, std::uint32_t p_dimensionSize)
        {
            m_typeSize = p_typeSize;
            m_dimensionSize = p_dimensionSize;
        }

        void 
        readVectorFile() noexcept
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

            // Testing it as the default (binary) type.
            std::int32_t numVectors;
            std::int32_t numDimension;

            std::int32_t currentLoadedVectors = 0;

            // Return the position to the start.
            vectorFile.seekg(0, std::ios::beg);

            if (ENABLE_PRINTLOG)
            {
                m_logger->getInstance().getLogger()->info("File size: {} Bytes", fileSize);
            }

            size_t readOffset = 0;
            
            vectorFile.seekg(readOffset, std::ios::beg);
            vectorFile.read((char*)&numVectors, sizeof(std::int32_t));
            readOffset += sizeof(std::int32_t);

            vectorFile.seekg(readOffset, std::ios::beg);
            vectorFile.read((char*)&numDimension, sizeof(std::int32_t));
            readOffset += sizeof(std::int32_t);

            size_t readSize = (numDimension * (int32_t)m_typeSize);

            if (ENABLE_PRINTLOG)
            {
                m_logger->getInstance().getLogger()->info("File info: numVec({}), vecDim({})", numVectors, numDimension);

                size_t expectedRawVecSize = (fileSize - sizeof(numVectors) - sizeof(numDimension));
                double expectedNumVectors = (1.0 * expectedRawVecSize) / numDimension;

                if (numDimension != m_dimensionSize)
                {
                    printWarn(ENABLE_PRINTLOG, "Dimension mismatch.");
                    return;
                }

                m_logger->getInstance().getLogger()->info("Expected total vectors: {}, Next read size {}", expectedNumVectors, readSize);
            }

            while (fileSize > readOffset)
            {
                m_vectorList.emplace_back(new FixedSizeBuffer(readSize));

                std::uint8_t* targetReadBuffer = m_vectorList.back()->getStartAddr();

                vectorFile.seekg(readOffset, std::ios::beg);
                vectorFile.read((char*)targetReadBuffer, readSize);

                readOffset += readSize;

                currentLoadedVectors++;


                // if (ENABLE_PRINTLOG)
                // {
                //     m_logger->getInstance().getLogger()->info(
                //         "Loading #{}: {} Byte Offset / {} Bytes (Read: {} Bytes)", currentLoadedVectors, readOffset, fileSize, readSize);
                // }
            }

            vectorFile.close();
        }


        const size_t
        checkVectorDuplicates(std::map<size_t, size_t>& p_dupCountMap) noexcept
        {
            bool foundDup;
            std::map<size_t, size_t> localDupMap; // Only to remove multiple counts.

            for (size_t curIdx = 0; curIdx < m_vectorList.size() - 1; curIdx++)
            {
                foundDup = false;

                // If previously viewed, skip.
                if (localDupMap.find(curIdx) != localDupMap.end())
                    continue;

                else 
                {
                    for (size_t cmpIdx = curIdx + 1; cmpIdx < m_vectorList.size(); cmpIdx++)
                    {
                        auto* curBuffer = m_vectorList[curIdx].get();
                        auto* cmpBuffer = m_vectorList[cmpIdx].get();

                        if (curBuffer->getSize() != cmpBuffer->getSize())
                            continue;

                        int rc = std::memcmp(
                            curBuffer->getStartAddr(),
                            cmpBuffer->getStartAddr(),
                            curBuffer->getSize()
                        );

                        if (rc == 0)
                        {
                            if (!foundDup) 
                            {
                                foundDup = true;
                                p_dupCountMap.insert(std::make_pair(curIdx, 2));
                                localDupMap.insert(std::make_pair(cmpIdx, 0));
                            }
                            else
                            {
                                p_dupCountMap[curIdx]++;
                                localDupMap.insert(std::make_pair(cmpIdx, 0));
                            }
                        }
                    }
                }

                if (!foundDup)
                    p_dupCountMap.insert(std::make_pair(curIdx, 1));
            }

            return p_dupCountMap.size();
        }

    };
}

#endif