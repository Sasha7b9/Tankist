rem Всё должно собираться static runtime

rem *** Create links ***

rem set start_dir=%CD%
rem cd install
rem call create_links.bat
rem cd %start_dir%

rem *** Clone and build Urho3D ***

rem cd install\Urho3D
rem call assembly.bat full all
rem cd %start_dir%

rem *** Build third party ***

rem cd install\ThirdParty
rem call make_build_all.bat
rem cd %start_dir%

rem *** Build Tankist ***
cd Windows
call make.bat build all
cd %start_dir%
