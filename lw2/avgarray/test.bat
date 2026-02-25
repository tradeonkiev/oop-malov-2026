@echo off
setlocal enabledelayedexpansion
chcp 65001 > nul

set PROGRAM=avgarray.exe
set PASS=0
set FAIL=0

echo ========================================
echo Running tests for %PROGRAM%
echo ========================================

call :check_output "positive and fractional" "1.0 2 3.659512" "3.220 4.220 5.879"
call :check_output "mixed positive and negative" "4 16 -30 10" "-20.000 14.000 20.000 26.000"
call :check_output "all negative" "-1.0004000 -703 -3.659512 -11" "-703.000 -11.000 -3.660 -1.000"
call :check_error "invalid input" "- 2 3"
call :check_empty "empty input"

echo.
echo ========================================
echo Results: %PASS% passed, %FAIL% failed
echo ========================================

del /q output.txt err.txt 2> nul

if %FAIL% GTR 0 exit /b 1
exit /b 0

:check_output
echo.
echo Test: %~1
echo %~2 | %PROGRAM% > output.txt 2> err.txt
set /p RESULT=<output.txt
set EXPECTED=%~3
if "!RESULT!"=="!EXPECTED!" (
    echo   PASS
    set /a PASS+=1
) else (
    echo   FAIL
    echo   Expected: !EXPECTED!
    echo   Got:      !RESULT!
    set /a FAIL+=1
)
exit /b

:check_empty
echo.
echo Test: %~1
echo. | %PROGRAM% > output.txt 2> err.txt
for %%A in (output.txt) do (
    if %%~zA==0 (
        echo   PASS
        set /a PASS+=1
    ) else (
        echo   FAIL
        echo   Expected: empty
        set /p RESULT=<output.txt
        echo   Got:      !RESULT!
        set /a FAIL+=1
    )
)
exit /b

:check_error
echo.
echo Test: %~1
echo %~2 | %PROGRAM% > output.txt 2> err.txt
if %ERRORLEVEL% NEQ 0 (
    echo   PASS returned error code
    set /a PASS+=1
) else (
    echo   FAIL expected non-zero exit code
    set /a FAIL+=1
)
exit /b
