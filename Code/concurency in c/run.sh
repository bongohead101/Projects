g++ -std=c++11 -pthread -fpermissive assignment3.cpp
clear all
echo "STARTING INPUT 3a.TXT"
./a.out < input3a.txt 1>output1.txt
echo "STARTING INPUT 3b.TXT"
./a.out < input3b.txt 1>output2.txt
echo "STARTING INPUT 3c.TXT"
./a.out < input3c.txt 1> output3.txt
echo "DONE WITH THE EXPERIMENTS"
