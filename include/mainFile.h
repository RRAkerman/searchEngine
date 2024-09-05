#ifndef MAINFILE_H
#define MAINFILE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <exception>
using json = nlohmann::json;
class ConfigEmpty:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Config file is empty";
    }
};
class ConfigMissing:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Config file is missing";
    }
};
class FilesMissing:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Missing paths to resource files";
    }
};
class ResoursesDirectoryMissing:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "The resource directory is empty or missing";
    }
};
class UpdatePathsFiles:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Update the path to resource files";
    }
};
//Data Validation Class config.json
class MainFiles
{
public:
    MainFiles();

    void getEngineConfig();
    void getUpdateFiles();
private:
    /*
     *  Method for obtaining initial data config.json
     */
    void EngineConfig();
    /*
     *  The method updates the paths in config.json
     */
    void updateFiles();
};

#endif // MAINFILE_H
