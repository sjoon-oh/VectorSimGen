#include <iostream>
#include <fstream>
#include <string>

#include "Logger.hh"
#include "VectorLoader.hh"


int main(int argc, char** argv)
{
    Logger::getInstance().getLogger()->info("VectorLoader Test");

    if (argc != 4)
    {
        Logger::getInstance().getLogger()->info("Wrong arguments.");
        return -1;
    }

    char* fileName = argv[1];
    int dimensionSize = std::stoi(std::string(argv[2]));
    int vectorType = std::stoi(std::string(argv[3]));

    vector_sim_gen::VectorLoader vectorLoader;
    vectorLoader.setFilePath(fileName);
    
    // vectorLoader.setVectorInfo(
    //     vector_sim_gen::VECTOR_TYPE_INT8_T, dimensionSize);

    vectorLoader.setVectorInfo(vectorType, dimensionSize);
    vectorLoader.readVectorFile();

    std::map<size_t, size_t> dupCheckMap;

    size_t dupCounts = vectorLoader.checkVectorDuplicates(dupCheckMap);
    Logger::getInstance().getLogger()->info("Check for {} duplicates: {}", fileName, dupCounts);

    if (dupCounts > 0)
    {        
        std::fstream dupfileLog("duplicate-file.csv", std::ios::out);

        if (!dupfileLog)
        {
            Logger::getInstance().getLogger()->warn("Log file failed to open.");
            return -2;
        }

        for (auto& elem: dupCheckMap)
        {
            dupfileLog << elem.first << "\t" << elem.second << std::endl;
        }

        Logger::getInstance().getLogger()->info("Map size: {}", dupCheckMap.size());

        dupfileLog.close();
    }

    return 0;
}