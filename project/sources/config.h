#ifndef CONFIG_H
#define CONFIG_H
///----------------------------------------------------------------------------|
/// Конфигурато. Виден глобально из всех точек программы.
///----------------------------------------------------------------------------:

#include <string>
#include <format>

#ifdef  MYDEBUG
    #define  l(a)  std::cout << #a << " = " << a << '\n';
    #define lp(a)  std::cout << #a << " = " << a << '\n'; std::cin.get();
    #define SIGNAL std::cout << "SIGNAL\n";
#else
    #define  l(a)
    #define lp(a)
    #define SIGNAL
#endif // MYDEBUG

#define TEST friend bool tests(); static err_t test

extern const char* const LOGOVERSION;

constexpr const char* HELP_STR = R"(
///------------------------------------------------------------------------Help:
/// Текущие флаги в настройке конвертера:
///   -depth_recursive: {} - глубина рекурсии для поиска входных файлов.
///   -is_log:          {} - включить логирование.
///   -remove_webm:     {} - удалять отсканированные входные файлы.
///   -quality:         {} - качество jpeg.
///   -better_smaller:  {} - лучше(false) или меньше(true).
///   -basename:        {} - корень имени для выходных файлов.
///   -h                {} - справка.
///----------------------------------------------------------------------------.
)";

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

    std::string EXE_NAME     = "webp2jpg-rc2";
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

    static std::string get_filename_dest(const Config& cfg, unsigned n)
    {   return std::format(
            "{}_{}{}", cfg.basename, std::to_string(n), cfg.dest
        );
    }

    void init_filename(std::string_view dir)
    {
        const auto p = dir.rfind("\\") + 1;
        EXE_NAME     = dir.substr(p, dir.size() - p);
    }

    unsigned get_etalon_length() const
    {   return basename.size() < 5 ? 5 : basename.size();
    }

    static void createbat(const Config& cfg)
    {
        if(!std::ifstream("run_W2J(with_config).bat").is_open())
        {   std::ofstream("run_W2J(with_config).bat")
             << "::---------------------------------------------------------|\n"
             << ":: Дефолтная конфигурация, т.е. конфиг по умолчанию.       |\n"
             << "::---------------------------------------------------------:\n"
             << cfg.EXE_NAME << ' '
             << "-depth_recursive:0 "
             << "-is_log:true "
             << "-remove_webm:true "
             << "-quality:90 "
             << "-better_smaller:false "
             << "-basename:img -h\n\npause" << std::endl;
        }
    }
};

extern Config _cfg;

#endif // CONFIG_H
