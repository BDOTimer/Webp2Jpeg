const char* const LOGOVERSION = R"(
///-------------------------------|
/// Webp2Jpeg-2024, версия:0.4.6  |
///-------------------------------|
///----------------------------------------------------------------------------|
/// Конвертер *.webp ---> *.jpg
///----------------------------------------------------------------------------:
)";

#include "console-args.h"
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
    {   ConsoleArg::_2_Config( _cfg, argc, argv);
    }

    if(tests()) return 0;

    return run();
}



