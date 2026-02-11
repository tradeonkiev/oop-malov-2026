echo off

set PROGRAM="%~dp0crypt.exe"

echo hello wrld!!;:\ж test 1 2 3 4 5 1 2 5 3 > "%~dp0test_input.txt"

echo TEST Encrypt and decrypt (key=42)
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 42
%PROGRAM% decrypt "%~dp0test_enc.txt" "%~dp0test_dec.txt" 42
fc /b "%~dp0test_input.txt" "%~dp0test_dec.txt"
if errorlevel 1 (echo FAIL) else (echo OK)
echo =========================================

echo TEST Encrypt and decrypt (key=0)
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 0
%PROGRAM% decrypt "%~dp0test_enc.txt" "%~dp0test_dec.txt" 0
fc /b "%~dp0test_input.txt" "%~dp0test_dec.txt"
if errorlevel 1 (echo FAIL) else (echo OK)
echo =========================================

echo TEST Encrypt and decrypt (key=255)
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 255
%PROGRAM% decrypt "%~dp0test_enc.txt" "%~dp0test_dec.txt" 255
fc /b "%~dp0test_input.txt" "%~dp0test_dec.txt"
if errorlevel 1 (echo FAIL) else (echo OK)
echo =========================================

echo TEST Encrypted file should differ from original
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 42
fc /b "%~dp0test_input.txt" "%~dp0test_enc.txt"
if errorlevel 1 (echo OK - files are different) else (echo FAIL - files are the same)
echo =========================================

echo TEST Empty file
type nul > "%~dp0test_empty.txt"
%PROGRAM% crypt "%~dp0test_empty.txt" "%~dp0test_enc.txt" 100
%PROGRAM% decrypt "%~dp0test_enc.txt" "%~dp0test_dec.txt" 100
fc /b "%~dp0test_empty.txt" "%~dp0test_dec.txt"
if errorlevel 1 (echo FAIL) else (echo OK)
echo =========================================

echo TEST Different keys
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 42
%PROGRAM% decrypt "%~dp0test_enc.txt" "%~dp0test_dec.txt" 43
fc /b "%~dp0test_input.txt" "%~dp0test_dec.txt"
if errorlevel 1 (echo OK - wrong key) else (echo FAIL)
echo =========================================

echo TEST No arguments
%PROGRAM%
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Invalid mode
%PROGRAM% encode "%~dp0test_input.txt" "%~dp0test_enc.txt" 42
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Key is not a number
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" abc
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Key out of range (256)
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 256
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Key out of range (-1)
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" -1
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Non-existent input file
%PROGRAM% crypt "%~dp0no_such_file.txt" "%~dp0test_enc.txt" 42
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

echo TEST Key with letters 42abc
%PROGRAM% crypt "%~dp0test_input.txt" "%~dp0test_enc.txt" 42abc
if errorlevel 1 (echo OK - error returned) else (echo FAIL)
echo =========================================

del "%~dp0test_input.txt" 2>nul
del "%~dp0test_enc.txt" 2>nul
del "%~dp0test_dec.txt" 2>nul
del "%~dp0test_empty.txt" 2>nul

echo TEST ARE CLOSED
pause
