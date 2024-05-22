@echo off
echo "1.missing_course"
echo "2.cs50"
echo "3.assembly wang_shuang"
echo "4.python tutorial"
set /p choice="Please select a number: "

if "%choice%"=="1" (
    call "C:\Users\26554\Desktop\select_bat\missing_course.bat"
) else if "%choice%"=="2" (
    call "C:\Users\26554\Desktop\select_bat\cs50.bat"
) else if "%choice%"=="3" (
    call "C:\Users\26554\Desktop\select_bat\assembly_wangshuang.bat"
) else if "%choice%"=="4" (
    call "C:\Users\26554\Desktop\select_bat\python_tutorial.bat"
) else (
    echo "invalid number!!!"
    pause
    exit
)
