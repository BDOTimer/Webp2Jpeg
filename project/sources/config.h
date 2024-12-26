#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#ifdef  MYDEBUG
    #define  l(a) std::cout << #a << " = " << a << '\n';
    #define lp(a) std::cout << #a << " = " << a << '\n'; std::cin.get();
#else
    #define  l(a)
    #define lp(a)
#endif // MYDEBUG

extern const char* LOGOVERSION;

///----------------------------------------------------------------------------|
/// Дефолтные флаги для строки аргументов(в случаее пустой строки):
///     -depth_recursive:0
///     -is_log:true
///     -remove_webm:true
///     -quality:90
///     -better_smaller:false
///     -basename:img
///----------------------------------------------------------------------------:
struct  Config
{       Config()
        {   std::system("chcp 65001");
        }
        Config          (const Config&) = delete;
        Config operator=(const Config&) = delete;

    std::string EXE_NAME     = "webp2jpg-rc5";
    const char* LOGOVERSION  = ::LOGOVERSION;

    const std::string source = ".webp";
    const std::string dest   = ".jpg" ;

    int  depth  =     1; /// Глубина вложенности для подпапок.
    bool is_log =  true; /// Вести лог.
    bool remove =  true; /// Удалять *.webp после конвертации.

    ///--------------------------------|
    /// 0 = worst, 100 = best,         |
    /// 80 to 90 are most often used   |
    ///--------------------------------:
    unsigned char    quality  =      90;

    ///--------------------------------|
    /// false = YCbCr444(better quality)
    /// true  = YCbCr420(smaller   file)
    ///--------------------------------:
    bool          downsample  =   false;

    std::string   basename    = "img"  ;

    void init_filename(std::string_view dir)
    {
        auto   p = dir.rfind("\\") + 1;
        EXE_NAME = dir.substr(p, dir.size() - p);

        l(EXE_NAME)
    }
};

extern Config _cfg;

#endif // CONFIG_H
