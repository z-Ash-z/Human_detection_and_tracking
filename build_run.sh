cd build
rm -rf *
cmake .. && make
cd ..
./build/app/human_detect_and_track_app
