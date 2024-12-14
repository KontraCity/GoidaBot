#pragma once

// STL modules
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// Library nlohmann::json
#include <nlohmann/json.hpp>

// Library {fmt}
#include <fmt/format.h>

namespace gb {

/* Namespace aliases and imports */
using nlohmann::json;

namespace ConfigConst
{
    // Bot configuration JSON file name
    constexpr const char* ConfigFile = "config.json";

    namespace Objects
    {
        constexpr const char* TelegramBotApiToken = "telegram_bot_api_token";
        constexpr const char* Ids = "ids";
        constexpr const char* Admins = "admins";
        constexpr const char* Targets = "targets";
        constexpr const char* GifQuery = "gif_query";
        constexpr const char* BotEnabled = "bot_enabled";
    }
}

class Config
{
public:
    using Pointer = std::shared_ptr<Config>;

public:
    /// @brief Generate sample configuration file for user to fill out
    /// @throw std::runtime_error if the file couldn't be created
    static void GenerateSampleFile();

private:
    std::string m_telegramBotApiToken;
    std::vector<int64_t> m_adminIds;
    std::vector<int64_t> m_targetIds;
    std::string m_gifQuery;
    bool m_botEnabled = true;

public:
    /// @brief Read and parse configuration file
    /// @throw std::runtime_error if the file couldn't be read/parsed
    Config();

private:
    /// @brief Save to configuration file
    /// @throw std::runtime_error if the file couldn't be read/parsed
    void save();

public:
    /// @brief Get Telegram bot API token
    /// @return Telegram bot API token
    inline const std::string& telegramBotApiToken() const
    {
        return m_telegramBotApiToken;
    }

    /// @brief Get admin IDs
    /// @return Admin IDs
    inline const std::vector<int64_t>& adminIds() const
    {
        return m_adminIds;
    }

    /// @brief Check if an ID is an admin ID
    /// @param id The ID to check
    /// @return True if the ID is an admin ID, false otherwise
    inline bool isAdminId(uint64_t id) const
    {
        return std::find(m_adminIds.begin(), m_adminIds.end(), id) != m_adminIds.end();
    }

    /// @brief Get target IDs
    /// @return Target IDs
    inline const std::vector<int64_t>& targetIds() const
    {
        return m_targetIds;
    }

    /// @brief Check if an ID is a target ID
    /// @param id The ID to check
    /// @return True if the ID is a target ID, false otherwise
    inline bool isTargetId(uint64_t id) const
    {
        return std::find(m_targetIds.begin(), m_targetIds.end(), id) != m_targetIds.end();
    }

    /// @brief Get GIF query
    /// @return GIF query
    inline const std::string& gifQuery() const
    {
        return m_gifQuery;
    }

    /// @brief Check if bot is enabled
    /// @return True if the bot is enabled, false otherwise
    inline bool isBotEnabled() const
    {
        return m_botEnabled;
    }

    /// @brief Set bot enabled state
    /// @param enabled The state to set
    inline void setBotEnabled(bool enabled)
    {
        m_botEnabled = enabled;
        save();
    }
};

} // namespace gb
