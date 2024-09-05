#ifndef CONVERTJSON_H
#define CONVERTJSON_H
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <exception>
#include <nlohmann/json.hpp>
#include "searchServer.h"
using json = nlohmann::json;
class RequestsMissing:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "File requests.json is missing";
    }
};
class RequestsEmpty:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "File requests.json is empty";
    }
};
class RequestsIncorrect:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Incorrect request structure";
    }
};

// Class for working with JSON files

class ConvertJson
{
public:
    ConvertJson();
    /*
     *  Method for getting file contents
     *  @return Returns a list with the contents of the files listed
     *  in config.json
     */
    std::vector<std::string> getTextDocuments();
    /*
     *  The method reads the max_responses field to determine the maximum
     *  number of responses per request
     *  @return a number equal to the maximum number of possible responses per request
     */
    int getResponsesLimit();
    /*
     *  Method for getting requests from requests.json file
     *  @return returns a list of requests from requests.json file
     */
    std::vector<std::string> getRequests();

    void setPutAnswers(const std::vector<std::vector<RelativeIndex> > &setSearch);
    void getPutAnswers();
private:
    std::vector<std::vector<RelativeIndex>> search;
    std::vector<std::string> textDocuments();
    int responsesLimit();
    std::vector<std::string> requests();
    /*
     *  Put the search results into the answers.json file
     */
    void putAnswers(const std::vector<std::vector<RelativeIndex>> &search);
};

#endif // CONVERTJSON_H
