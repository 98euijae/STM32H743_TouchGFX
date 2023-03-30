/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <fonts/ApplicationFontProvider.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

touchgfx::Font* ApplicationFontProvider::getFont(touchgfx::FontId typography)
{
    switch (typography)
    {
    case Typography::DEFAULT:
        // verdana_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[0]);
    case Typography::LARGE:
        // verdana_40_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[1]);
    case Typography::SMALL:
        // verdana_10_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[2]);
    case Typography::CONSOLAS_20:
        // consola_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[3]);
    case Typography::CONSOLAS_15:
        // consola_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[4]);
    case Typography::CONSOLASBOLD_15:
        // consolab_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[5]);
    case Typography::SCOREDREAM_15:
        // SCDream6_otf_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[6]);
    default:
        return 0;
    }
}
