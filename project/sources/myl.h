#ifndef MYL_H
#define MYL_H

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>
#include <string>

#include "config.h"

namespace fs = std::filesystem;

///----------------------------------------------------------------------------|
/// WinAPI.
///----------------------------------------------------------------------------:
namespace win{

#include <windows.h>

inline std::wstring utf8_to_wide(const std::string& utf8_str)
{
    ///-----------------------------------------|
    /// Determine the length of the wide string.|
    ///-----------------------------------------:
    int len = MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), -1, nullptr, 0
    );

    if (len == 0)
    {   std::cerr << "Error in MultiByteToWideChar: "
                  << GetLastError() << std::endl;
        return L"";
    }

    ///-----------------------------------------|
    /// Convert string UTF-8 to wstring UCS-2.  |
    ///-----------------------------------------:
    std::wstring wide_str(--len, '0');
    MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), -1, &wide_str[0], len
    );

    return wide_str;
}
}

struct  Log
{       Log(){ clear(); }

    template<typename T>
    Log& operator<<(const   T& val)
    {   if(_cfg.is_log) log << val;
        return *this;
    }

    const std::string get() const
    {   return _cfg.is_log ? log.str() : "Логирование оключено ...\n";
    }

    void clear ()
    {   log.str("");
        log << '\n';
    }

private:
    std::stringstream log{};
};

inline std::ostream& operator<<(std::ostream& o, Log& _log)
{   if(!_cfg.is_log) return o;
           o << _log.get() << std::endl; _log.clear();
    return o;
}

extern Log log1;
extern Log log_must;

///----------------------------------------------------------------------------|
/// Полезные процедуры...
///----------------------------------------------------------------------------:
struct myls
{
    static std::streampos getSize(std::ifstream& file)
    {
        file.seekg(0, std::ios::end);
        std::streampos filesize = file.tellg();
        file.seekg(0, std::ios::beg);

        return filesize;
    }

    static std::vector<uint8_t> readFile(const fs::path& path)
    {
        std::wstring wfilename = win::utf8_to_wide(path.string());

        std::ifstream file(wfilename.c_str(), std::ios::binary);

        const auto fileSize = fs::file_size(path);
      //const auto fileSize = getSize(file);

        std::vector<uint8_t> vec(fileSize);

        ///----------------------------------------|
        /// Stop eating new lines in binary mode!  |
        ///----------------------------------------:
        file.unsetf(std::ios::skipws);

        vec.insert(vec.begin(),
            std::istream_iterator<uint8_t>(file),
            std::istream_iterator<uint8_t>()   );
        return vec;
    }

    static void output(Log& log)
    {   std::cout << log << '\n';
    }

    static void output(const std::string_view log)
    {   std::cout << log << '\n';
    }

    static std::string_view trim_prefix(std::string_view s)
    {   s.remove_prefix(std::distance(s.cbegin(),
                                      std::find_if(s.cbegin(), s.cend(),
            [](int c) {return !std::isspace(c);}))
        );
        return s;
    }

    static std::string_view trim_suffix(std::string_view s)
    {   s.remove_suffix(std::distance(s.crbegin(),
                                      std::find_if(s.crbegin(), s.crend(),
            [](int c) {return !std::isspace(c);}))
        );
        return s;
    }

    static std::string_view trim(std::string_view s)
    {   return trim_prefix(
               trim_suffix(s)
        );
    }
};

using ushort = unsigned short;
using uchar  = unsigned char ;

///----------------------------------------------------------------------------|
/// Данные.
///----------------------------------------------------------------------------:
struct  Bitmap
{       Bitmap(ushort  W , ushort H)
            :   width (W),
                height(H),
                image (W * H * bytesPerPixel)
        {
        }
        Bitmap() = default;
        Bitmap          (const Bitmap&) = delete;
        Bitmap operator=(const Bitmap&) = delete;

    ///-----------------------------|
    /// Image size.                 |
    ///-----------------------------:
    int width {};
    int height{};

    ///-----------------------------|
    /// RGB: one byte each for:     |
    ///      red, green, blue.      |
    ///-----------------------------:
    const ushort    bytesPerPixel{3};

    uchar* datain = nullptr;

    std::string info()
    {
        std::stringstream o;
        o << "width : " << width  << '\n';
        o << "height: " << height << '\n';
        return o.str();
    }

protected:
    ///-----------------------------|
    /// allocate memory.            |
    ///-----------------------------:
    std::vector<uchar>       image{};
};

#endif // MYL_H

