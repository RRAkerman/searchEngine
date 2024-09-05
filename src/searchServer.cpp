#include "../include/searchServer.h"

SearchServer::SearchServer(InvertedIndex &idx) : _index(idx){ }

void SearchServer::setSearch(const std::vector<std::string> &setQueriesInput, const int &setResponsesLimit)
{
    queriesInput = setQueriesInput;
    responsesLimit = setResponsesLimit;
}

std::vector<std::vector<RelativeIndex> > SearchServer::getSearch()
{
    return search(queriesInput,responsesLimit);
}

std::vector<std::vector<RelativeIndex> > SearchServer::search(const std::vector<std::string> &queriesInput, const int &responsesLimit)
{
    std::vector<std::vector<RelativeIndex>>relevanceDataArray;
    RelativeIndex rIndex;
    std::size_t maxWord = 1000;

    const std::size_t countAnswers = responsesLimit;
    auto strRank = [&maxWord](const float &searchRank)
    {
        float shortFloat = (float)searchRank/maxWord;
        std::string newRank = std::to_string(shortFloat);
        while(newRank.length() > 5)
            newRank.pop_back();
        return std::atof(newRank.c_str());
    };
    if(queriesInput.size() > 0)
    {
        for(const auto &i : queriesInput)
        {
            std::stringstream str(i);
            std::string iLine;
            std::map<std::size_t,float> findAMatch;
            std::vector<RelativeIndex> sortVector;
            while(std::getline(str, iLine, ' '))
            {
                _index.setWordCount(iLine);
                for(const auto &j : _index.getWordCount())
                {
                    auto wPair = std::make_pair(j.doc_id,strRank(j.count));
                    auto findWord = findAMatch.find(wPair.first);
                    if(findWord != findAMatch.end())
                    {
                        findWord->second += wPair.second;
                    }
                    else
                        findAMatch.insert(wPair);
                }
            }
            for(const auto &[x,y] : findAMatch)
            {
                rIndex.doc_id = x;
                rIndex.rank = y;
                if(sortVector.size() < countAnswers)
                    sortVector.push_back(rIndex);
            }
            sort(sortVector.begin(),sortVector.end(),[](const RelativeIndex &i, const RelativeIndex &j){ return i.rank > j.rank; });
            relevanceDataArray.push_back(sortVector);
        }
    }

    return relevanceDataArray;
}

