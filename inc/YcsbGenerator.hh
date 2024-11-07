// 
// Author: Sukjoon Oh

#ifndef _VECTORSIMGEN_YCSB_WRAPPER_H_
#define _VECTORSIMGEN_YCSB_WRAPPER_H_

#include <string>
#include <memory>


#include "YCSB-C/core/generator.h"
#include "YCSB-C/core/uniform_generator.h"
#include "YCSB-C/core/zipfian_generator.h"
#include "YCSB-C/core/scrambled_zipfian_generator.h"
#include "YCSB-C/core/skewed_latest_generator.h"
#include "YCSB-C/core/const_generator.h"


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


    class DistGenerator
    {
    protected:
        struct DistributionType m_distType;
        
        std::unique_ptr<ycsbc::CounterGenerator> m_keyGenerator;
        std::unique_ptr<ycsbc::Generator<std::uint64_t>> m_keyChooser;

        size_t m_recordCount;
        ycsbc::CounterGenerator m_insertKeySequence;

    public:

        DistGenerator(char* p_distType, size_t p_recordCount) noexcept
            : m_recordCount(p_recordCount), m_insertKeySequence(3)
        {
            m_distType.m_type = p_distType;
            m_insertKeySequence.Set(m_recordCount);

            m_keyGenerator.reset(new ycsbc::CounterGenerator(0));
                // Insert start fixed to zero.

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
        std::unique_ptr<DistGenerator> distGenerator;

    public:

        YcsbStyleGenerator()
        {

        }

        virtual ~YcsbStyleGenerator()
        {

        }


    };
}


#endif


