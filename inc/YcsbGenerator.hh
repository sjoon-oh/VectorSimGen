// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_YCSB_WRAPPER_H_
#define _VECTORSIMGEN_YCSB_WRAPPER_H_

#include <string>
#include <memory>
#include <random>

#include <iostream>
#include <fstream>

#include <cstdarg>


#include "YCSB-C/core/generator.h"
#include "YCSB-C/core/uniform_generator.h"
#include "YCSB-C/core/zipfian_generator.h"
#include "YCSB-C/core/scrambled_zipfian_generator.h"
#include "YCSB-C/core/skewed_latest_generator.h"
#include "YCSB-C/core/const_generator.h"

#include "Logger.hh"
#include "Buffer.hh"
#include "VectorOptions.hh"
#include "VectorBaseLoader.hh"

#define ENABLE_LOGGER

namespace vsg 
{
    struct DistributionType
    {
        std::string m_type;

        DistributionType() = default;
        DistributionType(std::string p_type) noexcept
            : m_type(p_type)
        {
            
        }
    };

#ifdef ENABLE_LOGGER
    #define LOG_INFO(FMT, ...)    \
        do { m_logger->getLogger()->info((FMT), __VA_ARGS__); } while(0)
    #define LOG_WARN(FMT, ...)    \
        do { m_logger->getLogger()->warn((FMT), __VA_ARGS__); } while(0)
#else
    #define LOG_INFO(FMT, ...)    \
        do { } while(0)
    #define LOG_WARN(FMT, ...)    \
        do { } while(0)

#endif


    class DistGenerator
    {
    protected:
        std::unique_ptr<Logger> m_logger;

        struct DistributionType m_distType;
        
        std::unique_ptr<ycsbc::CounterGenerator> m_keyGenerator;
        std::unique_ptr<ycsbc::Generator<std::uint64_t>> m_keyChooser;

        size_t m_recordCount;
        ycsbc::CounterGenerator m_insertKeySequence;

    public:

        DistGenerator(char* p_distType, size_t p_recordCount) noexcept
            : m_recordCount(p_recordCount), m_insertKeySequence(3)
        {
#ifdef ENABLE_LOGGER            
            m_logger.reset(new Logger("m_distGenerator"));
#else
            m_logger.reset();
#endif

            m_distType.m_type = p_distType;
            m_insertKeySequence.Set(m_recordCount);

            m_keyGenerator.reset(new ycsbc::CounterGenerator(0));
                // Insert start fixed to zero.

            LOG_INFO("Set keyChooser distribution: {}", m_distType.m_type);

            if (m_distType.m_type == "uniform")
            {
                m_keyChooser.reset(new ycsbc::UniformGenerator(0, m_recordCount - 1));
            }

            else if (m_distType.m_type == "zipfian")
            {
                // Do not assume any inserts for now.
                int opCount = 0;
                int newKeys = 0;
                m_keyChooser.reset(new ycsbc::ScrambledZipfianGenerator(m_recordCount));
            }

            else if (m_distType.m_type == "latest")
            {
                m_keyChooser.reset(new ycsbc::SkewedLatestGenerator(m_insertKeySequence));
            }

            else
                m_keyChooser.reset();
        }
        
        virtual ~DistGenerator() noexcept
        {
            m_keyGenerator.reset();
            m_keyChooser.reset();
        }

        std::uint64_t
        generateNextKey() noexcept
        {
            std::uint64_t keyNum = m_keyGenerator->Next();
            return keyNum;
        }

        std::uint64_t
        chooseNextKey() noexcept
        {
            std::uint64_t keyNum = 0;
            if (m_keyChooser.get() != nullptr)
            {   
                do
                {
                    keyNum = m_keyChooser->Next();
                } 
                while (keyNum > m_insertKeySequence.Last());
            }
            return keyNum;
        }

        inline size_t
        getRecordCount() noexcept
        {
            return m_recordCount;
        }

    };


    class YcsbStyleGenerator
    {
    private:
        std::unique_ptr<Logger> m_logger;
        std::unique_ptr<DistGenerator> m_distGenerator;

        // Load base vector here.
        std::vector<std::unique_ptr<FixedSizeBuffer>> m_vectorList;


        // 
        // Assumes that the list of the base vectors are placed by its order of IDs.
        std::vector<std::uint64_t> m_vectorBaseSequence;
        std::vector<std::uint64_t> m_vectorQuerySequence;

    public:

        YcsbStyleGenerator(char* p_distType, size_t p_recordCount)
        {
#ifdef ENABLE_LOGGER
            m_logger.reset(new Logger("YcsbStyleGenerator"));
#else
            m_logger.reset();
#endif

            // 
            // Reset new
            m_distGenerator.reset(new DistGenerator(p_distType, p_recordCount));
        }

        virtual ~YcsbStyleGenerator()
        {

        }


        void
        loadBaseVector(std::uint8_t* p_src, size_t p_numVec, size_t p_vecSize) noexcept
        {
            // p_vecSize : Dimension * Type size() for each vector.
            size_t readSize = 0;
            const size_t totalReadSize = p_vecSize * p_numVec;

            while (readSize < totalReadSize)
            {
                uint8_t* addr = p_src + readSize;

                m_vectorList.emplace_back(new FixedSizeBuffer(p_vecSize));
                std::memcpy(m_vectorList.back()->getStartAddr(), addr, p_vecSize);

                readSize += p_vecSize;
            }

            LOG_INFO("Vector loaded to the YcsbStyleGenerator: {} vectors.", m_vectorList.size());
        }



        size_t 
        generateRandomBaseVector(
            struct VectorTypeInfo& p_vecInfo, 
            size_t p_numVec, 
            size_t p_numDim,
            struct VectorFileDefaultTemplate& p_vecTemplate) noexcept
        {
            std::mt19937 engine(0);
            std::uniform_int_distribution<std::uint8_t> dist(0, 255);
            
            p_vecTemplate.m_numVec = p_numVec;
            p_vecTemplate.m_dimSize = p_numDim;

            size_t vectorBytes = (p_numVec * p_vecInfo.m_typeSize * p_vecTemplate.m_dimSize);
            p_vecTemplate.m_vectors = new uint8_t[vectorBytes];

            if (p_vecTemplate.m_vectors == nullptr)
                return 0;

            size_t totalBytes = sizeof(std::int32_t) + sizeof(std::int32_t) + vectorBytes;

            LOG_INFO("Filling random values as vectors.", "");

            for (size_t byteOffset = 0; byteOffset < vectorBytes; byteOffset++)
            {
                p_vecTemplate.m_vectors[byteOffset] = dist(engine);

#ifdef ENABLE_LOGGER                
                std::cout << "\r\tProgress: " << (byteOffset * 100.0 / vectorBytes) << "%\t\t";
#endif
            }
#ifdef ENABLE_LOGGER 
                std::cout << std::endl;
#endif

            LOG_INFO("Generated base: {} typed {} vectors (dim: {}), {} bytes.", 
                    p_vecInfo.m_typeStr,
                    p_vecTemplate.m_numVec,
                    p_vecTemplate.m_dimSize,
                    vectorBytes
                );
            
            return p_numVec;
        }


        void
        exportQuerySequenceDist() noexcept
        {
            std::map<std::uint64_t, size_t> countMap;
            std::multimap<size_t, uint64_t, std::greater<size_t>> reversedMap;

            size_t totalNumVec = m_vectorQuerySequence.size();

            for (auto& vecID: m_vectorQuerySequence)
            {   

                if (countMap.find(vecID) != countMap.end())
                    countMap[vecID] += 1;
                
                else
                    countMap.insert(std::make_pair(vecID, 1));
            }
            
            for (const auto& pair : countMap) {
                reversedMap.insert(std::make_pair(pair.second, pair.first));
            }

            std::ofstream outputFileGen("generator-vecID-dist.txt");

            LOG_INFO("Exporting {}, total query size of {}", "generator-vecID-dist.txt", totalNumVec);

            for (const auto& pair : reversedMap) {
                outputFileGen << pair.second << "\t" << pair.first << std::endl;
            }
            
            outputFileGen.close();
        }


        std::vector<std::uint64_t>*
        generateQuerySequence(size_t p_numQueryVec) noexcept
        {
            if (m_distGenerator == nullptr)
                return nullptr;

            size_t totalVecNum = m_vectorList.size();
            for (size_t count = 0; count < totalVecNum; count++)
            {
                std::uint64_t vectorID = m_distGenerator->generateNextKey();
                m_vectorBaseSequence.emplace_back(vectorID);
            }

            LOG_INFO("Mapping the base vector ID sequence: {} total", totalVecNum);

            for (size_t count = 0; count < p_numQueryVec; count++)
            {
                std::uint64_t vectorID = m_distGenerator->chooseNextKey();
                m_vectorQuerySequence.emplace_back(vectorID);
            }
            return &(m_vectorQuerySequence);
        }


        std::vector<std::uint64_t>*
        generateQueryIndexSequence(size_t p_numQueryVec) noexcept
        {
            if (m_distGenerator == nullptr)
                return nullptr;

            size_t totalVecNum = p_numQueryVec;
            LOG_INFO("Mapping query vector ID sequence: {} total", totalVecNum);

            for (size_t count = 0; count < p_numQueryVec; count++)
            {
                std::uint64_t vectorID = m_distGenerator->chooseNextKey();
                m_vectorQuerySequence.emplace_back(vectorID);
            }
            return &(m_vectorQuerySequence);
        }


        void
        generateExactQuerySequenceFile(size_t p_numQueryVec, const char* p_filePath = "query.default-type.bin") noexcept
        {
            if (m_vectorList.size() == 0)
            {
                generateQuerySequence(p_numQueryVec);
            }

            std::fstream outQueryFile(p_filePath, std::ios::binary | std::ios::out);

            if (!outQueryFile)
            {
                LOG_WARN("Binary file write failed.", "");
                return;
            }

            LOG_INFO("Exporting {}", p_filePath);

            char statusPrintBuffer[512] = { 0, };

            size_t totalVecNum = m_vectorQuerySequence.size();
            
            size_t currCount = 0;
            size_t writeSize = 0;
            for (auto& vectorId: m_vectorQuerySequence)
            {

                FixedSizeBuffer* vectorBuffer = m_vectorList[vectorId].get();
                uint8_t* vectorBufferStart = vectorBuffer->getStartAddr();

                outQueryFile.seekp(writeSize, std::ios::beg);
                outQueryFile.write(
                        (char*)vectorBufferStart, 
                        vectorBuffer->getSize()
                    );

                writeSize += vectorBuffer->getSize();

                std::sprintf(statusPrintBuffer, "\rWrite progress: %.3lf", currCount * 100.0 / totalVecNum);
                std::cout << statusPrintBuffer; 

                currCount++;

                std::memset(statusPrintBuffer, 0, sizeof(statusPrintBuffer));
            }

            std::cout << "\n";

            outQueryFile.close();
        }

    };
}


#endif


