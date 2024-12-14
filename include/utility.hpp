#pragma once

// STL modules
#include <string>
#include <optional>
#include <random>

// Library spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace gb {

namespace Utility
{
    /// @brief Create logger
    /// @param name Logger name
    /// @param forceColor Whether to force sinks colors or not
    /// @return Created logger
    spdlog::logger CreateLogger(const std::string& name, std::optional<bool> forceColor = {});

    /// @brief Generate random integer
    /// @param min Min integer value
    /// @param max Max integer value
    /// @return Generated integer
    int Random(int min, int max);
}

} // namespace gb
