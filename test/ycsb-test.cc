#include <iostream>
#include <fstream>
#include <string>

#include <functional>
#include <map>
// #include <multimap>

#include "Logger.hh"
#include "YcsbGenerator.hh"


int main()
{
    size_t recordCount = 1000000;
    size_t queryCount = 1000000;
    vsg::DistGenerator distGenerator("zipfian", recordCount);
    
    Logger::getInstance().getLogger()->info("YcsbStyleGenerator test.");

    std::map<std::uint64_t, size_t> countMap;
    std::multimap<size_t, uint64_t, std::greater<size_t>> reversedMap;

    for (int i = 0; i < recordCount; i++)
    {   
        std::uint64_t nextKey = distGenerator.generateNextKey();

        if (countMap.find(nextKey) != countMap.end())
            countMap[nextKey] += 1;
        
        else
            countMap.insert(std::make_pair(nextKey, 1));
    }
    
    for (const auto& pair : countMap) {
        reversedMap.insert(std::make_pair(pair.second, pair.first));
    }

    std::ofstream outputFileGen("generator-test-keylist.txt");

    for (const auto& pair : reversedMap) {
        outputFileGen << pair.second << "\t" << pair.first << std::endl;
    }
    
    outputFileGen.close();

    // -----
    countMap.clear();
    reversedMap.clear();

    for (int i = 0; i < queryCount; i++)
    {   
        std::uint64_t nextKey = distGenerator.chooseNextKey();

        if (countMap.find(nextKey) != countMap.end())
            countMap[nextKey] += 1;
        
        else
            countMap.insert(std::make_pair(nextKey, 1));
    }
    
    for (const auto& pair : countMap) {
        reversedMap.insert(std::make_pair(pair.second, pair.first));
    }

    std::ofstream outputFile("generator-test-query.txt");

    for (const auto& pair : reversedMap) {
        outputFile << pair.second << "\t" << pair.first << std::endl;
    }
    
    outputFile.close();

    return 0;
}

