rem *** Create links ***

set start_dir=%CD%
cd install
call create_links.bat
cd %start_dir%

rem *** Clone and build Urho3D ***

cd install\Urho3D
call assembly.bat build all
cd %start_dir%

rem *** Build third party ***

cd install\ThirdParty
call make_build_all.bat
cd %start_dir%

rem *** Build Tankist ***
