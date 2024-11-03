#include <iostream>
#include <string>

#include "Logger.hh"
#include "VectorLoader.hh"


int main()
{
    Logger::getInstance().getLogger()->info("VectorLoader Test");

    vector_sim_gen::VectorLoader vectorLoader;
    vectorLoader.setFilePath("./dataset/spacev1b/query.bin");
    
    vectorLoader.setVectorInfo(
        vector_sim_gen::VECTOR_TYPE_INT8_T, 100);
    vectorLoader.readVectorFile();

    return 0;
}