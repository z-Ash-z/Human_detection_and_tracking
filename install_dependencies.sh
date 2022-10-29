# Install OpenCV
sudo apt update && sudo apt install -y cmake g++ wget unzip # Install minimal prerequisites
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip # Download and unpack sources
unzip opencv.zip
mkdir -p build && cd build # Create build directory
cmake  ../opencv-4.x # Configure
cmake --build . # Build
sudo make install # Install

# Dowload yolo v3 weights
cd dependencies
wget https://github.com/patrick013/Object-Detection---Yolov3/blob/master/model/yolov3.weights