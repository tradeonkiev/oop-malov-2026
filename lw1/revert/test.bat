@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0revert.exe"
set PASSED=0
set FAILED=0

if not exist %PROGRAM% (
    echo ERROR: revert.exe not found. Compile the project first.
    exit /b 1
)

rem Create temp directory for test files
set "TMPDIR=%~dp0tmp_test"
if not exist "%TMPDIR%" mkdir "%TMPDIR%"

rem ===== Test 1: Basic integer matrix (example 1) =====
set "NUM=1"
set "DESC=Basic integer matrix inversion"
(
    echo 1	2	3
    echo 0	1	4
    echo 5	6	0
) > "%TMPDIR%\input.txt"
(
    echo -24.000	18.000	5.000
    echo 20.000	-15.000	-4.000
    echo -5.000	4.000	1.000
) > "%TMPDIR%\expected.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
fc /w "%TMPDIR%\expected.txt" "%TMPDIR%\output.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:
    type "%TMPDIR%\expected.txt"
    echo    Got:
    type "%TMPDIR%\output.txt"
    set /a FAILED+=1
)
echo =============================

rem ===== Test 2: Float matrix (example 2) =====
set "NUM=2"
set "DESC=Float matrix inversion"
(
    echo 4	7	2.3
    echo 2	1	1
    echo 3	-2	-2.31
) > "%TMPDIR%\input.txt"
(
    echo -0.009	0.321	0.131
    echo 0.212	-0.448	0.017
    echo -0.194	0.806	-0.278
) > "%TMPDIR%\expected.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
fc /w "%TMPDIR%\expected.txt" "%TMPDIR%\output.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:
    type "%TMPDIR%\expected.txt"
    echo    Got:
    type "%TMPDIR%\output.txt"
    set /a FAILED+=1
)
echo =============================

rem ===== Test 3: Non-invertible matrix (det=0) =====
set "NUM=3"
set "DESC=Non-invertible matrix - determinant is zero"
(
    echo 1	2	3
    echo 2	4	6
    echo 1	2	3
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Non-invertible" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Non-invertible
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem ===== Test 4: Identity matrix =====
set "NUM=4"
set "DESC=Identity matrix inversion"
(
    echo 1	0	0
    echo 0	1	0
    echo 0	0	1
) > "%TMPDIR%\input.txt"
(
    echo 1.000	0.000	0.000
    echo 0.000	1.000	0.000
    echo 0.000	0.000	1.000
) > "%TMPDIR%\expected.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
fc /w "%TMPDIR%\expected.txt" "%TMPDIR%\output.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:
    type "%TMPDIR%\expected.txt"
    echo    Got:
    type "%TMPDIR%\output.txt"
    set /a FAILED+=1
)
echo =============================

rem ===== Test 5: Invalid matrix format (2x3 instead of 3x3) =====
set "NUM=5"
set "DESC=Invalid matrix format - only 2 rows"
(
    echo 1	2	3
    echo 4	5	6
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Invalid matrix format" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Invalid matrix format
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem ===== Test 6: Invalid matrix format (4 columns) =====
set "NUM=6"
set "DESC=Invalid matrix format - 4 columns"
(
    echo 1	2	3	4
    echo 5	6	7	8
    echo 9	10	11	12
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Invalid matrix format" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Invalid matrix format
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem ===== Test 7: Invalid matrix (non-numeric value) =====
set "NUM=7"
set "DESC=Invalid matrix - non-numeric value"
(
    echo 1	2	abc
    echo 4	5	6
    echo 7	8	9
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Invalid matrix" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Invalid matrix
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem ===== Test 8: Reading from stdin =====
set "NUM=8"
set "DESC=Reading matrix from stdin"
(
    echo 1	2	3
    echo 0	1	4
    echo 5	6	0
) > "%TMPDIR%\input.txt"
(
    echo -24.000	18.000	5.000
    echo 20.000	-15.000	-4.000
    echo -5.000	4.000	1.000
) > "%TMPDIR%\expected.txt"
%PROGRAM% < "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
fc /w "%TMPDIR%\expected.txt" "%TMPDIR%\output.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:
    type "%TMPDIR%\expected.txt"
    echo    Got:
    type "%TMPDIR%\output.txt"
    set /a FAILED+=1
)
echo =============================

rem ===== Test 9: Help flag -h =====
set "NUM=9"
set "DESC=Help flag -h prints usage"
%PROGRAM% -h > "%TMPDIR%\output.txt"
findstr /i "usage" "%TMPDIR%\output.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC% - expected usage info
    set /a FAILED+=1
)
echo =============================

rem ===== Test 10: Extra rows in matrix =====
set "NUM=10"
set "DESC=Invalid matrix format - extra rows"
(
    echo 1	2	3
    echo 4	5	6
    echo 7	8	9
    echo 10	11	12
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Invalid matrix format" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Invalid matrix format
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem ===== Test 11: Non-invertible zero matrix =====
set "NUM=11"
set "DESC=Non-invertible zero matrix"
(
    echo 0	0	0
    echo 0	0	0
    echo 0	0	0
) > "%TMPDIR%\input.txt"
%PROGRAM% "%TMPDIR%\input.txt" > "%TMPDIR%\output.txt"
set "RESULT="
for /f "delims=" %%A in ('type "%TMPDIR%\output.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Non-invertible" (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected: Non-invertible
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================

rem Cleanup
rd /s /q "%TMPDIR%" >nul 2>&1

echo.
echo Results: !PASSED! passed, !FAILED! failed
exit /b !FAILED!
