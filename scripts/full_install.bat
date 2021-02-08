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

cd install\ThirdParty
call make_build_all.bat
cd %start_dir%

rem *** Build Tankist ***
