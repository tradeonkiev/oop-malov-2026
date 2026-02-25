@echo off
setlocal enabledelayedexpansion

set PASS=0
set FAIL=0

echo ===== Running fill tests =====
echo.

call :run_test "Test 1: Example 1" tests\input1.txt tests\output1.txt tests\expected1.txt
call :run_test "Test 2: Example 2" tests\input2.txt tests\output2.txt tests\expected2.txt
call :run_test "Test 3: Two separate contours" tests\input3.txt tests\output3.txt tests\expected3.txt
call :run_test "Test 4: Spillage through gap" tests\input4_spillage.txt tests\output4.txt tests\expected4_spillage.txt
call :run_test "Test 5: O outside contour" tests\input5_outside.txt tests\output5.txt tests\expected5_outside.txt

call :check_exit_code "Test 6: -h flag returns exit code 0" 0 -h
call :check_exit_code "Test 7: Wrong args returns exit code 1" 1 arg1
call :check_exit_code "Test 8: Non-existent file returns exit code 1" 1 nonexistent.tx

call :run_stdinstdout_test

echo.
echo ===== Results: !PASS! passed, !FAIL! failed =====

if !FAIL! gtr 0 exit /b 1
exit /b 0

:run_test
set "name=%~1"
fill.exe %2 %3
fc %3 %4 > nul
if !errorlevel!==0 (
    echo [PASS] %name%
    set /a PASS+=1
) else (
    echo [FAIL] %name%
    set /a FAIL+=1
)
exit /b

:check_exit_code
set "name=%~1"
set "expected_code=%~2"
fill.exe %3 %4 > nul
if !errorlevel!==%expected_code% (
    echo [PASS] %name%
    set /a PASS+=1
) else (
    echo [FAIL] %name%
    set /a FAIL+=1
)
exit /b

:run_stdinstdout_test
fill.exe < tests\input2.txt > tests\output_stdin.txt
fc tests\output_stdin.txt tests\expected2.txt > nul 
if !errorlevel!==0 (
    echo [PASS] Test 9: stdin/stdout mode
    set /a PASS+=1
) else (
    echo [FAIL] Test 9: stdin/stdout mode
    set /a FAIL+=1
)
exit /b