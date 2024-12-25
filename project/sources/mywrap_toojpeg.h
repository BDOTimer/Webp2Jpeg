#ifndef MYWRAP_TOOJPEG_H
#define MYWRAP_TOOJPEG_H

#include "toojpeg.h"
#include "files_collected.h"

#include "myl.h"

///----------------------------------------------------------------------------|
/// Куда будем писать?!
///----------------------------------------------------------------------------:
struct  _2File : protected std::ofstream
{       _2File(std::string_view filename) : filename(filename)
        {
            setout  (this    );
            openfile(filename);
        }
        _2File()
        {   setout  (this    );
        }

    std::string_view filename{};

    ///--------------------------------------------|
    /// Callback function:                         |
    /// write a single byte compressed by tooJpeg  |
    ///--------------------------------------------:
    static void myOutput(uchar byte)
    {   *myFile << byte;
    }

    void openfile(std::string_view _filename)
    {   if(is_open()) close();

        std::wstring wfilename = win::utf8_to_wide(std::string(_filename));

        open(wfilename.data(), std::ios_base::out   |
                               std::ios_base::binary);
        filename = _filename;
    }

private:
    void setout(std::ofstream* file)
    {   myFile = file;
    }

    inline
    static std::ofstream* myFile = nullptr;
};


///----------------------------------------------------------------------------|
/// Алгоритм генерации данных.
///----------------------------------------------------------------------------:
struct  Generator42 : Bitmap
{       Generator42(ushort w, ushort h) : Bitmap(w, h)
        {
        }
        Generator42() = delete;

    void go()
    {
        const auto& W   = Bitmap::width        ;
        const auto& H   = Bitmap::height       ;
        const auto& BPP = Bitmap::bytesPerPixel;

        ///-----------------------------------|
        /// create a nice color transition    |
        /// (replace with your code)          |
        ///-----------------------------------:
        for     (auto y = 0; y < H; y++)
        {   for (auto x = 0; x < W; x++)
            {   // memory location of current pixel
                auto offset = (y * W + x) * BPP;
                // red and green fade from 0 to 255, blue is always 127
                image[offset    ] = 255 * x / W;
                image[offset + 1] = 255 * y / H;
                image[offset + 2] = 127;
            }
        }

        Bitmap::datain = &(Bitmap::image[0]);
    }
};

///----------------------------------------------------------------------------|
/// Кодировщик в JPEG.
///----------------------------------------------------------------------------:
struct  Encode2Jpeg
{       Encode2Jpeg(_2File& _2file) : _2file(_2file)
        {
        }

    ///---------------------------------------------------|
    /// start JPEG compression                            |
    /// note: myOutput is the function defined in line 18,|
    /// it saves the output in example.jpg                |
    /// optional parameters:                              |
    ///---------------------------------------------------:
    bool        isRGB      = true ; // true = RGB image, else false = grayscale
    unsigned char quality  = _cfg.quality;
    bool        downsample = _cfg.downsample;
    const char* comment    = "xlat-code"; // arbitrary JPEG comment

    int go(const Bitmap& bmp)
    {
        auto ok = TooJpeg::writeJpeg
        (
            _2File::myOutput,
             bmp.datain     , (ushort)(bmp.width), (ushort)(bmp.height),
             isRGB          , quality  , downsample, comment
        );
        return ok ? 0 : 1;
    }

    void openfile(std::string_view filename)
    {   _2file.openfile(filename);
    }

    static std::string info_ok(const Encode2Jpeg& enc, int ok)
    {   return std::string(enc._2file.filename) + " : "
                                                + (ok == 0 ? "good" : "failed");
    };

    static int test();

private:
    _2File& _2file;
};

///----------------------------------------------------------------------------|
/// Тест.
///----------------------------------------------------------------------------:
int Encode2Jpeg::test()
{
    ///-------------------------------|
    /// Файл для записи данных.       |
    ///-------------------------------:
    _2File _2file;
           _2file.openfile("ex05.jpg");

    ///-------------------------------|
    /// Generator42 битмапы.          |
    ///-------------------------------:
    Generator42 generator42(806, 608);
                generator42.go();

    ///-------------------------------|
    /// Кодировщик в файл.            |
    ///-------------------------------:
    Encode2Jpeg encode2Jpeg(_2file);
    int    ok = encode2Jpeg.go(generator42);

    l(Encode2Jpeg::info_ok(encode2Jpeg, ok));

    {   generator42.width  = 700;
        generator42.height = 300;

        encode2Jpeg.openfile("ex123.jpg");
        ok += encode2Jpeg.go(generator42);

        l(Encode2Jpeg::info_ok(encode2Jpeg, ok));
    }

    return ok;
}

#endif // MYWRAP_TOOJPEG_H

