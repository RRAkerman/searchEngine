#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H
#include "invertedindex.h"
struct RelativeIndex{
    std::size_t doc_id;
    float rank;

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
//Class for handling search queries
class SearchServer
{
public:
    /*
     *  @param idx a reference to the InvertedIndex, class is passed to the class constructor
     *  so that SearchServer can find out the frequency of words found in the query
     */
    SearchServer(InvertedIndex& idx);
    void setSearch(const std::vector<std::string>& setQueriesInput, const int &setResponsesLimit);
    std::vector<std::vector<RelativeIndex>> getSearch();
private:
    InvertedIndex _index;
    int responsesLimit = 0;
    std::vector<std::string> queriesInput;
    /*
     *  Method for processing search queries
     *  @param queries_input search queries taken from the file
     *  requests.json
     *  @return returns a sorted list of relevant answers for the given queries
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queriesInput, const int &responsesLimit);
};

#endif // SEARCHSERVER_H
