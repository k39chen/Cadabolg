::--------------------------------
:: Retrieves Cadabolg executables
:: Author: Kevin Chen
::         Copyright (c) 2011 K4SM
::--------------------------------
@echo off

echo CADABOLG DEPLOYMENT

:prompt
set /p bit="x86 or x64? "
if not %bit%==x86 (
if not %bit%==x64 (
  echo Invalid architecture.
  echo.
  goto prompt
)
)

echo.
echo Copying executable:
xcopy /s /y C:\K4SM\trunk\projects\Cadabolg\devel\project\Debug\* .\bin
echo.
echo Copying resources:
xcopy /s /y C:\K4SM\trunk\projects\Cadabolg\devel\project\resources\* .\resources
echo.
echo Removing extraneous files:
::dir /b .\bin | grep .ilk
del .\bin\*.ilk
::dir /b .\bin | grep .pdb
del .\bin\*.pdb

if %bit%==x86 (
  if exist .\bin\Cadabolg-x86.exe (
    del .\bin\Cadabolg-x86.exe
  )
  rename .\bin\Cadabolg.exe Cadabolg-x86.exe
) else (
  if exist .\bin\Cadabolg-x64.exe (
    del .\bin\Cadabolg-x64.exe
  )
  rename .\bin\Cadabolg.exe Cadabolg-x64.exe
)
echo.
echo Transfer completed!

pause