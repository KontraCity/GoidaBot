#include "tenor.hpp"

namespace gb {

std::vector<std::string> Tenor::Search(const std::string& query)
{
    Curl::Response response = Curl::Get(fmt::format("https://g.tenor.com/v1/search?q={}&key=LIVDSRZULELA&limit=50", query));
    if (response.code != 200)
    {
        throw std::runtime_error(fmt::format(
            "gb::Tenor::Search(): Couldn't get API response [query: \"{}\", response code: {}]",
            query, response.code
        ));
    }

    try
    {
        const json responseJson = json::parse(response.data);
        const json& results = responseJson.at("results");

        std::vector<std::string> urls;
        urls.reserve(results.size());

        for (const json& result : results)
            urls.push_back(result.at("media").at(0).at("gif").at("url"));
        return urls;
    }
    catch (const json::exception&)
    {
        throw std::runtime_error(fmt::format(
            "gb::Tenor::Search(): Couldn't parse API response [query: \"{}\"]",
            query
        ));
    }
}

} // namespace gb
