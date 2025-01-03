#ifndef WEB2JPEG_H
#define WEB2JPEG_H

///----------------------------------------------------------------------------|
/// Конвертер *.webp ---> *.jpg
///----------------------------------------------------------------------------:
#include "dec-Webp.h"
#include "enc-Jpeg.h"

struct  Webp2Jpeg
{       Webp2Jpeg(){}

    err_t go()
    {
        err_t err = NO;

        ///------------------|
        /// Поставщик файлов.|
        ///------------------:
        FilesCargo     fcargo;
        if( fcargo.empty())
        {   log << "Нет файлов *.webp!\n"; return 0;
        }

        log << "Найдено всего webp-файлов: " << fcargo.size() << '\n';
        log <<  fcargo.debug();

        ///-------------------------------|
        /// Файл для записи данных.       |
        ///-------------------------------:
        _2File _2file;

        ///-------------------------------|
        /// myDecodeWebp битмапы.         |
        ///-------------------------------:
        myDecodeWebp decodeWebp;

        unsigned cnt = 0;

        for(const auto& path : fcargo)
        {
            log1 << "----------------------------------------------log1:\n";
            log  << "  " << path.string() << '\n';

            if(err = decodeWebp.go(path); err)
            {
                log1 << "  ERROR: decodeWebp\n";
                myls::output(log1);
                continue;
            }

            const std::string filename_dest = fcargo.get_filename_dest(++cnt);

            fs::path dir_dest{
                path.parent_path().string()
                + "/"
                + filename_dest
            };

            _2file.openfile(dir_dest.string());

            ///---------------------------|
            /// Кодировщик в файл.        |
            ///---------------------------:
            Encode2Jpeg encode2Jpeg   (_2file);
            err       = encode2Jpeg.go(decodeWebp);

            if(err)
            {   log1 << "  status             : ERROR ...\n";
            }
            else
            {
                _2file.close();

                log1 << "  file out           : "
                     << dir_dest.string()
                     << ": [" << fs::file_size(dir_dest) << "]\n"
                     << "  status             : SUCSSES!";

                if (_cfg.remove) FilesCargo::remove(path);
            }

            ///---------------------------|
            /// Показать инфу об итерации.|
            ///---------------------------:
            myls::output(log1);
        }
        return err;
    }

    static int test_work()
    {
        Webp2Jpeg   webp2Jpeg;
        err_t err = webp2Jpeg.go();
                  l(webp2Jpeg.log.str())

        return err;
    }

    std::stringstream log{};

private:
    TEST();
};

///----------------------------------------------------------------------------|
/// Тест.
///----------------------------------------------------------------------------:
err_t Webp2Jpeg::test()
{
    err_t err = NO;

    ///------------------|
    /// Поставщик файлов.|
    ///------------------:
    FilesCargo fcargo;
            if(fcargo.empty()) return 0;

    ///-------------------------------|
    /// Файл для записи данных.       |
    ///-------------------------------:
    _2File _2file;
           _2file.openfile(fcargo.get_filename_dest(0));

    ///-------------------------------|
    /// myDecodeWebp битмапы.         |
    ///-------------------------------:
    myDecodeWebp decodeWebp;
    err       |= decodeWebp.go(fcargo[0]);

    ///-------------------------------|
    /// Кодировщик в файл.            |
    ///-------------------------------:
    Encode2Jpeg encode2Jpeg   (_2file);
    err      |= encode2Jpeg.go(decodeWebp);

    return err;
}

///----------------------------------------------------------------------------|
/// run.
///----------------------------------------------------------------------------:
inline err_t run()
{
    std::cout << "СТАРТ КОНВЕРТЕРА *.webp ---> *.jpg ..." << std::endl;

    int ver = WebPGetDecoderVersion();

    std::cout << "WebPGetDecoderVersion - "
              << ((ver >> 16)       ) << '.'
              << ((ver >>  8) & 0xFF) << '.'
              <<  (ver        & 0xFF) << std::endl;

    err_t err = Webp2Jpeg::test_work();

    std::cout << log_must;

    if(!err) std::cout << "ПРОГРАММА УСПЕШНО ЗАВЕРШИЛА РАБОТУ!\n\n";
    else     std::cout << "ПРОГРАММА ЗАВЕРШИЛА РАБОТУ С ОШИБКОЙ!\n\n";

#ifdef    MYDEBUG
    std::cin.get();
#endif // MYDEBUG

    return err;
}
#endif // WEB2JPEG_H

