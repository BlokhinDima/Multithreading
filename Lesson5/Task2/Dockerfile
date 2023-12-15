FROM ubuntu:16.04
	ARG COMPILER=clang
	RUN apt-get update
	RUN apt-get install -y cmake ${COMPILER} nano make
	WORKDIR root/racesimulator
	COPY RaceSimulator .
	RUN mkdir build
	WORKDIR ./build

	RUN if [ "$COMPILER" = "clang" ];\
	then cmake -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_CXX_STANDARD=11 .. ;\
    	fi
	
	RUN if [ "$COMPILER" = "g++" ];\
	then cmake -D CMAKE_CXX_COMPILER=g++ -D CMAKE_CXX_STANDARD=11 .. ;\
    	fi

	RUN make
	CMD ["./RaceSimulator"]
