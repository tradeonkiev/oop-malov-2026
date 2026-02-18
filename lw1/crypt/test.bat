@echo off
setlocal enabledelayedexpansion

set "PROGRAM=%~dp0crypt.exe"
set "INPUT=%~dp0test_input.txt"
set "ENC=%~dp0test_enc.txt"
set "DEC=%~dp0test_dec.txt"
set "EMPTY=%~dp0test_empty.txt"
set PASSED=0
set FAILED=0

if not exist "!PROGRAM!" (
    echo ERROR: crypt.exe not found. Compile the project first.
    exit /b 1
)

echo hello wrld!!;:\ж test 1 2 3 4 5 1 2 5 3 > "!INPUT!"

call :testCryptDecrypt	"1"		"Encrypt and decrypt (key=42)"		42
call :testCryptDecrypt	"2"		"Encrypt and decrypt (key=0)"		0
call :testCryptDecrypt	"3"		"Encrypt and decrypt (key=255)"		255
call :testFilesDiffer	"4"		"Encrypted file should differ from original" 42
call :testEmptyFile		"5"		"Empty file encrypt and decrypt" 100

call :testWrongKey		"6"		"Different keys produce different result" 42 43
call :testError			"7"		"No arguments"				""									"Usage: crypt.exe"
call :testError			"8"		"Invalid mode"				"encode !INPUT! !ENC! 42"			"first arg must be"
call :testError			"9"		"Key is not a number"		"crypt !INPUT! !ENC! abc"			"key must be in range 0-255"
call :testError			"10"	"Key out of range (256)"	"crypt !INPUT! !ENC! 256"			"key must be in range 0-255"
call :testError			"11"	"Key out of range (-1)"		"crypt !INPUT! !ENC! -1"			"key must be in range 0-255"
call :testError			"12"	"Non-existent input"		"crypt %~dp0no_such_file.txt !ENC! 42"	"cant open input file"
call :testError			"13"	"Key with letters 42abc"	"crypt !INPUT! !ENC! 42abc"			"key must be in range 0-255"

del "!INPUT!" 2>nul
del "!ENC!" 2>nul
del "!DEC!" 2>nul
del "!EMPTY!" 2>nul

echo.
echo Results: !PASSED! passed, !FAILED! failed
exit /b 0

:testCryptDecrypt
set "NUM=%~1"
set "DESC=%~2"
set "KEY=%~3"
"!PROGRAM!" crypt "!INPUT!" "!ENC!" %KEY%
"!PROGRAM!" decrypt "!ENC!" "!DEC!" %KEY%
fc /b "!INPUT!" "!DEC!" > nul 2>&1
if errorlevel 1 (
    echo Test !NUM! FAILED: !DESC!
    set /a FAILED+=1
) else (
    echo Test !NUM! PASSED: !DESC!
    set /a PASSED+=1
)
echo =============================
goto :eof

:testFilesDiffer
set "NUM=%~1"
set "DESC=%~2"
set "KEY=%~3"
"!PROGRAM!" crypt "!INPUT!" "!ENC!" %KEY%
fc /b "!INPUT!" "!ENC!" > nul 2>&1
if errorlevel 1 (
    echo Test !NUM! PASSED: !DESC!
    set /a PASSED+=1
) else (
    echo Test !NUM! FAILED: !DESC! - files are the same
    set /a FAILED+=1
)
echo =============================
goto :eof

:testEmptyFile
set "NUM=%~1"
set "DESC=%~2"
set "KEY=%~3"
type nul > "!EMPTY!"
"!PROGRAM!" crypt "!EMPTY!" "!ENC!" %KEY%
"!PROGRAM!" decrypt "!ENC!" "!DEC!" %KEY%
fc /b "!EMPTY!" "!DEC!" > nul 2>&1
if errorlevel 1 (
    echo Test !NUM! FAILED: !DESC!
    set /a FAILED+=1
) else (
    echo Test !NUM! PASSED: !DESC!
    set /a PASSED+=1
)
echo =============================
goto :eof

:testWrongKey
set "NUM=%~1"
set "DESC=%~2"
set "KEY1=%~3"
set "KEY2=%~4"
"!PROGRAM!" crypt "!INPUT!" "!ENC!" %KEY1%
"!PROGRAM!" decrypt "!ENC!" "!DEC!" %KEY2%
fc /b "!INPUT!" "!DEC!" > nul 2>&1
if errorlevel 1 (
    echo Test !NUM! PASSED: !DESC!
    set /a PASSED+=1
) else (
    echo Test !NUM! FAILED: !DESC! - files match with wrong key
    set /a FAILED+=1
)
echo =============================
goto :eof

:testError
set "NUM=%~1"
set "DESC=%~2"
set "ARGS=%~3"
set "EXPECTED=%~4"
set "OUTPUT_FILE=%~dp0test_output.txt"
"!PROGRAM!" !ARGS! > "!OUTPUT_FILE!" 2>&1
if not errorlevel 1 (
    echo Test !NUM! FAILED: !DESC! - expected non-zero exit code
    set /a FAILED+=1
    del "!OUTPUT_FILE!" 2>nul
    echo =============================
    goto :eof
)
findstr /c:"!EXPECTED!" "!OUTPUT_FILE!" > nul
if errorlevel 1 (
    echo Test !NUM! FAILED: !DESC!
    echo    Expected message containing: !EXPECTED!
    echo    Got:
    type "!OUTPUT_FILE!"
    set /a FAILED+=1
) else (
    echo Test !NUM! PASSED: !DESC!
    set /a PASSED+=1
)
del "!OUTPUT_FILE!" 2>nul
echo =============================
goto :eof
