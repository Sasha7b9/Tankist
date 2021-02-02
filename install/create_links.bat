cd ..

mkdir "out/release"

mkdir "out/debug/log"
mkdir "out/release/log"

mklink /j "out/release/conf"                    "out/debug/conf"

cd install
