@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0replace.exe"

if not exist %PROGRAM% (
    echo ERROR: replace.exe not found. Compile the project first.
    exit /b 1
)

mkdir "%~dp0test_temp"

echo Basic replacement
echo mama papa mama> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "mama" "dada"
fc /b "%~dp0test_temp\out.txt" nul 
set "EXPECTED=dada papa dada"
set /p RESULT=<"%~dp0test_temp\out.txt"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 1 PASSED: Basic replacement
) else (
    echo Test 1 FAILED: Basic replacement
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Search substring not found
echo hello world> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "xyz" "abc"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=hello world"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 2 PASSED: Search string not found
) else (
    echo Test 2 FAILED: Search string not found
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Replace with empty string (deletion)
echo abcXXXdef> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "XXX" ""
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=abcdef"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 3 PASSED: Replace with empty string
) else (
    echo Test 3 FAILED: Replace with empty string
    echo    Expected:   !EXPECTED!
    echo    Got:    !RESULT!
)

echo Empty search string (no changes)
echo hello> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "" "abc"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=hello"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 4 PASSED: Empty search string
) else (
    echo Test 4 FAILED: Empty search string
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================


echo Multiple occurrences
echo aaa bbb aaa bbb aaa> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "aaa" "ccc"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=ccc bbb ccc bbb ccc"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 5 PASSED: Multiple occurrences
) else (
    echo Test 5 FAILED: Multiple occurrences
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Replace short with long
echo a+b> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "+" "PLUS"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=aPLUSb"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 6 PASSED: Replace short with long
) else (
    echo Test 6 FAILED: Replace short with long
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)

echo =============================

echo 1231234 - partial match at boundary
echo 1231234> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "1234" "XY"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=123XY"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 7 PASSED: Partial match at boundary (1231234)
) else (
    echo Test 7 FAILED: Partial match at boundary (1231234)
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================


echo Search string at the start
echo ABCdef> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "ABC" "XYZ"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=XYZdef"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 8 PASSED: Replacement at start of line
) else (
    echo Test 8 FAILED: Replacement at start of line
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Test 9: Search string at the very end
echo defABC> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "ABC" "XYZ"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=defXYZ"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 9 PASSED: Replacement at end of line
) else (
    echo Test 9 FAILED: Replacement at end of line
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Entire string is the search string
echo ABC> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "ABC" "XYZ"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=XYZ"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 10 PASSED: Entire string is search string
) else (
    echo Test 10 FAILED: Entire string is search string
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Non-existent input file
%PROGRAM% "%~dp0test_temp\nonexistent.txt" "%~dp0test_temp\out.txt" "a" "b"
if !ERRORLEVEL! NEQ 0 (
    echo Test 11 PASSED: Non-existent input file returns error
) else (
    echo Test 11 FAILED: Non-existent input file should return error
)
echo =============================

echo Wrong argument count
%PROGRAM% "one" "two"
if !ERRORLEVEL! NEQ 0 (
    echo Test 12 PASSED: Wrong argument count returns error
) else (
    echo Test 12 FAILED: Wrong argument count should return error
)
echo =============================

echo Multiline file
(
    echo first cat line
    echo second cat here
    echo third cat end
) > "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "cat" "dog"
(
    echo first dog line
    echo second dog here
    echo third dog end
) > "%~dp0test_temp\expected.txt"
fc "%~dp0test_temp\out.txt" "%~dp0test_temp\expected.txt"
if !ERRORLEVEL! EQU 0 (
    echo Test 13 PASSED: Multi-line file replacement
) else (
    echo Test 13 FAILED: Multi-line file replacement
)
echo =============================

echo Consecutive search strings
echo aaaa> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "aa" "b"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=bb"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 14 PASSED: Consecutive non-overlapping matches
) else (
    echo Test 14 FAILED: Consecutive non-overlapping matches
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Replace with string containing search string
echo ab> "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "a" "aa"
set /p RESULT=<"%~dp0test_temp\out.txt"
set "EXPECTED=aab"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 15 PASSED: Replacement contains search string
) else (
    echo Test 15 FAILED: Replacement contains search string
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Empty file
type nul > "%~dp0test_temp\in.txt"
%PROGRAM% "%~dp0test_temp\in.txt" "%~dp0test_temp\out.txt" "abc" "xyz"
for %%A in ("%~dp0test_temp\out.txt") do set FSIZE=%%~zA
if "!FSIZE!"=="0" (
    echo Test 16 PASSED: Empty file
) else (
    echo Test 16 FAILED: Empty file should produce empty output
)

rmdir /s /q "%~dp0test_temp" 2>nul
