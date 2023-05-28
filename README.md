# flower_game
The code is separated on two parts: 
1) namespace "core" which uses only standart of C++ without any thirdaprty dependencies.
2) namespace "view" where we have Qt dependencies.
The idea was to keep as much functionality as possible on C++ standart/STL part, and minimize Qt usage as much as possible (with idea of future porting to other SDK).
Due to this code in general might look overloaded in some places (due to non-qt and qt part communication), but due to this we may easy swap any other SDK.

The demo tested on linux, macos, windows and android.

Windows build:
https://drive.google.com/file/d/1mzXlcL5jhq3N9Fe_b744QcNR0nu8mgET/view?usp=share_link

Android apk:
https://drive.google.com/file/d/1OYXGrn_sNyNQAcbXWt9I3weCX1XTS_ik/view?usp=share_link
