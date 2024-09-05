#include "../include/mainFile.h"
#include "../include/convertJson.h"
#include "../include/invertedindex.h"
#include "../include/searchServer.h"
void workTheEngine(MainFiles &sEngine, ConvertJson &jConvert, InvertedIndex &iInvert)
{
    sEngine.getEngineConfig();
    while(true)
    {
        std::cout << "1.Search" << std::endl;
        std::cout << "2.Update database" << std::endl;
        std::cout << "3.Stop engine" << std::endl;
        std::cout << "Command no.: ";
        std::size_t command = 0;
        std::cin >> command;
        if(command == 1)
        {
            iInvert.setUpdateDocumentBase(jConvert.getTextDocuments());
            iInvert.getUpdateDocumentBase();

            SearchServer sServer(iInvert);
            sServer.setSearch(jConvert.getRequests(), jConvert.getResponsesLimit());

            jConvert.setPutAnswers(sServer.getSearch());
            jConvert.getPutAnswers();
        }
        else if(command == 2)
            sEngine.getUpdateFiles();
        else if(command == 3)
            break;
        else
            std::cerr << "command not found" << std::endl;
    }
}
int main()
{
    MainFiles sEngine;
    ConvertJson jConvert;
    InvertedIndex iInvert;
    workTheEngine(sEngine, jConvert, iInvert);

    return 0;
}
