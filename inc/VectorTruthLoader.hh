// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_VECTOR_TRUTH_LOADER_H_
#define _VECTORSIMGEN_VECTOR_TRUTH_LOADER_H_


#include <memory>
#include <string>
#include <fstream>

#include <cstdint>

#include <vector>
#include <map>

#include "VectorOptions.hh"
#include "Logger.hh"

#define ENABLE_PRINTLOG 1


namespace vsg
{
    class VectorTruthLoader
    {
    protected:

        std::unique_ptr<Logger> m_logger;

        std::string m_filePath;
        
        std::vector<std::vector<std::int32_t>> m_truthVidList;
        std::vector<std::vector<float>> m_truthDistList;

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
        VectorTruthLoader() noexcept
        {
            m_logger.reset(new Logger("TruthLoader"));
            printLog(ENABLE_PRINTLOG, "TruthLoader initialized.");
        }

        virtual ~VectorTruthLoader() noexcept
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
        readTruthFile() noexcept
        {
            std::fstream vectorFile(m_filePath, std::ios::binary | std::ios::in);

            if (!vectorFile) {
                printWarn(ENABLE_PRINTLOG, "Loader cannot load fiile.");
                return;
            }

            size_t readOffset = 0;

            std::int32_t numCounts;
            std::int32_t numTopK;

            std::int32_t currentLoadedVectors = 0;

            vectorFile.seekg(0, std::ios::end);
            size_t fileSize = static_cast<size_t>(vectorFile.tellg());     

            vectorFile.seekg(readOffset, std::ios::beg);
            vectorFile.read((char*)&numCounts, sizeof(std::int32_t));
            readOffset += sizeof(std::int32_t);

            vectorFile.seekg(readOffset, std::ios::beg);
            vectorFile.read((char*)&numTopK, sizeof(std::int32_t));
            readOffset += sizeof(std::int32_t);

            size_t leftSize = fileSize - readOffset;

            if (ENABLE_PRINTLOG)
            {
                m_logger->getInstance().getLogger()->info("File info: numCounts({}), numTopK({})", numCounts, numTopK);
                m_logger->getInstance().getLogger()->info("Expected read size left: {}", leftSize);
            }

            std::int32_t currentCount = 0;
            for (currentCount = 0; currentCount < numCounts; currentCount++)
            {
                m_truthVidList.emplace_back(std::vector<int32_t>());

                for (int i = 0; i < numTopK; i++)
                {
                    std::int32_t vectorId;

                    vectorFile.seekg(readOffset, std::ios::beg);
                    vectorFile.read((char*)&vectorId, sizeof(std::int32_t));

                    readOffset += sizeof(std::int32_t);

                    m_truthVidList.back().emplace_back(vectorId);
                }
            }

            leftSize = fileSize - readOffset;

            if (ENABLE_PRINTLOG)
            {
                m_logger->getInstance().getLogger()->info("Loaded vector IDs.");
                m_logger->getInstance().getLogger()->info("Expected read size left: {}", leftSize);
            }

            for (currentCount = 0; currentCount < numCounts; currentCount++)
            {
                m_truthDistList.emplace_back(std::vector<float>());

                // size_t readSize = sizeof(float);
                for (int i = 0; i < numTopK; i++)
                {
                    float vectorDistance;

                    vectorFile.seekg(readOffset, std::ios::beg);
                    vectorFile.read((char*)&vectorDistance, sizeof(float));

                    readOffset += sizeof(float);

                    m_truthVidList.back().emplace_back(vectorDistance);
                }
            }

            leftSize = fileSize - readOffset;

            if (ENABLE_PRINTLOG)
            {
                m_logger->getInstance().getLogger()->info("Loaded distances.");
                m_logger->getInstance().getLogger()->info("Expected read size left: {}", leftSize);
            }
        }

    };
}

#endif