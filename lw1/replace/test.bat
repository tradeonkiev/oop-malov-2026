@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0replace.exe"
set TEMPDIR=%~dp0test_temp
set PASSED=0
set FAILED=0

if not exist %PROGRAM% (
    echo ERROR: replace.exe not found. Compile the project first.
    exit /b 1
)

mkdir "%TEMPDIR%"

call :RunTest 1         "Basic replacement" "mama papa mama" "mama" "dada" "dada papa dada"
call :RunTest 2         "Search string not found" "hello world" "xyz" "abc" "hello world"
call :RunTest 3         "Replace with empty string" "abcXXXdef" "XXX" "" "abcdef"
call :RunTest 4         "Empty search string" "hello" "" "abc" "hello"
call :RunTest 5         "Multiple occurrences" "aaa bbb aaa bbb aaa" "aaa" "ccc" "ccc bbb ccc bbb ccc"
call :RunTest 6         "Replace short with long" "a+b" "+" "PLUS" "aPLUSb"
call :RunTest 7         "Partial match at boundary" "1231234" "1234" "XY" "123XY"
call :RunTest 8         "Replacement at start of line" "ABCdef" "ABC" "XYZ" "XYZdef"
call :RunTest 9         "Replacement at end of line" "defABC" "ABC" "XYZ" "defXYZ"
call :RunTest 10        "Entire string is search string" "ABC" "ABC" "XYZ" "XYZ"
call :RunErrorTest 11   "Non-existent input file" "%TEMPDIR%\nonexistent.txt" "%TEMPDIR%\out.txt" "a" "b"
call :RunErrorTest 12   "Wrong argument count" "one" "two"
call :RunMultilineTest
call :RunTest 14        "Consecutive non-overlapping matches" "aaaa" "aa" "b" "bb"
call :RunTest 15        "Replacement contains search string" "ab" "a" "aa" "aab"
call :RunEmptyFileTest

echo.
echo Results: !PASSED! passed, !FAILED! failed

rmdir /s /q "%TEMPDIR%"
exit /b 0

:RunTest
:: %1=number %2=description %3=input %4=search %5=replace %6=expected
set "NUM=%~1"
set "DESC=%~2"
set "INPUT=%~3"
set "SEARCH=%~4"
set "REPLACE=%~5"
set "EXPECTED=%~6"
echo %INPUT%> "%TEMPDIR%\in.txt"
%PROGRAM% "%TEMPDIR%\in.txt" "%TEMPDIR%\out.txt" "%SEARCH%" "%REPLACE%"
set /p RESULT=<"%TEMPDIR%\out.txt"
if "!RESULT!"=="!EXPECTED!" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
    set /a FAILED+=1
)
echo =============================
exit /b

:RunErrorTest
set "NUM=%~1"
set "DESC=%~2"
shift
shift
%PROGRAM% %1 %2 %3 %4
if !ERRORLEVEL! NEQ 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    set /a FAILED+=1
)
echo =============================
exit /b

:RunMultilineTest
(
    echo first cat line
    echo second cat here
    echo third cat end
) > "%TEMPDIR%\in.txt"
%PROGRAM% "%TEMPDIR%\in.txt" "%TEMPDIR%\out.txt" "cat" "dog"
(
    echo first dog line
    echo second dog here
    echo third dog end
) > "%TEMPDIR%\expected.txt"
fc "%TEMPDIR%\out.txt" "%TEMPDIR%\expected.txt" >nul
if !ERRORLEVEL! EQU 0 (
    echo Test 13 PASSED: Multi-line file replacement
    set /a PASSED+=1
) else (
    echo Test 13 FAILED: Multi-line file replacement
    set /a FAILED+=1
)
echo =============================
exit /b

:RunEmptyFileTest
type nul > "%TEMPDIR%\in.txt"
%PROGRAM% "%TEMPDIR%\in.txt" "%TEMPDIR%\out.txt" "abc" "xyz"
for %%A in ("%TEMPDIR%\out.txt") do set FSIZE=%%~zA
if "!FSIZE!"=="0" (
    echo Test 16 PASSED: Empty file
    set /a PASSED+=1
) else (
    echo Test 16 FAILED: Empty file should produce empty output
    set /a FAILED+=1
)
echo =============================
exit /b
