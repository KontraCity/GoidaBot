#include "utility.hpp"

namespace gb {

spdlog::logger Utility::CreateLogger(const std::string& name, std::optional<bool> forceColor)
{
    static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> sink;
    if (!sink)
    {
        sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern("[%^%d.%m.%C %H:%M:%S %L%$] [%n] %v");
    }

    if (forceColor)
        sink->set_color_mode(*forceColor ? spdlog::color_mode::always : spdlog::color_mode::automatic);
    return { name, {sink} };
}

int Utility::Random(int min, int max)
{
    static std::mt19937 generator(std::random_device{}());
    return std::uniform_int_distribution(min, max)(generator);
}

} // namespace gb
