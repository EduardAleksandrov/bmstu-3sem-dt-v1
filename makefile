
run0.check:
	g++ -std=c++17 ./0.check.cpp -o ./build/0.check -g && ./build/0.check


run1.integral:
	g++ -std=c++17 ./1.integral.cpp -o ./build/1.integral -g && ./build/1.integral
	

run2.1.queue:
	g++ -std=c++17 ./2.1.queue.cpp -o ./build/2.1.queue -g && ./build/2.1.queue
run2.1.1.queue:
	g++ -std=c++17 ./2.1.1.queue.cpp -o ./build/2.1.1.queue -g && ./build/2.1.1.queue
run2.1.2.queue:
	g++ -std=c++17 ./2.1.2.queue.cpp -o ./build/2.1.2.queue -g && ./build/2.1.2.queue

run2.2.stack:
	g++ -std=c++17 ./2.2.stack.cpp -o ./build/2.2.stack -g && ./build/2.2.stack
	