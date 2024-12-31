const char* LOGOVERSION =    R"(
///------------------------------|
/// Webp2Jpeg-2024, версия:0.4.3 |
///------------------------------|
///----------------------------------------------------------------------------|
/// Конвертер *.webp ---> *.jpg
///----------------------------------------------------------------------------:
)";

#include "webp2jpeg.h"

Config _cfg;
Log    log1;
Log    log_must;

///----------------------------------------------------------------------------|
/// Тесты.
///----------------------------------------------------------------------------:
bool tests()
{   return false;

    std::cout << "START tests() ...\n";

    FilesCargo  ::test();
    myDecodeWebp::test();
    Encode2Jpeg ::test();

    std::cout << "FINISHED tests() ...\n";
    return true;
}

void nanotest()
{
/// ...
}

///----------------------------------------------------------------------------|
/// main.
///----------------------------------------------------------------------------:
int main(int argc, char* argv[])
{
    nanotest();

    myls::output(LOGOVERSION);

    _cfg.init_filename(argv[0]);

    if(argc == 1)
    {   Config::createbat(_cfg);
    }
    else
    {   void start_ConsoleArg(Config& cfg, int argc, char* argv[]);
             start_ConsoleArg(       _cfg,     argc,       argv);
    }

    if(tests()) return 0;

    return run();
}

#include <map>
#include <functional>

using foo_t = std::function<void(std::string)>;
using S     = const std::string&;

static const std::array<foo_t, 6> F
{
    [](S s){_cfg.depth      = std::stoi(s) % 256          ;},
    [](S s){_cfg.is_log     = s == "false" ? false : true ;},
    [](S s){_cfg.remove     = s == "false" ? false : true ;},
    [](S s){_cfg.quality    = std::stoi(s) % 100          ;},
    [](S s){_cfg.downsample = s == "true"  ? true  : false;},
    [](S s){_cfg.basename   = s                           ;}
};

static const std::map<std::string, foo_t> dic
{
    {"-depth_recursive", F[0]},
    {"-is_log"         , F[1]},
    {"-remove_webm"    , F[2]},
    {"-quality"        , F[3]},
    {"-better_smaller" , F[4]},
    {"-basename"       , F[5]}
};

struct  ConsoleArg
{       ConsoleArg(Config& cfg, int argc, char* argv[])
        {
            if(dic.size()+1 < (unsigned)argc-1)
            {   std::cerr << "ERROR:ConsoleArg!\n";
            }
            else load2cfg(argc, argv);

            if(ishelp)
            {
                info_helpstr(std::cout, cfg);
            }
        }

private:
    bool ishelp{false};

    void load2cfg(int argc, char* argv[])
    {
        for (int i = 1; i < argc; ++i)
        {
            try
            {   if(std::string(argv[i]) == "-h")
                {
                /// std::cout << HELP_STR;
                    ishelp = true;
                }
                else step_one(argv[i]);

            }
            catch(std::string err)
            {   std::cerr << "\n>>>" << err  << "!!!\n\n";;
            }
            catch(...)
            {   std::cerr << "\n>>> Argunent ERROR : " << argv[i] <<" !!!\n\n";
            }
        }
    }

    static void step_one(std::string s)
    {   auto p  = s.find(":");
        std::string s1 = s.substr(0, p++);
        std::string s2 = s.substr(p, s.size() - p);

        l(s1)
        l(s2)
        l(s2.size())

        if(auto i = dic.find(s1); i != dic.end())
        {
            try
            {   i->second(std::string(trim(s2)));
            }
            catch(...)
            {   throw std::string("Argument value is ERROR: ") + s2;
            }
        }
        else throw std::string("Argument name is ERROR: ") + s1;
    }

    static std::string bool2str(bool b)
    {   std::string s(b ? "true" : "false");
        s.resize(_cfg.get_etalon_length(), ' ');
        return s;
    }

    static std::string int2str(int n)
    {   std::string s = std::to_string(n);
        s.resize(_cfg.get_etalon_length(), ' ');
        return s;
    }

    static void info_helpstr(std::ostream& o, Config& cfg)
    {
        o << std::format( HELP_STR  ,
             int2str(cfg.depth     ),
            bool2str(cfg.is_log    ),
            bool2str(cfg.remove    ),
             int2str(cfg.quality   ),
            bool2str(cfg.downsample),
            cfg.basename            ,
            std::string(cfg.basename.size(), ' ')
        );
    }

    static std::string_view trim(std::string_view s)
    {   return myls::trim_suffix(s);
    }
};

void     start_ConsoleArg(Config& cfg, int argc, char* argv[])
{   ConsoleArg ConsoleArg(        cfg,     argc,       argv);
}


