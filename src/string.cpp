#include <string.hpp>
#include <iostream>

namespace mdl
{

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
                // tbh this doesn't really change anything, it just shifts the problem from the first letter to the last :/
                // But in some cases this seems to help for some reason? Weird...
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

    size_t find_last(std::string_view str, std::string_view chr, size_t start)
    {
        size_t subSize = chr.size();
        size_t fulSize = str.size();

        if (start == std::string::npos)
        {
            start = fulSize-subSize;
        }

        auto str_d = str.data();
        auto chr_d = chr.data();

        subSize--;

        for (ssize_t i = start; i >= 0; --i)
        {
            for (size_t t = 0; t <= subSize; t++)
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

    size_t find_first_not_in(std::string_view str, std::string_view collection, size_t start)
    {

        auto str_d = str.data();
        auto col_d = collection.data();

        auto colSize = collection.size();
        bool match;

        for (size_t i = start; i < str.size(); ++i)
        {
            match = false;
            for (auto c = 0; c < colSize; ++c)
            {
                if (str_d[i] == col_d[c])
                {
                    match = true;
                    break;
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

    std::vector<std::string_view> split(std::string_view str, std::string_view delimiter)
    {
        std::vector<std::string_view> split;

        size_t start = 0;
        size_t end = 0;
        bool running = true;

        auto delSize = delimiter.size();

        while (running)
        {
            end = find_first(str, delimiter, start);
            if (end == std::string::npos)
            {
                end = str.size();
                running = false;
            }
            split.push_back(str.substr(start, end-start));
            start = end + delSize;
        }

        return split;
    }

    std::vector<std::string_view> split2(std::string_view str, std::string_view delimiter)
    {
        std::vector<std::string_view> split;

        size_t start = 0;
        size_t end = 0;
        bool running = true;

        auto delSize = delimiter.size();

        while (running)
        {
            end = find_first_earlyexit(str, delimiter, start);
            if (end == std::string::npos)
            {
                end = str.size();
                running = false;
            }
            split.push_back(str.substr(start, end-start));
            start = end + delSize;
        }

        return split;
    }

    std::vector<std::string_view> split3(std::string_view str, std::string_view delimiter)
    {
        std::vector<std::string_view> split;

        size_t start = 0;
        size_t end = 0;
        bool running = true;

        auto delSize = delimiter.size();

        while (running)
        {
            end = str.find(delimiter, start);
            if (end == std::string::npos)
            {
                end = str.size();
                running = false;
            }
            split.push_back(str.substr(start, end-start));
            start = end + delSize;
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