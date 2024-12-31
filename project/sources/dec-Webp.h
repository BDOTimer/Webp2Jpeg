#ifndef DEC_WEBP_H
#define DEC_WEBP_H

#ifdef HAVE_CONFIG_H
//#include "webp/config.h"
#endif

#include "imageio/image_enc.h"
#include "imageio/webpdec.h"
#include "files-cargo.h"

using buf_t = std::vector<uint8_t>;

using err_t     = bool ;
const bool ERR  = true ;
const bool GOOD = false;

///----------------------------------------------------------------------------|
/// Декодер webp.
///----------------------------------------------------------------------------:
struct  myDecodeWebp    : Bitmap
{       myDecodeWebp()  = default;
        myDecodeWebp(const myDecodeWebp&) = delete;
       ~myDecodeWebp()
        {   if(dataout != nullptr) WebPFree((void*)dataout);
        }

        const myDecodeWebp& operator=(const myDecodeWebp&) = delete;

    err_t go(const fs::path& path)
    {
        if(dataout != nullptr) WebPFree((void*)dataout);
           dataout  = nullptr;

        buf_t  buf  = myls::readFile(path);

        const uint8_t* data   = &buf[0];
        size_t      data_size =  buf.size();

        int* W = &(Bitmap::width );
        int* H = &(Bitmap::height);

        [[maybe_unused]]
        int success = WebPGetInfo  ( data, data_size, W, H );
            dataout = WebPDecodeRGB( data, data_size, W, H );

        log1 << "  path.string()      : " << path.string     () << '\n'
             << "  path.parent_path() : " << path.parent_path() << '\n'
             << "  data_size          : " << data_size          << '\n'
             << "  Width              : " << *W       << '\n'
             << "  Height             : " << *H       << '\n';

        Bitmap::datain = (uchar*)dataout;

        return success == 0 ? ERR : GOOD;
    }

private:
    friend bool tests();
    static void test ()
    {   std::cout << "STARTTEST myDecodeWebp::test() ...\n";

        ///------------------|
        /// Поставщик файлов.|
        ///------------------:
        FilesCargo filesCargo;
                 l(filesCargo.debug())

        if(filesCargo.empty()) return;

        myDecodeWebp mydec;
                     mydec.go(filesCargo[0]);

        l(filesCargo[0].string())
        std::cout << mydec.info() << '\n';
    }

    uint8_t* dataout = nullptr;
};

#endif // DEC_WEBP_H

