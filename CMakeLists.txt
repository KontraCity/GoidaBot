## --- Project configuration --- ##
cmake_minimum_required(VERSION 3.20)
project(GoidaBot)

## --- Compiler configuration --- ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
include_directories("include/")

## --- Packages configuration --- ##
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(CURL REQUIRED)

## --- Submodules configuration --- ##
add_subdirectory("submodules/tgbot-cpp")

## --- Executable configuration  --- ##
add_executable(GoidaBot "source/main.cpp"
    "source/bot.cpp"
    "source/config.cpp"
    "source/curl.cpp"
    "source/tenor.cpp"
    "source/utility.cpp"
)
target_link_libraries(GoidaBot PRIVATE
    # Packages
    fmt::fmt
    spdlog::spdlog
    CURL::libcurl

    # Submodules
    TgBot
)
