# Webp2Jpeg
 Лёгкий конвертер из `** *.webp ---> *.jpg**`
---
 
### Почему?
 webp формат появился в 2010 году, но:
 - нельзя ***.webp** сделать обоями рабочего стола.
 - нельзя повесить через теги на свой коммент на том форуме, который я юзаю.
---
 
### Зачем?
 **paint.net** может же это делать! но,
 - но небыстро.
 - нужно проклацать 100500 батонов чтобы сконверить одну картинку, а если их много?
 - поэтому цель данного нано-конвертора это **ОДИН клик + ВЕСЬ пакет** картинок из данной директории.
---
 
### Как это работает?
 - кидаем **exe** в целевую папку, в которою будут приходить **webp**-изображения.
 - в момент, когда нам понадобиться ***.jpg** нужно всего лишь кликнуть по файлику программы.
 - всё.
---
 
### Как это работает(подробности)?
 - можно сконфигурировать некоторые настройки
 - и далее запускать прогу через **батник**.
 - **батник** появляется автоматически, если он отсутствовал ранее при первом клике ***.exe**
 - список настроек можно увидеть при запуске проги.
---
 
### Инстременты и материалы разработки то что юзал я?
 - проект без всяких симейков - тупо топорно проект **Code::Blocks**
 - компилятор **gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5**
 - две сишные библиотеки [декодер](https://github.com/webmproject/libwebp/) и [кодер](https://github.com/stbrumme/toojpeg).
 - рукописные на них враперы на **C++20**
 - пожалуй всё.
---
 
### Как это скомпилировать?
 - понадобиться **Code::Blocks**
 - сам проект отсюда.
 - открыть в **C::B** [воркспейс Tools.workspace](project/).
 - нажать ребилд.
 - готово.
---
 
### Баги?
 - возможно конечные юзеры увидят баги в самом удобстве/дизайне использования ...
 - откровенных фатальных багов лично я не обнаружил...
---
 
### TODO?
 - НЕТ ПРЕДЕЛУ СОВЕРШЕНСТВА!
 - есть варианты развития - разные форматы, но сначала вопрос "ПОЧЕМУ?"
---
 
### ...
---
 
 