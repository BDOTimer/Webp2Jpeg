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
            }

            {   const auto& ext = ifile->path().extension().string();

                if(ext == _cfg.source)
                {   push_back(ifile->path());
                }
                else
                if(ext == _cfg.dest)
                {   dest.push_back(ifile->path());
                }
            }
        }

        l(dest.size())

        this->log     ();
        this->log_must();
    }

    unsigned get_percent(unsigned i)
    {   return (100 * i) / size();
    }

    std::string debug()
    {   std::string s(std::string("size: ") + std::to_string(size()) + '\n');

        s += "|------------------Webp:\n";

        for(const fs::path& path : *this)
        {
            s += path.string();
            s += "\n";
        }

        s += "|------------------Jpeg:\n";

        for(const fs::path& path : dest)
        {
            s += path.string();
            s += "\n";
        }

        s += "get_filename_dest() = ";
        s +=  get_filename_dest();
        s += "\n";

        return s ;
    }

    static void test()
    {
        FilesCargo   filesCargo;
        std::cout << filesCargo.debug() << '\n';
    }

    std::string        get_filename_dest()
    {   return Config::get_filename_dest(_cfg, dest.size()+1);
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
    std::vector<fs::path> dest{};
};

#endif // FILE_COLLECTED_H

