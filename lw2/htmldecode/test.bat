@echo off
setlocal enabledelayedexpansion
chcp 65001 > nul

set PROGRAM=decoder.exe
set PASS=0
set FAIL=0

echo ========================================
echo Running tests for %PROGRAM%
echo ========================================

REM --- Test 1: all entities ---
set "TEST_NAME=all entities"
> input.txt echo Cat ^&lt;says^&gt; ^&quot;Meow^&quot;. M^&amp;M^&apos;s
> expected.txt echo Cat ^<says^> "Meow". M^&M's
call :run_test

REM --- Test 2: only lt ---
set "TEST_NAME=only lt"
> input.txt echo ^&lt;
> expected.txt echo ^<
call :run_test

REM --- Test 3: only gt ---
set "TEST_NAME=only gt"
> input.txt echo ^&gt;
> expected.txt echo ^>
call :run_test

REM --- Test 4: only amp ---
set "TEST_NAME=only amp"
> input.txt echo ^&amp;
> expected.txt echo ^&
call :run_test

REM --- Test 6: only apos ---
set "TEST_NAME=only apos"
> input.txt echo ^&apos;
> expected.txt echo '
call :run_test

REM --- Test 7: no entities ---
set "TEST_NAME=no entities"
> input.txt echo Hello World
> expected.txt echo Hello World
call :run_test

REM --- Test 8: unknown entity passthrough ---
set "TEST_NAME=unknown entity passthrough"
> input.txt echo ^&unknown; text
> expected.txt echo ^&unknown; text
call :run_test

REM --- Test 9: ampersand alone ---
set "TEST_NAME=ampersand alone"
> input.txt echo a ^& b
> expected.txt echo a ^& b
call :run_test

REM --- Test 10: consecutive entities ---
set "TEST_NAME=consecutive entities"
> input.txt echo ^&lt;^&gt;^&amp;
> expected.txt echo ^<^>^&
call :run_test

REM --- Test 11: entity at end ---
set "TEST_NAME=entity at end"
> input.txt echo test^&lt;
> expected.txt echo test^<
call :run_test

REM --- Test 12: entity at start ---
set "TEST_NAME=entity at start"
> input.txt echo ^&gt;test
> expected.txt echo ^>test
call :run_test

REM --- Test 13: empty string ---
set "TEST_NAME=empty string"
type nul > input.txt
type nul > expected.txt
call :run_test

REM --- Test 14: ampersand at end ---
set "TEST_NAME=ampersand at end"
> input.txt echo test^&
> expected.txt echo test^&
call :run_test

REM --- Test 15: double encoded amp ---
set "TEST_NAME=double encoded amp"
> input.txt echo ^&amp;amp;
> expected.txt echo ^&amp;
call :run_test

REM --- Test 16: multiline ---
set "TEST_NAME=multiline input"
(echo ^&lt;html^&gt;
echo ^&amp;copy;) > input.txt
(echo ^<html^>
echo ^&copy;) > expected.txt
call :run_test

echo.
echo ========================================
echo Results: !PASS! passed, !FAIL! failed
echo ========================================

del /q output.txt expected.txt input.txt 2> nul

if !FAIL! GTR 0 exit /b 1
exit /b 0

:run_test
echo.
echo Test: !TEST_NAME!
%PROGRAM% < input.txt > output.txt 2> nul
fc /b output.txt expected.txt > nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo   PASS
    set /a PASS+=1
) else (
    echo   FAIL
    echo   Expected:
    type expected.txt
    echo   Got:
    type output.txt
    set /a FAIL+=1
)
exit /b
