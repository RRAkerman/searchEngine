cmake_minimum_required (VERSION 3.5)

add_executable (searchEngine main.cpp ../include/convertJson.h convertJson.cpp  ../include/invertedindex.h invertedindex.cpp ../include/mainFile.h mainFile.cpp ../include/searchServer.h searchServer.cpp)
target_link_libraries(searchEngine PRIVATE nlohmann_json::nlohmann_json)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
include(GNUInstallDirs)
install(TARGETS searchEngine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
