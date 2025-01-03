#ifndef CONSOLE_ARGS_H
#define CONSOLE_ARGS_H
///----------------------------------------------------------------------------|
/// Загрузка данных конфига из коммандной строки в конфиг.
///----------------------------------------------------------------------------:

#include "myl.h"

#include <map>
#include <functional>

struct  ConsoleArg
{       ConsoleArg(Config& c, int argc, char* argv[]) : cfg(c)
        {
            if(dic.size()+1 < (unsigned)argc-1)
            {   std::cout << "ERROR:ConsoleArg!\n"
                          << "Будет загружена дефолтная настройка...\n";
            }
            else load2cfg(argc, argv);

            if(ishelp) std::cout << info_help();
        }

private:

    Config& cfg;

    using foo_t = std::function<void(std::string)>;
    using S     = const std::string&;

    const std::array<foo_t, 6> F
    {
        [&](S s){cfg.depth      = std::stoi(s) % 256          ;},
        [&](S s){cfg.is_log     = s == "false" ? false : true ;},
        [&](S s){cfg.remove     = s == "false" ? false : true ;},
        [&](S s){cfg.quality    = std::stoi(s) % 100          ;},
        [&](S s){cfg.downsample = s == "true"  ? true  : false;},
        [&](S s){cfg.basename   = s                           ;}
    };

    const std::map<std::string_view, foo_t> dic
    {
        {"-depth_recursive", F[0]},
        {"-is_log"         , F[1]},
        {"-remove_webm"    , F[2]},
        {"-quality"        , F[3]},
        {"-better_smaller" , F[4]},
        {"-basename"       , F[5]}
    };

    bool ishelp{false};

    void load2cfg(int argc, char* argv[])
    {
        for (int i = 1; i < argc; ++i)
        {
            try
            {   if(std::string_view(argv[i]) == "-h") ishelp  =    true;
                else                                  step_one(argv[i]);
            }
            catch(std::string err)
            {   std::cout << "\n>>>" << err  << "!!!\n\n";
            }
            catch(...)
            {   std::cout << "\n>>> Argunent ERROR : " << argv[i] <<" !!!\n\n";
            }
        }
    }

    void step_one(std::string_view s)
    {             size_t p  = s.find  (":");
        std::string_view s1 = s.substr(0, p++);
        std::string_view s2 = s.substr(p, s.size() - p);

        l(s1)
        l(s2)
        l(s2.size())

        if(auto i = dic.find(s1); i != dic.end())
        {
            try
            {   i->second(std::string(s2));
            }
            catch(...)
            {   throw std::string("Argument value is ERROR: ") + s2.data();
            }
        }
        else throw std::string("Argument name is ERROR: ") + s1.data();
    }

    std::string bool2str(bool b) const
    {   std::string s(b ? "true" : "false");
        s.resize(cfg.get_etalon_length(), ' ');
        return s;
    }

    std::string _int2str(int n) const
    {   std::string s = std::to_string(n);
        s.resize(cfg.get_etalon_length(), ' ');
        return s;
    }

    std::string info_help() const
    {
        std::stringstream o;

        const auto ETALON = cfg.get_etalon_length();

        auto a = std::string(cfg.basename);
             a.resize       (ETALON,  ' ');

        o << std::format( HELP_STR  ,
            _int2str(cfg.depth     ),
            bool2str(cfg.is_log    ),
            bool2str(cfg.remove    ),
            _int2str(cfg.quality   ),
            bool2str(cfg.downsample),
            a,
            std::string(ETALON, ' ')
        );
        return o.str();
    }

    inline std::string_view trim(std::string_view s)
    {   return myls::trim_suffix(s);
    }

public:
    static
    void  _2_Config(Config& cfg, int argc, char* argv[])
    {   ConsoleArg object(  cfg,     argc,       argv);
    }
};

#endif // CONSOLE_ARGS_H

