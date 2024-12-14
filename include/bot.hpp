#pragma once

// STL modules
#include <thread>

// Library tgbot-cpp
#include <tgbot/tgbot.h>

// Custom modules
#include "config.hpp"
#include "tenor.hpp"
#include "utility.hpp"

namespace gb {

class Bot final : private TgBot::Bot
{
private:
    spdlog::logger m_logger;
    Config::Pointer m_config;

private:
    /// @brief Handle /start command
    /// @param message The command to handle
    void onStartCommand(const TgBot::Message::Ptr message);

    /// @brief Handle /enable command
    /// @param message The command to handle
    void onEnableCommand(const TgBot::Message::Ptr message);

    /// @brief Handle /disable command
    /// @param message The command to handle
    void onDisableCommand(const TgBot::Message::Ptr message);

    /// @brief Handle any message
    /// @param message The message to handle
    void onAnyMessage(const TgBot::Message::Ptr message);

public:
    /// @brief Initialize bot
    /// @param config Parsed config
    Bot(const Config::Pointer& config);

    /// @brief Start bot
    void start();
};

} // namespace gb
