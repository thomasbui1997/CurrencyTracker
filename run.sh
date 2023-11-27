g++ -c Validation.cpp -o Validation
g++ -c Main.cpp -o Main

g++ Validation Main -o Currency -lcurl
./Currency