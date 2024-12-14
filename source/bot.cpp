#include "bot.hpp"

namespace gb {

void Bot::onStartCommand(const TgBot::Message::Ptr message)
{
    m_logger.info("@{}: /start: Showing start message", message->from->username);
    getApi().sendMessage(message->chat->id,
        "<b>Available commands:</b>\n"
        "/start - Show this message\n"
        "/enable - Enable Goida patrol\n"
        "/disable - Disable Goida patrol\n",
        nullptr, nullptr, nullptr, "HTML"
    );
}

void Bot::onEnableCommand(const TgBot::Message::Ptr message)
{
    if (!m_config->isAdminId(message->from->id))
    {
        m_logger.info("@{}: /enable: Not an admin", message->from->username);
        getApi().sendMessage(message->chat->id, "Not an admin");
        return;
    }

    if (m_config->isBotEnabled())
    {
        m_logger.info("@{}: /enable: Already enabled", message->from->username);
        getApi().sendMessage(message->chat->id, "Already enabled");
        return;
    }
    m_config->setBotEnabled(true);
}

void Bot::onDisableCommand(const TgBot::Message::Ptr message)
{
    if (!m_config->isAdminId(message->from->id))
    {
        m_logger.info("@{}: /disable: Not an admin", message->from->username);
        getApi().sendMessage(message->chat->id, "Not an admin");
        return;
    }

    if (!m_config->isBotEnabled())
    {
        m_logger.info("@{}: /disable: Already disabled", message->from->username);
        getApi().sendMessage(message->chat->id, "Already disabled");
        return;
    }
    m_config->setBotEnabled(false);
}

void Bot::onAnyMessage(const TgBot::Message::Ptr message)
{
    if (!m_config->isTargetId(message->from->id))
        return;

    std::thread([this, message]()
    {
        static std::vector<std::string> results;
        if (results.empty())
        {
            try
            {
                results = Tenor::Search(m_config->gifQuery());
                if (results.empty())
                {
                    m_logger.error(
                        "@{}: \"{}\": Couldn't find any GIFs",
                        message->from->username, message->text
                    );
                    return;
                }
            }
            catch (const std::runtime_error& error)
            {
                m_logger.error(
                    "@{}: \"{}\": Couldn't search for GIFs: \"{}\"",
                    message->from->username, message->text, error.what()
                );
                return;
            }
        }
        
        m_logger.info("@{}: \"{}\": Replying with random GIF", message->from->username, message->text);
        getApi().sendAnimation(message->chat->id, results[Utility::Random(0, results.size() - 1)]);
    }).detach();
}

Bot::Bot(const Config::Pointer& config)
    : TgBot::Bot(config->telegramBotApiToken())
    , m_logger(Utility::CreateLogger("bot"))
    , m_config(config)
{
    getEvents().onCommand("start", std::bind(&Bot::onStartCommand, this, std::placeholders::_1));
    getEvents().onCommand("enable", std::bind(&Bot::onEnableCommand, this, std::placeholders::_1));
    getEvents().onCommand("disable", std::bind(&Bot::onDisableCommand, this, std::placeholders::_1));
    getEvents().onAnyMessage(std::bind(&Bot::onAnyMessage, this, std::placeholders::_1));
}

void Bot::start()
{
    TgBot::TgLongPoll poll(*this);
    while (true)
    {
        static bool readyMessageShown = false;
        if (!readyMessageShown)
        {
            m_logger.info("Ready: logged in as @{}", getApi().getMe()->username);
            readyMessageShown = true;
        }
        poll.start();
    }
}

} // namespace gb
