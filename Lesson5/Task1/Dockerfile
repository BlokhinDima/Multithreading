FROM ubuntu:16.04
	RUN apt-get update
	RUN apt-get install -y g++ nano
	WORKDIR root/helloworld
	COPY hello_world.cpp .
	RUN g++ hello_world.cpp -o hello_world
	CMD ["./hello_world"]
