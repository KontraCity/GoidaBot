// STL modules
#include <filesystem>

// Library {fmt}
#include <fmt/format.h>

// Custom modules
#include "bot.hpp"
#include "config.hpp"
#include "utility.hpp"
using namespace gb;

struct ParseResult
{
    enum class Result
    {
        None,       // Parsing error occured
        ShowHelp,   // Help message was requested
        Generate,   // Files generation was requested
        Start,      // Normal bot start was requested
    };

    const char* executable;
    Result result;
    bool forceColor;
};

/// @brief Parse commmandline arguments
/// @param argc Count of arguments
/// @param argv Values of arguments
/// @return Parsed options
static ParseResult ParseOptions(int argc, char** argv)
{
    ParseResult result;
    result.executable = argv[0];
    result.result = ParseResult::Result::Start;
    result.forceColor = false;

    for (int index = 1; index < argc; ++index)
    {
        std::string option = argv[index];

        if (option == "-fc" || option == "--force-color")
        {
            result.forceColor = true;
            continue;
        }

        if (result.result != ParseResult::Result::Start)
        {
            fmt::print("Ignoring option: \"{}\"\n", option);
            continue;
        }

        if (option == "-h" || option == "--help")
        {
            result.result = ParseResult::Result::ShowHelp;
            continue;
        }

        if (option == "-g" || option == "--generate")
        {
            result.result = ParseResult::Result::Generate;
            continue;
        }

        fmt::print(
            "Unknown option: \"{}\"\n"
            "See {} --help\n",
            option, result.executable
        );

        result.result = ParseResult::Result::None;
        return result;
    }

    return result;
}

/// @brief Show help message
/// @param result Commandline arguments parse result
static int ShowHelpMessage(const ParseResult& result)
{
    fmt::print(
        "GoidaBot usage: {} [OPTIONS]\n"
        "Available options:\n"
        "    (No options)\tStart bot normally\n"
        "    -fc, --force-color\tForce colored logs regardless of whether current tty supports them or not\n"
        "Unique options:\n"
        "    -h, --help\t\tShow this message and exit\n"
        "    -g, --generate\tGenerate files and exit\n"
        "Only one of the unique options may be passed at the same time. All others will be ignored.\n",
        result.executable
    );
    return 0;
}

/// @brief Generate necessary files
/// @return Executable exit code
static int GenerateFiles()
{
    if (std::filesystem::is_regular_file(ConfigConst::ConfigFile))
    {
        fmt::print(
            "Configuration file \"{}\" already exists.\n"
            "Delete it first to confirm that you don't care about its contents.\n",
            ConfigConst::ConfigFile
        );
        return 1;
    }

    try
    {
        Config::GenerateSampleFile();
    }
    catch (...)
    {
        fmt::print(
            "Couldn't create configuration file \"{}\".\n"
            "Please check permissions.\n",
            ConfigConst::ConfigFile
        );
        return 1;
    }


    fmt::print(
        "Configuration file \"{}\" was created.\n"
        "Please configure the file before starting GoidaBot.\n",
        ConfigConst::ConfigFile
    );
    return 0;
}

/// @brief Parse config
/// @param result Commandline arguments parse result
/// @return Config if parsed successfully, empty pointer otherwise
static Config::Pointer ParseConfig(const ParseResult& result)
{
    spdlog::logger logger = Utility::CreateLogger("init", result.forceColor);
    try
    {
        return std::make_shared<Config>();
    }
    catch (const std::runtime_error& error)
    {
        logger.error("Configuration error: \"{}\"", error.what());
        logger.info("Hint: Check configuration file \"{}\"", ConfigConst::ConfigFile);
        logger.info("Hint: You can generate necessary files by running {} --generate", result.executable);
        return {};
    }
}

int main(int argc, char** argv)
{
    ParseResult result = ParseOptions(argc, argv);
    switch (result.result)
    {
        case ParseResult::Result::None:
            return 1;
        case ParseResult::Result::ShowHelp:
            return ShowHelpMessage(result);
        case ParseResult::Result::Generate:
            return GenerateFiles();
        default:
            break;
    }

    Config::Pointer config = ParseConfig(result);
    if (!config)
        return 1;

    fmt::print(
        "Welcome to GoidaBot\n"
        "GitHub repository: https://github.com/KontraCity/GoidaBot\n"
    );

    Bot bot(config);
    bot.start();
}
