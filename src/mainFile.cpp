#include "../include/mainFile.h"
MainFiles::MainFiles() {}

void MainFiles::getEngineConfig()
{
    return EngineConfig();
}
void MainFiles::getUpdateFiles()
{
    return updateFiles();
}
void MainFiles::EngineConfig()
{

    auto findConfigPath = []()
    {
        const std::string windowsPath = "..\\..\\..\\..\\json\\config.json";
        const std::string linuxPath = "../../../json/config.json";
        const std::string voidPath = "";
        if (std::filesystem::is_regular_file(windowsPath))
            return windowsPath;
        else
            if(std::filesystem::is_regular_file(linuxPath))
                return linuxPath;
        return voidPath;
    };
    const std::string config = findConfigPath();
    try
    {
        std::ifstream openConfig(config, std::ios_base::in);
        if(openConfig.is_open())
        {
            if(openConfig.peek() != EOF)
            {
                json readConfig = json::parse(openConfig);
                auto openConfigOptions = readConfig.find("config");
                if(openConfigOptions != readConfig.end())
                {
                    json readConfigOptions = *openConfigOptions;
                    auto configName = readConfigOptions.find("name");
                    std::string engineName = *configName;
                    auto configVersion = readConfigOptions.find("version");
                    std::string engineVersion = *configVersion;
                    auto configMaxResponses = readConfigOptions.find("max_responses");
                    std::size_t engineMaxResponses = *configMaxResponses;
                    std::cout << "Name: " << engineName << std::endl;
                    std::cout << "Version: " << engineVersion << std::endl;
                    std::cout << "Maximum number of responses: " << engineMaxResponses << std::endl;
                    auto searchFiles = readConfig.find("files");

                    if(searchFiles != readConfig.end())
                    {
                        json pathsFiles = *searchFiles;
                        std::vector<std::string>pathArray;
                        for(const auto &i : pathsFiles)
                            pathArray.push_back(i);
                        std::vector<std::string> pathArrayNow;
                        auto findResourcesPath = []()
                        {
                            const std::string windowsPath = "..\\..\\..\\..\\resources";
                            const std::string linuxPath = "../../../resources";
                            const std::string voidPath = "";
                            if (std::filesystem::is_directory(windowsPath))
                            {
                                return windowsPath;
                            }
                            else
                            {
                                if (std::filesystem::is_directory(linuxPath))
                                    return linuxPath;
                            }
                            return voidPath;
                        };
                        const std::string resourcesPath = findResourcesPath();
                        if(!resourcesPath.empty())
                        {
                            for (const auto& entry : std::filesystem::directory_iterator(resourcesPath))
                            {
                                pathArrayNow.push_back(entry.path().string());
                            }
                            if(pathArrayNow.empty())
                                throw ResoursesDirectoryMissing();
                            if(pathArrayNow.size() != pathArray.size())
                                throw UpdatePathsFiles();
                            else
                            {
                                std::size_t j = 0;
                                for(const auto &i : pathArrayNow)
                                {
                                    if(i != pathArray[j])
                                    {
                                        throw UpdatePathsFiles();
                                        break;
                                    }
                                    ++j;
                                }
                            }
                        }
                        else
                            throw UpdatePathsFiles();
                    }
                    else
                        throw FilesMissing();
                }
                else
                    throw ConfigEmpty();
            }
            else
                throw ConfigEmpty();
        }
        else
        {
            throw ConfigMissing();
        }
        openConfig.close();
        openConfig.clear();

    }
    catch(const ConfigEmpty &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(const ConfigMissing &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(const FilesMissing &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(const UpdatePathsFiles &x)
    {
        std::cerr << x.what() << std::endl;
    }
    catch(const ResoursesDirectoryMissing &x)
    {
        std::cerr << x.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
void MainFiles::updateFiles()
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
    try
    {
        std::ifstream configFile(config,std::ios_base::in);
        if(configFile.is_open())
        {
            if(configFile.peek() != EOF)
            {
                json parseConfig = json::parse(configFile);
                auto findMainData = parseConfig.find("config");
                if(findMainData != parseConfig.end())
                {
                    json mainData;
                    mainData.push_back(json::object_t::value_type("config", *findMainData));
                    configFile.close();
                    configFile.clear();
                    auto findResourcesPath = []()
                    {
                        const std::string windowsPath = "..\\..\\..\\..\\resources";
                        const std::string linuxPath = "../../../resources";
                        const std::string voidPath{};
                        if (std::filesystem::is_directory(windowsPath))
                        {
                            return windowsPath;
                        }
                        else
                        {
                            if (std::filesystem::is_directory(linuxPath))
                                return linuxPath;
                        }
                        return voidPath;
                    };
                    const std::string path = findResourcesPath();
                    std::vector<std::string> pathArray;
                    if(!path.empty())
                    {
                        for (const auto& entry : std::filesystem::directory_iterator(path))
                            pathArray.push_back(entry.path().string());
                        json addPath = json::array();
                        for(const auto &i : pathArray)
                        {
                            addPath.push_back(i);
                        }
                        mainData.push_back(json::object_t::value_type("files", pathArray));
                        std::ofstream openConfigFile(config,std::ios_base::out);
                        openConfigFile << mainData;
                        openConfigFile.close();
                        openConfigFile.clear();
                        std::cout << "complied" << std::endl;
                    }
                    else
                    {
                        std::cerr << "\"resources\" directory missing" << std::endl;
                    }
                }
            }
            else
                throw ConfigEmpty();
        }
        else
            throw ConfigMissing();

        configFile.close();
        configFile.clear();
    }
    catch(const ConfigMissing &x)
    {
        std::cerr << x.what() << std::endl;
    }
    catch(const ConfigEmpty &x)
    {
        std::cerr << x.what() << std::endl;
    }
}
