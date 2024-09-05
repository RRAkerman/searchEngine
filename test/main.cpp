#define CATCH_CONFIG_MAIN
#include <iostream>
#include <filesystem>
#include "gtest/gtest.h"
#include "../include/invertedindex.h"
#include "../include/searchServer.h"
using namespace std;
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}
void TestInvertedIndexFunctionality(
    const vector<string>& docs,
    const vector<string>& requests,
    const std::vector<vector<Entry>>& expected
    ) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.setUpdateDocumentBase(docs);
    idx.getUpdateDocumentBase();
    for(const auto& request : requests) {
        idx.setWordCount(request);
        std::vector<Entry> word_count = idx.getWordCount();
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    auto findTestPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\test\\testFiles";
        const std::string linuxPath = "../../../test/testFiles";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            return 1;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
                return 2;
        }
        return 3;
    };
    vector<string> findDocs;
    if(findTestPath() == 1)
    {
        findDocs = {
            "..\\..\\..\\..\\test\\testFiles\\testBasic\\test0.txt",
            "..\\..\\..\\..\\test\\testFiles\\testBasic\\test1.txt"
        };
    }
    else if(findTestPath()==2)
    {
        findDocs = {
            "../../../test/testFiles/testBasic/test0.txt",
            "../../../test/testFiles/testBasic/test1.txt"
        };
    }

    const vector<string> docs = findDocs;
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = {
        {
            {0, 1}
        },
        {
            {0, 1}, {1, 3}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2) {
    auto findTestPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\test\\testFiles";
        const std::string linuxPath = "../../../test/testFiles";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            return 1;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
                return 2;
        }
        return 3;
    };
    vector<string> findDocs;
    if(findTestPath() == 1)
    {
        findDocs = {
            "..\\..\\..\\..\\test\\testFiles\\TestBasic2TestSimple\\test0.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestBasic2TestSimple\\test1.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestBasic2TestSimple\\test2.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestBasic2TestSimple\\test3.txt",
        };
    }
    else if(findTestPath() == 2)
    {
        findDocs = {
            "../../../test/testFiles/TestBasic2TestSimple/test0.txt",
            "../../../test/testFiles/TestBasic2TestSimple/test1.txt",
            "../../../test/testFiles/TestBasic2TestSimple/test2.txt",
            "../../../test/testFiles/TestBasic2TestSimple/test3.txt"
        };
    }
    const vector<string> docs = findDocs;
    const vector<string> requests = {"milk", "water", "cappuccino"};
    const vector<vector<Entry>> expected = {
        {
            {0, 4}, {1, 1}, {2, 5}
        }, {
            {0, 3}, {1, 2}, {2, 5}
        }, {
            {3, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    auto findTestPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\test\\testFiles";
        const std::string linuxPath = "../../../test/testFiles";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            return 1;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
                return 2;
        }
        return 3;
    };
    vector<string> findDocs;
    if(findTestPath() == 1)
    {
        findDocs = {
            "..\\..\\..\\..\\test\\testFiles\\TestInvertedIndexMissingWord\\test0.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestInvertedIndexMissingWord\\test1.txt"
        };
    }
    else if(findTestPath() == 2)
    {
        findDocs = {
            "../../../test/testFiles/TestInvertedIndexMissingWord/test0.txt",
            "../../../test/testFiles/TestInvertedIndexMissingWord/test1.txt"
        };
    }
    const vector<string> docs = findDocs;
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = {
        {

        },
        {
                {1, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseSearchServer, TestSimple) {
    auto findTestPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\test\\testFiles";
        const std::string linuxPath = "../../../test/testFiles";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            return 1;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
                return 2;
        }
        return 3;
    };
    vector<string> findDocs;
    if(findTestPath() == 1)
    {
        findDocs = {
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file0.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file1.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file2.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file3.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file4.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file5.txt",
        };
    }
    else if(findTestPath() == 2)
    {
        findDocs = {
            "../../../test/testFiles/TestSimpleTestTop5/file0.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file1.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file2.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file3.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file4.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file5.txt"
        };
    }
    const vector<string> docs = findDocs;
    int responsesLimit = 5;
    const vector<string> request = {"subaru wrx sti", "toyota chaser","abc bca", "mercedes benz amg"};
    const std::vector<vector<RelativeIndex>> expected = {
        {
            {0, 0.059},{4, 0.001}
        },
        {
            {1, 0.045},{4, 0.006}
        },
        {

        },
        {
            {5, 0.113},{2, 0.021}
        }

    };
    InvertedIndex idx;
    idx.setUpdateDocumentBase(docs);
    idx.getUpdateDocumentBase();
    SearchServer srv(idx);
    srv.setSearch(request,responsesLimit);
    std::vector<vector<RelativeIndex>> result = srv.getSearch();
    ASSERT_EQ(result, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    auto findTestPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\test\\testFiles";
        const std::string linuxPath = "../../../test/testFiles";
        const std::string voidPath{};
        if (std::filesystem::is_directory(windowsPath))
        {
            return 1;
        }
        else
        {
            if (std::filesystem::is_directory(linuxPath))
                return 2;
        }
        return 3;
    };
    vector<string> findDocs;
    if(findTestPath() == 1)
    {
        findDocs = {
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file0.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file1.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file2.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file3.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file4.txt",
            "..\\..\\..\\..\\test\\testFiles\\TestSimpleTestTop5\\file5.txt",
        };
    }
    else if(findTestPath() == 2)
    {
        findDocs = {
            "../../../test/testFiles/TestSimpleTestTop5/file0.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file1.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file2.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file3.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file4.txt",
            "../../../test/testFiles/TestSimpleTestTop5/file5.txt"
        };
    }
    const vector<string> docs = findDocs;
    const vector<string> request = {"the"};
    int responsesLimit = 5;
    const std::vector<vector<RelativeIndex>> expected = {
        {
            {0, 0.081},
            {1, 0.074},
            {2, 0.07},
            {4, 0.065},
            {3, 0.057}
        }
    };
    InvertedIndex idx;
    idx.setUpdateDocumentBase(docs);
    idx.getUpdateDocumentBase();
    SearchServer srv(idx);
    srv.setSearch(request,responsesLimit);
    std::vector<vector<RelativeIndex>> result = srv.getSearch();
    ASSERT_EQ(result, expected);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
