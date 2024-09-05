#include "../include/convertJson.h"

ConvertJson::ConvertJson() {}

std::vector<std::string> ConvertJson::getTextDocuments()
{
    return textDocuments();
}

int ConvertJson::getResponsesLimit()
{
    return responsesLimit();
}

std::vector<std::string> ConvertJson::getRequests()
{
    return requests();
}

void ConvertJson::setPutAnswers(const std::vector<std::vector<RelativeIndex> > &setSearch)
{
    search = setSearch;
}

void ConvertJson::getPutAnswers()
{
    return putAnswers(search);
}
std::vector<std::string> ConvertJson::textDocuments()
{
    auto findConfigPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\json\\config.json";
        const std::string linuxPath = "../../../json/config.json";
        const std::string voidPath{};
        if (std::filesystem::is_regular_file(windowsPath))
            return windowsPath;
        else
            if(std::filesystem::is_regular_file(linuxPath))
                return linuxPath;
        return voidPath;
    };
    const std::string config = findConfigPath();
    std::vector<std::string> pathsStorage;
    std::ifstream openConfig(config,std::ios_base::in);
    if(openConfig.is_open())
    {
        if(openConfig.peek() != EOF)
        {
            json parseConfig = json::parse(openConfig);
            openConfig.close();
            openConfig.clear();
            auto findFiles = parseConfig.find("files");
            if(findFiles != parseConfig.end())
            {
                json openFiles = *findFiles;
                for(auto i = openFiles.begin();i != openFiles.end();++i)
                {
                    pathsStorage.push_back(*i);
                }
                std::sort(pathsStorage.begin(), pathsStorage.end());
            }
        }
    }
    else
        std::cerr << "Config file is missing" << std::endl;
    return pathsStorage;
}

int ConvertJson::responsesLimit()
{
    auto findConfigPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\json\\config.json";
        const std::string linuxPath = "../../../json/config.json";
        const std::string voidPath{};
        if (std::filesystem::is_regular_file(windowsPath))
            return windowsPath;
        else
            if(std::filesystem::is_regular_file(linuxPath))
                return linuxPath;
        return voidPath;
    };
    const std::string config = findConfigPath();
    int maxResponses = 0;
    std::ifstream openConfig(config, std::ios_base::in);
    if(openConfig.is_open())
    {
        json parseConfig = json::parse(openConfig);
        openConfig.close();
        openConfig.clear();
        auto findConfig = parseConfig.find("config");
        json openConfigFile = *findConfig;
        auto findMaxResponses = openConfigFile.find("max_responses");
        maxResponses = *findMaxResponses;
    }
    else
        std::cerr << "Config file is missing" << std::endl;
    return maxResponses;
}

std::vector<std::string> ConvertJson::requests()
{
    auto findRequestsPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\json\\requests.json";
        const std::string linuxPath = "../../../json/requests.json";
        const std::string voidPath{};
        if (std::filesystem::is_regular_file(windowsPath))
            return windowsPath;
        else
            if(std::filesystem::is_regular_file(linuxPath))
                return linuxPath;
        return voidPath;
    };
    const std::string requests = findRequestsPath();
    try
    {
        std::vector<std::string> requestsStorrage;
        std::ifstream openRequests(requests,std::ios_base::in);
        if(openRequests.is_open())
        {
            if(openRequests.peek() != EOF)
            {
                const std::size_t maxWords = 1000;
                const std::size_t maxSize = 1000;
                auto requestCheck = [&](const std::string &request)
                {
                    bool simbolCheck = true;
                    for(const auto &i : request)
                        if(i >= 'z' && i <= 'a')
                            return false;
                    std::stringstream dropRequest(request);
                    std::string word;
                    std::size_t countWord = 0;
                    while(std::getline(dropRequest,word, ' '))
                    {
                        if(word.length() > 100 || countWord > maxWords)
                            return false;
                        ++countWord;
                    }
                    return true;
                };
                json parseRequests = json::parse(openRequests);
                openRequests.close();
                openRequests.clear();
                auto findRequests = parseRequests.find("requests");
                if(findRequests != parseRequests.end())
                {
                    json readRequests = *findRequests;

                    if(!readRequests.empty())
                    {
                        if(readRequests.size() > maxSize)
                            std::cerr << "File requests.json is too big" << std::endl;
                        else
                        {
                            for(const auto &j : readRequests)
                            {
                                if(!requestCheck(j))
                                {
                                    std::cerr << "The request does not match the parameters:" << std::endl;
                                    std::cerr << j << std::endl;
                                }
                                else
                                    requestsStorrage.push_back(j);
                            }
                        }

                        return requestsStorrage;
                    }
                    else
                        throw RequestsEmpty();
                }
                else
                    throw RequestsIncorrect();
            }
            else
                throw RequestsEmpty();

        }
        else
            throw RequestsMissing();
    }
    catch(const RequestsMissing &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(const RequestsEmpty &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(const RequestsIncorrect &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ConvertJson::putAnswers(const std::vector<std::vector<RelativeIndex>> &search)
{
    json createAnswers;
    json answersFile;
    std::size_t count = 0;
    auto strRank = [](const float &searchRank){
        std::string newRank = std::to_string(searchRank);
        while(newRank.length() > 5)
            newRank.pop_back();
        return std::atof(newRank.c_str());
    };
    for(const auto &i : search)
    {
        json jsonI = json::array();
        json jsonJ = json::array();
        json jsonK;
        if(i.size() > 0)
        {
            for(const auto &j : i)
            {
                jsonI.push_back({{"docid",j.doc_id},{"rank",strRank(j.rank)}});
            }
            jsonJ.push_back({{"result","true"}});
            if(i.size() > 1)
                jsonJ.push_back({"relevance", jsonI});
            else
                jsonJ.push_back({jsonI});
        }
        else
            jsonJ.push_back({{"result","false"}});
        jsonK.push_back(json::object_t::value_type("request" + std::to_string(count),jsonJ));
        createAnswers.push_back(jsonK);
        ++count;
    }
    answersFile.push_back(json::object_t::value_type("answers",createAnswers));
    auto findAnswersPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\json";
        const std::string linuxPath = "../../../json";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            const std::string windowsPathAnswers = windowsPath + "\\answers.json";
            return windowsPathAnswers;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
            {
                const std::string linuxPathAnswers = linuxPath + "/answers.json";
                return linuxPathAnswers;
            }
        }
        return voidPath;
    };
    const std::string answers = findAnswersPath();
    std::ofstream openAnswersFile(answers, std::ios_base::out);
    if(openAnswersFile.is_open())
    {
        openAnswersFile << answersFile;
        openAnswersFile.close();
        openAnswersFile.clear();
        std::cout << "complied" << std::endl;
    }
    else
        std::cerr << "Error writing file. Invalid file path" << std::endl;
}

