@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0radix.exe"
set PASSED=0
set FAILED=0

if not exist %PROGRAM% (
    echo ERROR: radix.exe not found. Compile the project first.
    exit /b 1
)

call :testValue  "1"    "Decimal to binary 255"             10 2  255           "11111111"
call :testValue  "2"    "Binary to decimal 11111111"        2  10 11111111      "255"
call :testValue  "3"    "Decimal to hex 255"                10 16 255           "FF"
call :testValue  "4"    "Hex to decimal FF"                 16 10 FF            "255"
call :testValue  "5"    "Lowercase hex input ff"            16 10 ff            "255"
call :testValue  "6"    "Zero"                              10 2  0             "0"
call :testValue  "7"    "Negative number -255 to hex"       10 16 -255          "-FF"
call :testValue  "8"    "Octal to decimal 77"               8  10 77            "63"
call :testValue  "9"    "Base 36 Z to decimal"              36 10 Z             "35"
call :testValue  "10"   "Max int 2147483647 to hex"         10 16 2147483647    "7FFFFFFF"
call :testValue  "11"   "Min int -2147483648 to hex"        10 16 -2147483648   "-80000000"
call :testValue  "12"   "Same base conversion hex"          16 16 1A            "1A"

call :testError  "13"   "Overflow 2147483648"               10 16 2147483648    "Overflow: number is too large to convert"
call :testError  "14"   "Overflow -2147483649"              10 16 -2147483649   "Overflow: number is too large to convert"
call :testError  "15"   "Invalid char G in base 16"         16 10 G             "Digit G is out of range for base 16"
call :testError  "16"   "Invalid source radix 1"            1  10 5             "Invalid source notation: must be a number from 2 to 36"
call :testError  "17"   "Invalid destination radix 37"      10 37 5             "Invalid destination notation: must be a number from 2 to 36"

call :testErrorCode "18" "Wrong argument count" "%PROGRAM% 10 16"

echo.
echo Results: !PASSED! passed, !FAILED! failed
exit /b !FAILED!

:testValue
set "NUM=%~1"
set "DESC=%~2"
set "SRC=%~3"
set "DST=%~4"
set "INPUT=%~5"
set "EXPECTED=%~6"
for /f "delims=" %%A in ('%PROGRAM% %SRC% %DST% %INPUT%') do set "RESULT=%%A"
if "!RESULT!"=="!EXPECTED!" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: !EXPECTED!
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================
exit /b

:testError
set "NUM=%~1"
set "DESC=%~2"
set "SRC=%~3"
set "DST=%~4"
set "INPUT=%~5"
set "EXPECTED=%~6"
for /f "delims=" %%A in ('%PROGRAM% %SRC% %DST% %INPUT%') do set "RESULT=%%A"
if "!RESULT!"=="!EXPECTED!" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: !EXPECTED!
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================
exit /b

:testErrorCode
set "NUM=%~1"
set "DESC=%~2"
set "CMD=%~3"
%CMD% >nul 2>&1
if !ERRORLEVEL! NEQ 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC% - expected non-zero exit code
    set /a FAILED+=1
)
echo =============================
exit /b
