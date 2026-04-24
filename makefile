

output/solution: output solution.cpp
	gcc solution.cpp -lstdc++ -g -O0 -o output/solution

output:
	mkdir output
