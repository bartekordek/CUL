set CONFIG_TYPE=%1

echo CONFIG TYPE: %CONFIG_TYPE%

cmake -S . -B Build-Windows -DCMAKE_BUILD_TYPE=%CONFIG_TYPE%