@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0radix.exe"

if not exist %PROGRAM% (
    echo ERROR: radix.exe not found. Compile the project first.
    exit /b 1
)

echo Decimal to binary 255 - 11111111
for /f %%A in ('%PROGRAM% 10 2 255') do set "RESULT=%%A"
set "EXPECTED=11111111"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 1 PASSED: Decimal to binary
) else (
    echo Test 1 FAILED: Decimal to binary
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Binary to decimal 11111111 - 255
for /f %%A in ('%PROGRAM% 2 10 11111111') do set "RESULT=%%A"
set "EXPECTED=255"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 2 PASSED: Binary to decimal
) else (
    echo Test 2 FAILED: Binary to decimal
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Decimal to hex 255 - FF
for /f %%A in ('%PROGRAM% 10 16 255') do set "RESULT=%%A"
set "EXPECTED=FF"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 3 PASSED: Decimal to hex
) else (
    echo Test 3 FAILED: Decimal to hex
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Hex to decimal FF - 255
for /f %%A in ('%PROGRAM% 16 10 FF') do set "RESULT=%%A"
set "EXPECTED=255"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 4 PASSED: Hex to decimal
) else (
    echo Test 4 FAILED: Hex to decimal
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Lowercase hex input ff - 255
for /f %%A in ('%PROGRAM% 16 10 ff') do set "RESULT=%%A"
set "EXPECTED=255"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 5 PASSED: Lowercase hex input
) else (
    echo Test 5 FAILED: Lowercase hex input
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Zero
for /f %%A in ('%PROGRAM% 10 2 0') do set "RESULT=%%A"
set "EXPECTED=0"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 6 PASSED: Zero
) else (
    echo Test 6 FAILED: Zero
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Negative number -255 decimal to hex
for /f %%A in ('%PROGRAM% 10 16 -255') do set "RESULT=%%A"
set "EXPECTED=-FF"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 7 PASSED: Negative number
) else (
    echo Test 7 FAILED: Negative number
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Octal to decimal 77 - 63
for /f %%A in ('%PROGRAM% 8 10 77') do set "RESULT=%%A"
set "EXPECTED=63"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 8 PASSED: Octal to decimal
) else (
    echo Test 8 FAILED: Octal to decimal
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Base 36 Z - 35
for /f %%A in ('%PROGRAM% 36 10 Z') do set "RESULT=%%A"
set "EXPECTED=35"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 9 PASSED: Base 36
) else (
    echo Test 9 FAILED: Base 36
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Max int (2147483647 decimal to hex)
for /f %%A in ('%PROGRAM% 10 16 2147483647') do set "RESULT=%%A"
set "EXPECTED=7FFFFFFF"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 10 PASSED: Max int
) else (
    echo Test 10 FAILED: Max int
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Min int
for /f %%A in ('%PROGRAM% 10 16 -2147483648') do set "RESULT=%%A"
set "EXPECTED=-80000000"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 11 PASSED: Min int
) else (
    echo Test 11 FAILED: Min int
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
echo =============================

echo Invalid source radix (1)
%PROGRAM% 1 10 5
if !ERRORLEVEL! NEQ 0 (
    echo Test 12 PASSED: Invalid source radix
) else (
    echo Test 12 FAILED: Invalid source radix should return error
)
echo =============================

echo Invalid destination radix (37)
%PROGRAM% 10 37 5
if !ERRORLEVEL! NEQ 0 (
    echo Test 13 PASSED: Invalid destination radix
) else (
    echo Test 13 FAILED: Invalid destination radix should return error
)
echo =============================

echo Invalid value for source notation (G in base 16)
%PROGRAM% 16 10 G
if !ERRORLEVEL! NEQ 0 (
    echo Test 14 PASSED: Invalid value for source notation
) else (
    echo Test 14 FAILED: Invalid value should return error
)
echo =============================

echo Wrong argument count
%PROGRAM% 10 16 >nul 2>&1
if !ERRORLEVEL! NEQ 0 (
    echo Test 15 PASSED: Wrong argument count
) else (
    echo Test 15 FAILED: Wrong argument count should return error
)
echo =============================

echo Same base conversion 16 - 16
for /f %%A in ('%PROGRAM% 16 16 1A') do set "RESULT=%%A"
set "EXPECTED=1A"
if "!RESULT!"=="!EXPECTED!" (
    echo Test 16 PASSED: Same base conversion
) else (
    echo Test 16 FAILED: Same base conversion
    echo    Expected:   !EXPECTED!
    echo    Got:        !RESULT!
)
