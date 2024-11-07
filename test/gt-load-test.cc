#include <iostream>
#include <fstream>
#include <string>

#include "Logger.hh"
#include "VectorOptions.hh"
#include "VectorTruthLoader.hh"


int main(int argc, char** argv)
{
    Logger::getInstance().getLogger()->info("VectorTruthLoader Test");

    if (argc != 4)
    {
        Logger::getInstance().getLogger()->info("Wrong arguments.");
        return -1;
    }

    char* fileName = argv[1];
    int dimensionSize = std::stoi(std::string(argv[2]));
    int typeSize = vsg::option::getVectorSize(std::string(argv[3]));

    vsg::VectorTruthLoader vectorLoader;
    vectorLoader.setFilePath(fileName);
    
    // vectorLoader.setVectorInfo(
    //     vsg::VECTOR_TYPE_INT8_T, dimensionSize);

    vectorLoader.setVectorInfo(typeSize, dimensionSize);
    vectorLoader.readTruthFile();

    // std::map<size_t, size_t> dupCheckMap;

    // size_t dupCounts = vectorLoader.checkVectorDuplicates(dupCheckMap);
    // Logger::getInstance().getLogger()->info("Check for {} duplicates: {}", fileName, dupCounts);

    // if (dupCounts > 0)
    // {        
    //     std::fstream dupfileLog("duplicate-file.csv", std::ios::out);

    //     if (!dupfileLog)
    //     {
    //         Logger::getInstance().getLogger()->warn("Log file failed to open.");
    //         return -2;
    //     }

    //     for (auto& elem: dupCheckMap)
    //     {
    //         dupfileLog << elem.first << "\t" << elem.second << std::endl;
    //     }

    //     Logger::getInstance().getLogger()->info("Map size: {}", dupCheckMap.size());

    //     dupfileLog.close();
    // }

    return 0;
}