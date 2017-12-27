#include <string.hpp>

namespace mdl
{

    // Faster reimplementations of string functionality may eventually move into my own string wrapper or something.
    size_t find_first(std::string_view str, char chr, size_t start)
    {
        for (size_t i = start; i < str.size(); ++i)
        {
            if (str[i] == chr)
            {
                return i;
            }
        }
        return std::string::npos;
    }

    size_t find_last(std::string_view str, char chr, size_t start)
    {
        if (start == std::string::npos)
        {
            start = str.size()-1;
        }
        for (size_t i = start; i >= 0; --i)
        {
            if (str[i] == chr)
            {
                return i;
            }
        }
        return std::string::npos;
    }

    size_t find_first_not_in(std::string_view str, std::string_view collection, size_t start)
    {
        for (size_t i = start; i < str.size(); ++i)
        {
            auto &chr = str[i];
            bool match = false;
            for (auto &item : collection)
            {
                if (chr == item)
                {
                    match = true;
                }
            }
            if (match != true)
            {
                return i;
            }
        }
        return std::string::npos;
    }

    size_t find_last_not_in(std::string_view str, std::string_view collection, size_t start)
    {
        if (start == std::string::npos)
        {
            start = str.size()-1;
        }
        for (size_t i = start; i >= 0; --i)
        {
            auto &chr = str[i];
            bool match = false;
            for (auto &item : collection)
            {
                if (chr == item)
                {
                    match = true;
                }
            }
            if (match != true)
            {
                return i;
            }
        }
        return std::string::npos;
    }

    int count(const std::string& str, const std::string& substr)
    {
        std::size_t start = 0;
        int count = 0;
        while (true)
        {
            start = str.find(substr, start);
            if (start != std::string::npos)
            {
                count++;
                start += substr.size();
            }
            else
            {
                break;
            }
        }

        return count;
    }

    std::string join(const std::vector<std::string>& strElements, const std::string& delimiter)
    {
        int strSize = 0;
        for (const auto &str : strElements)
        {
            strSize += str.size();
        }
        std::string output;
        output.reserve(strSize);
        const std::string &vec_back = strElements.back();
        // int vecSize = strElements.size();
        for (const auto &str : strElements)
        {
            output.append(str);
            if (str != vec_back)
            {
                output.append(delimiter);
            }
        }
        return output;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> split;

        size_t start = 0;
        size_t end = 0;
        bool running = true;

        while (running)
        {
            end = str.find(delimiter, start);
            if (end == std::string::npos)
            {
                end = str.size();
                running = false;
            }
            split.push_back(str.substr(start, end-start));
            start = end + delimiter.size();
        }

        return split;
    }

    std::vector<std::string_view> split(std::string_view str, char delimiter)
    {
        std::vector<std::string_view> split;

        size_t start = 0;
        size_t end = 0;
        bool running = true;

        while (running)
        {
            end = find_first(str, delimiter, start);
            if (end == std::string::npos)
            {
                end = str.size();
                running = false;
            }
            split.push_back(str.substr(start, end-start));
            start = end + 1;
        }

        return split;
    }

    std::string_view strip(std::string_view str)
    {
        size_t first = find_first_not_in(str, " \t");
        size_t last = find_last_not_in(str, " \t");

        // Check for blank lines.
        if (first == std::string::npos && last == std::string::npos)
        {
            return "";
        }
        else
        {
            return str.substr(first, last-first+1);
        }
    }

} // namespace mdl