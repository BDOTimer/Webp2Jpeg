#ifndef DEC_WEBP_H
#define DEC_WEBP_H

#ifdef HAVE_CONFIG_H
//#include "webp/config.h"
#endif

#include "imageio/image_enc.h"
#include "imageio/webpdec.h"
#include "files-cargo.h"

using buf_t = std::vector<uint8_t>;

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

        log1 << std::format(
                "  file in            : {}: [{}]\n", path.string(), data_size)
             << std::format(
                "  path.parent_path() : {}\n", path.parent_path().string())
             << std::format(
                "  image size         : {} x {}\n", *W, *H);

        Bitmap::datain = (uchar*)dataout;

        return success == 0 ? YES : NO;
    }

private:
    TEST()
    {   std::cout << "STARTTEST myDecodeWebp::test() ...\n";

        ///------------------|
        /// Поставщик файлов.|
        ///------------------:
        FilesCargo filesCargo;
                 l(filesCargo.debug())

        if(filesCargo.empty()) return YES;

        myDecodeWebp mydec;
        err_t status = mydec.go(filesCargo[0]);

        l(filesCargo[0].string())
        std::cout << mydec.info() << '\n';

        return status;
    }

    uint8_t* dataout = nullptr;
};

#endif // DEC_WEBP_H

