#ifndef FILE_COLLECTED_H
#define FILE_COLLECTED_H
///-----------------------------------------------------------------------------
/// Файловый коллектор.
///----------------------------------------------------------------------------:
#include "myl.h"

struct  FilesCargo : std::vector<fs::path>
{       FilesCargo()
        {   scan  ();
        }

    void scan()
    {
        const auto& spd = fs::directory_options::skip_permission_denied;

        const fs::recursive_directory_iterator START("./", spd);
        const fs::recursive_directory_iterator END  {};

        for (auto ifile  = START; ifile != END; ++ifile)
        {
            if(ifile.depth() > _cfg.depth)
            {   ifile.pop( );

                if(ifile == END) break;

                continue;
            }

            const auto ext = ifile->path().extension().string();

            if(ext == _cfg.source)
            {   push_back(ifile->path());
            }
            else
            if(ext == _cfg.dest)
            {   d.push_back(ifile->path());
            }
        }

        this->log     ();
        this->log_must();
    }

    std::string debug()
    {   std::string s(std::string("size: ") + std::to_string(size()) + '\n');

        for(const fs::path& path : *this)
        {
            s += path.string();
            s += "\n";
        }
        s += "get_base_name_dest(0) = ";
        s +=  get_base_name_dest(0);
        s += "\n";
        return s ;
    }

    static void test()
    {
        FilesCargo   filesCargo;
        std::cout << filesCargo.debug() << '\n';
    }

    std::string get_base_name_dest(int n)
    {
        n += d.size();

        std::string start{_cfg.basename};

        return std::format(
            "{}{}{}{}", start, '_', std::to_string(n), _cfg.dest
        );
    }

    static void remove(const fs::path& path)
    {   fs::remove(path);
    }

    void log()
    {    log1 << "Всего найдено "                << size()
              << " файлов с расширением *.webp!" << "\n\n";
    }

    void  log_must ()
    {   ::log_must <<
            (empty () ? "Файлы *.webp для конвертации отсутствуют!\n" : "");
    }

private:
    std::vector<fs::path> d{};
};

#endif // FILE_COLLECTED_H

