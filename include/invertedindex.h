#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
struct Entry {
    std::size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
//Class for creating an inverted index for documents
class InvertedIndex
{
public:
    InvertedIndex();

    void setUpdateDocumentBase(const std::vector<std::string> &setInputDocs);
    void getUpdateDocumentBase();
    void setWordCount(const std::string &setWord);
    std::vector<Entry> getWordCount();
    /*
     *  @return frequency dictionary of words in documents
     */
    std::map<std::string,std::vector<Entry>> getFreq();
private:
    std::vector<std::string> inputDocs;
    std::string word;
    std::vector<std::string> docs;  //list of document contents
    std::map<std::string,std::vector<Entry>> freq_dictionary;   //frequency dictionary
    /*
     *  Update or fill the document database, which we will search
     *  @param texts_input document contents
     */
    void updateDocumentBase(const std::vector<std::string> &inputDocs);
    /*
     *  The method determines the number of occurrences of the word word in the loaded document database
     *  @param word is the word whose frequency of occurrence needs to be determined
     *  @return returns the prepared list with the frequency of words
     */
    std::vector<Entry> wordCount(const std::string &word);
};

#endif // INVERTEDINDEX_H
