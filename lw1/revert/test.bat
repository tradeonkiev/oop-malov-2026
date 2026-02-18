@echo off
setlocal enabledelayedexpansion

set PROGRAM="%~dp0revert.exe"
set TEMPDIR=%~dp0test_temp
set PASSED=0
set FAILED=0

if not exist %PROGRAM% (
    echo ERROR: revert.exe not found. Compile the project first.
    exit /b 1
)

mkdir "%TEMPDIR%"

call :RunTest 1 "Basic integer matrix (example 1)" "1	2   3" "0	1	4" "5	6	0" "-24.000	18.000	5.000" "20.000	-15.000	-4.000" "-5.000	4.000	1.000"
call :RunTest 2 "Float matrix (example 2)" "4	7	2.3" "2	1	1" "3	-2	-2.31" "-0.009	0.321	0.131" "0.212	-0.448	0.017" "-0.194	0.806	-0.278"
call :RunTest 3 "Identity matrix" "1	0	0" "0	1	0" "0	0	1" "1.000	0.000	0.000" "0.000	1.000	0.000" "0.000	0.000	1.000"
call :RunMessageTest 4 "Non-invertible matrix (example 3)" "1	2	3" "2	4	6" "1	2	3" "Non-invertible"
call :RunMessageTest 5 "Non-invertible zero matrix" "0	0	0" "0	0	0" "0	0	0" "Non-invertible"
call :RunInvalidFormatTest 6 "Only 2 rows"
call :RunInvalidFormatTest2 7 "4 columns in a row"
call :RunInvalidMatrixTest 8 "Non-numeric value"
call :RunStdinTest
call :RunHelpTest
call :RunExtraRowsTest
call :RunErrorTest 12 "Too many arguments" "%PROGRAM% file1 file2"

echo.
echo Results: !PASSED! passed, !FAILED! failed

rmdir /s /q "%TEMPDIR%"
exit /b 0

:RunTest
set "NUM=%~1"
set "DESC=%~2"
set "R1=%~3"
set "R2=%~4"
set "R3=%~5"
set "E1=%~6"
set "E2=%~7"
set "E3=%~8"
(
    echo !R1!
    echo !R2!
    echo !R3!
) > "%TEMPDIR%\in.txt"
(
    echo !E1!
    echo !E2!
    echo !E3!
) > "%TEMPDIR%\expected.txt"
%PROGRAM% "%TEMPDIR%\in.txt" > "%TEMPDIR%\out.txt"
fc /w "%TEMPDIR%\expected.txt" "%TEMPDIR%\out.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    echo    Expected:
    type "%TEMPDIR%\expected.txt"
    echo    Got:
    type "%TEMPDIR%\out.txt"
    set /a FAILED+=1
)
echo =============================
exit /b

:RunMessageTest
set "NUM=%~1"
set "DESC=%~2"
set "R1=%~3"
set "R2=%~4"
set "R3=%~5"
set "EXPECTED=%~6"
(
    echo !R1!
    echo !R2!
    echo !R3!
) > "%TEMPDIR%\in.txt"
set "RESULT="
for /f "delims=" %%A in ('%PROGRAM% "%TEMPDIR%\in.txt"') do set "RESULT=%%A"
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

:RunInvalidFormatTest
set "NUM=%~1"
set "DESC=%~2"
(
    echo 1	2	3
    echo 4	5	6
) > "%TEMPDIR%\in.txt"
set "RESULT="
for /f "delims=" %%A in ('%PROGRAM% "%TEMPDIR%\in.txt"') do set "RESULT=%%A"
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
exit /b

:RunInvalidFormatTest2
set "NUM=%~1"
set "DESC=%~2"
(
    echo 1	2	3	4
    echo 5	6	7	8
    echo 9	10	11	12
) > "%TEMPDIR%\in.txt"
set "RESULT="
for /f "delims=" %%A in ('%PROGRAM% "%TEMPDIR%\in.txt"') do set "RESULT=%%A"
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
exit /b

:RunInvalidMatrixTest
set "NUM=%~1"
set "DESC=%~2"
(
    echo 1	2	abc
    echo 4	5	6
    echo 7	8	9
) > "%TEMPDIR%\in.txt"
set "RESULT="
for /f "delims=" %%A in ('%PROGRAM% "%TEMPDIR%\in.txt"') do set "RESULT=%%A"
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
exit /b

:RunStdinTest
(
    echo 1	2	3
    echo 0	1	4
    echo 5	6	0
) > "%TEMPDIR%\in.txt"
(
    echo -24.000	18.000	5.000
    echo 20.000	-15.000	-4.000
    echo -5.000	4.000	1.000
) > "%TEMPDIR%\expected.txt"
%PROGRAM% < "%TEMPDIR%\in.txt" > "%TEMPDIR%\out.txt"
fc /w "%TEMPDIR%\expected.txt" "%TEMPDIR%\out.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test 9 PASSED: Reading matrix from stdin
    set /a PASSED+=1
) else (
    echo Test 9 FAILED: Reading matrix from stdin
    echo    Expected:
    type "%TEMPDIR%\expected.txt"
    echo    Got:
    type "%TEMPDIR%\out.txt"
    set /a FAILED+=1
)
echo =============================
exit /b

:RunHelpTest
%PROGRAM% -h > "%TEMPDIR%\out.txt"
findstr /i "usage" "%TEMPDIR%\out.txt" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo Test 10 PASSED: Help flag -h prints usage
    set /a PASSED+=1
) else (
    echo Test 10 FAILED: Help flag -h prints usage - expected usage info
    set /a FAILED+=1
)
echo =============================
exit /b

:RunExtraRowsTest
(
    echo 1	2	3
    echo 4	5	6
    echo 7	8	9
    echo 10	11	12
) > "%TEMPDIR%\in.txt"
set "RESULT="
for /f "delims=" %%A in ('%PROGRAM% "%TEMPDIR%\in.txt"') do set "RESULT=%%A"
if "!RESULT!"=="Invalid matrix format" (
    echo Test 11 PASSED: Extra rows in matrix
    set /a PASSED+=1
) else (
    echo Test 11 FAILED: Extra rows in matrix
    echo    Expected: Invalid matrix format
    echo    Got:      !RESULT!
    set /a FAILED+=1
)
echo =============================
exit /b

:RunErrorTest
set "NUM=%~1"
set "DESC=%~2"
set "CMD=%~3"
%CMD% >nul 2>&1
if !ERRORLEVEL! NEQ 0 (
    echo Test %NUM% PASSED: %DESC%
    set /a PASSED+=1
) else (
    echo Test %NUM% FAILED: %DESC%
    set /a FAILED+=1
)
echo =============================
exit /b
