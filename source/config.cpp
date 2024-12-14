#include "config.hpp"
using namespace gb::ConfigConst;

namespace gb {

void Config::GenerateSampleFile()
{
    std::ofstream configFile(ConfigFile);
    if (!configFile)
        throw std::runtime_error("gb::Config::GenerateSampleFile(): Couldn't create sample configuration file");

    json idsObject;
    idsObject[Objects::Admins] = std::vector<int64_t>();
    idsObject[Objects::Targets] = std::vector<int64_t>();

    json configJson;
    configJson[Objects::TelegramBotApiToken] = "Enter Telegram bot API token here";
    configJson[Objects::Ids] = idsObject;
    configJson[Objects::GifQuery] = "test";
    configJson[Objects::BotEnabled] = true;
    configFile << configJson.dump(4) << '\n';
}

Config::Config()
{
    std::ifstream configFile(ConfigFile);
    if (!configFile)
        throw std::runtime_error("gb::Config::Config(): Couldn't open configuration file");

    try
    {
        const json configJson = json::parse(configFile);
        m_telegramBotApiToken = configJson.at(Objects::TelegramBotApiToken);
        m_adminIds = configJson.at(Objects::Ids).at(Objects::Admins).get<std::vector<int64_t>>();
        m_targetIds = configJson.at(Objects::Ids).at(Objects::Targets).get<std::vector<int64_t>>();
        m_gifQuery = configJson.at(Objects::GifQuery);
        m_botEnabled = configJson.at(Objects::BotEnabled);
    }
    catch (const json::exception&)
    {
        throw std::runtime_error("gb::Config::Config(): Couldn't parse configuration file JSON");
    }
}

void Config::save()
{
    std::ofstream configFile(ConfigFile, std::ios::trunc);
    if (!configFile)
        throw std::runtime_error("gb::Config::save(): Couldn't open configuration file");

    json idsObject;
    idsObject[Objects::Admins] = m_adminIds;
    idsObject[Objects::Targets] = m_targetIds;

    json configJson;
    configJson[Objects::TelegramBotApiToken] = m_telegramBotApiToken;
    configJson[Objects::Ids] = idsObject;
    configJson[Objects::GifQuery] = m_gifQuery;
    configJson[Objects::BotEnabled] = m_botEnabled;
    configFile << configJson.dump(4) << '\n';
}

} // namespace gb
