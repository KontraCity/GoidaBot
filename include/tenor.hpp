#pragma once

// STL modules
#include <string>
#include <vector>

// Library nlohmann::json
#include <nlohmann/json.hpp>

// Custom modules
#include "curl.hpp"

namespace gb {

/* Namespace aliases and imports */
using nlohmann::json;

namespace Tenor
{
    std::vector<std::string> Search(const std::string& query);
}

} // namespace gb
