#ifndef WEB2JPEG_H
#define WEB2JPEG_H

///----------------------------------------------------------------------------|
/// Конвертер *.webp ---> *.jpg
///----------------------------------------------------------------------------:
#include "dec-Webp.h"
#include "mywrap_toojpeg.h"

struct  Webp2Jpeg
{       Webp2Jpeg(){}

    int go()
    {
        ///------------------|
        /// Поставщик файлов.|
        ///------------------:
        FilesCargo     fcargo;
        if( fcargo.empty())
        {   log << "Нет файлов *.webp!\n"; return 0;
        }

        log << "fcargo.size() = " << fcargo.size() << '\n';
        log <<  fcargo.debug();

        ///-------------------------------|
        /// Файл для записи данных.       |
        ///-------------------------------:
        _2File _2file;

        ///-------------------------------|
        /// myDecodeWebp битмапы.         |
        ///-------------------------------:
        myDecodeWebp decodeWebp;

        int cnt = 0;

        for(const auto& path : fcargo)
        {
            log << "  " << path.string() << '\n';

            decodeWebp.go(path);

            fs::path dir{
                path.parent_path().string()
                + "\\"
                + fcargo.get_base_name_dest(++cnt)
            };

            _2file.openfile(dir.string());

            ///---------------------------|
            /// Кодировщик в файл.        |
            ///---------------------------:
            Encode2Jpeg encode2Jpeg(_2file);
            int err = encode2Jpeg.go(decodeWebp);

            if(err == 1) return 1;

            if(_cfg.remove) FilesCargo::remove(path);
        }
        return 0;
    }

    static int test_work()
    {
        Webp2Jpeg  webp2Jpeg;
        auto err = webp2Jpeg.go();
                 l(webp2Jpeg.log.str())

        return err;
    }

    std::stringstream log{};

    static int test();
};

///----------------------------------------------------------------------------|
/// Тест.
///----------------------------------------------------------------------------:
int Webp2Jpeg::test()
{
    ///------------------|
    /// Поставщик файлов.|
    ///------------------:
    FilesCargo fcargo;
            if(fcargo.empty()) return 0;

    ///-------------------------------|
    /// Файл для записи данных.       |
    ///-------------------------------:
    _2File _2file;
           _2file.openfile(fcargo.get_base_name_dest(2024));

    ///-------------------------------|
    /// myDecodeWebp битмапы.         |
    ///-------------------------------:
    myDecodeWebp decodeWebp;
                 decodeWebp.go(fcargo[0]);

    ///-------------------------------|
    /// Кодировщик в файл.            |
    ///-------------------------------:
    Encode2Jpeg encode2Jpeg(_2file);
    int    ok = encode2Jpeg.go(decodeWebp);

    return ok;
}

///----------------------------------------------------------------------------|
/// run.
///----------------------------------------------------------------------------:
int run()
{
    std::cout << "СТАРТ КОНВЕРТЕРА *.webp ---> *.jpg ..." << std::endl;

    int ver = WebPGetDecoderVersion();

    std::cout << "WebPGetDecoderVersion - "
              << ((ver >> 16)       ) << '.'
              << ((ver >>  8) & 0xFF) << '.'
              <<  (ver        & 0xFF) << std::endl;

    int err = Webp2Jpeg::test_work();

    std::cout << log_must;

    if(0 == err) std::cout << "ПРОГРАММА УСПЕШНО ЗАВЕРШИЛА РАБОТУ!\n\n";
    else         std::cout << "ПРОГРАММА ЗАВЕРШИЛА РАБОТУ С ОШИБКОЙ!\n\n";

#ifdef    MYDEBUG
    std::cin.get();
#endif // MYDEBUG

    return err;
}
#endif // WEB2JPEG_H

