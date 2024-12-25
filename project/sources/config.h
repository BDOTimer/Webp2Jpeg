#ifndef CONFIG_H
#define CONFIG_H

#include <string>

///----------------------------------------------------------------------------|
/// ��������� ����� ��� ������ ����������(� ������� ������ ������):
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

    const char* const EXE_NAME = "webp2jpg-rc5";

    const std::string source   = ".webp";
    const std::string dest     = ".jpg" ;

    int  depth  =     1; /// ������� ����������� ��� ��������.
    bool is_log =  true; /// ����� ���.
    bool remove =  true; /// ������� *.webp ����� �����������.

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
};

extern Config _cfg;

#endif // CONFIG_H
