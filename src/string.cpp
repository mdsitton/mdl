#include <string.hpp>

namespace mdl
{

    // Special case version of find for single 
    size_t find_first(std::string_view str, char chr, size_t start)
    {

        auto str_d = str.data();
        for (size_t i = start; i < str.size(); ++i)
        {
            if (str_d[i] == chr)
            {
                return i;
            }
        }
        return std::string::npos;
    }

    // This version of find, is essentially the same speed as the stl version.
    size_t find_first(std::string_view str, std::string_view chr, size_t start)
    {
        // Some sanity checking
        if (start >= str.size())
        {
            return std::string::npos;
        }

        if (chr.size() == 0 || str.size() == 0)
        {
            return std::string::npos;
        }

        size_t subSize = chr.size()-1;

        auto str_d = str.data();
        auto chr_d = chr.data();

        size_t t;

        for (size_t i = start; i < str.size(); ++i)
        {

            for (t=0; t <= subSize; t++)
            {
                if (str_d[i+t] != chr_d[t])
                {
                    break;
                }
                else if (t == subSize)
                {
                    return i;
                }
            }
        }
        return std::string::npos;
    }

size_t find_first_old(std::string_view str, std::string_view chr, size_t start)
{
    size_t subSize = chr.size();
    for (size_t i = start; i < str.size(); ++i)
    {
        if (str.substr(i, subSize) == chr)
        {
            return i;
        }
    }
    return std::string::npos;
}

    // This version of find, is essentially the same speed as the stl version.
    size_t find_first_earlyexit(std::string_view str, std::string_view chr, size_t start)
    {

        size_t subSize = chr.size();
        size_t fulSize = str.size();

        // Some sanity checking
        if (start >= fulSize)
        {
            return std::string::npos;
        }

        if (subSize == 0 || fulSize == 0)
        {
            return std::string::npos;
        }

        auto str_d = str.data();

        if (subSize == 1)
        {
            char chrZ = chr[0];

            for (size_t i = start; i < fulSize; ++i)
            {
                if (str_d[i] == chrZ)
                {
                    return i;
                }
            }
            return std::string::npos;
        }
        else
        {

            subSize--;
            auto chr_d = chr.data();
            size_t t;

            for (size_t i = start; i < fulSize; ++i)
            {
                // Fast exit for long strings.
                if (str_d[i+subSize] != chr_d[subSize])
                {
                    continue;
                }

                for (t=0; t < subSize; t++)
                {
                    if (str_d[i+t] != chr_d[t])
                    {
                        break;
                    }
                    else if (t == subSize-1)
                    {
                        return i+1;
                    }
                }
            }
            return std::string::npos;
        }

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

    int count(std::string_view str, std::string_view substr)
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

    std::string join(const std::vector<std::string>& strElements, std::string_view delimiter)
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