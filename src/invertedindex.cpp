#include "../include/invertedindex.h"
InvertedIndex::InvertedIndex() {}
std::mutex blockAccess;
void InvertedIndex::setUpdateDocumentBase(const std::vector<std::string> &setInputDocs)
{
    inputDocs = setInputDocs;
}
void InvertedIndex::getUpdateDocumentBase()
{
    return updateDocumentBase(inputDocs);
}
void InvertedIndex::setWordCount(const std::string &setWord)
{
    word = setWord;
}
std::vector<Entry> InvertedIndex::getWordCount()
{
    return wordCount(word);
}
std::map<std::string,std::vector<Entry>> InvertedIndex::getFreq()
{
    return freq_dictionary;
}

void InvertedIndex::updateDocumentBase(const std::vector<std::string> &inputDocs)
{
    std::vector<std::thread> threadStorage;
    const std::size_t maxWords = 1000;
    auto sortText = [&](const std::string &filePath)
    {
        std::ifstream file(filePath,std::ios_base::in);
        std::string parseFile;
        char simbol;
        bool gap = true;
        while(file.get(simbol))
        {
            if(simbol >= 'a' && simbol <= 'z' || simbol >= 'A' && simbol <= 'Z')
            {
                parseFile.push_back(simbol);
                gap = true;
            }
            else
            {
                if(gap)
                {
                    parseFile.push_back(' ');
                    gap = false;
                }
            }
        }
        std::transform(parseFile.begin(), parseFile.end(),parseFile.begin(), tolower);
        std::stringstream ssFile(parseFile);
        std::string line;
        std::vector<std::string> wordStorage;
        while (std::getline(ssFile, line, ' '))
        {
            if(line.length() <= 100)
            {
                if(wordStorage.size() < maxWords)
                    wordStorage.push_back(line);
                else
                    break;
            }

        }
        std::size_t countWord = 0;
        std::string wordsInDocument;
        for(const auto &i : wordStorage)
        {
            wordsInDocument += i;
            ++countWord;
            if(countWord < maxWords)
                wordsInDocument += " ";
        }
        docs.push_back(wordsInDocument);
    };
    for(const auto &filePath : inputDocs)
    {
        sortText(filePath);
    }
    auto indexText = [&](const std::string &fileDoc)
    {
        std::stringstream iStr(fileDoc);
        std::string iLine;
        while(std::getline(iStr,iLine, ' '))
        {
            Entry entry;
            std::vector<Entry> creatEntry;
            std::size_t countI = 0;
            for(const auto &j : docs)
            {
                std::size_t countJ = 1;
                std::stringstream jStr(j);
                std::string jLine;
                while(std::getline(jStr,jLine,' '))
                {
                    if(iLine == jLine)
                    {
                        ++countJ;
                    }
                }
                entry.doc_id = countI;
                entry.count = countJ;
                creatEntry.push_back(entry);
                ++countI;
            }
            blockAccess.lock();
            auto wPair = std::make_pair(iLine,creatEntry);
            freq_dictionary.insert(wPair);
            blockAccess.unlock();
        }
    };
    for(const auto i : docs)
    {
        threadStorage.push_back(std::thread(indexText,i));
    }
    for(auto &j : threadStorage)
        j.join();
}
std::vector<Entry> InvertedIndex::wordCount(const std::string &word)
{
    Entry entry{};
    std::vector<Entry> entryWord;
    for(const auto &[i,j]: freq_dictionary)
    {
        if(i == word)
        {
            for(const auto &g : j)
            {
                if(g.count != 1)
                {
                    entry.doc_id = g.doc_id;
                    entry.count = g.count - 1;
                    entryWord.push_back(entry);
                }
            }
        }
    }
    return entryWord;
}




