#pragma once

// STL modules
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// Library Curl
#include <curl/curl.h>

// Library {fmt}
#include <fmt/format.h>

// Custom modules
#include "utility.hpp"

namespace gb {

namespace Curl
{
    // Maximum amount of request attempts
    constexpr int MaxRequestAttempts = 5;

    struct Response
    {
        long code = -1;
        std::string headers;
        std::string data;
    };

    /// @brief Perform HTTP GET request
    /// @param url Request URL
    /// @param headers Request headers
    /// @throw std::runtime_error if internal error occurs
    /// @throw std::invalid_argument if connection fails
    /// @return Request response
    Response Get(const std::string& url, const std::vector<std::string>& headers = {});

    /// @brief Perform HTTP POST request
    /// @param url Request URL
    /// @param headers Request headers
    /// @param data Request data
    /// @throw std::runtime_error if internal error occurs
    /// @throw std::invalid_argument if connection fails
    /// @return Request response
    Response Post(const std::string& url, const std::vector<std::string>& headers, const std::string& data);
}

} // namespace gb
