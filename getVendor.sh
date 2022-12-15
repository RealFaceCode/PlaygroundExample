#!/bin/bash

echo "Cloning repositories..."
mkdir vendor
cd vendor || exit

git clone https://github.com/RealFaceCode/Playground.git

cd Playground || exit
./getVendor.sh