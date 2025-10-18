# Makefile for CPU Scheduling Algorithms Simulator

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
TESTFLAGS = -std=c++11 -Wall -Wextra -O2 -g

# Source files
MAIN_SOURCES = main.cpp Job.cpp FCFS.cpp SJN.cpp SRT.cpp RoundRobin.cpp OutputFormatter.cpp SchedulerBase.cpp
TEST_SOURCES = test_main.cpp test_framework.cpp test_job.cpp test_scheduler_base.cpp test_fcfs.cpp test_sjn.cpp test_srt.cpp test_round_robin.cpp test_integration.cpp
COMPREHENSIVE_TEST_SOURCES = run_all_tests.cpp test_framework.cpp test_job.cpp test_scheduler_base.cpp test_fcfs.cpp test_sjn.cpp test_srt.cpp test_round_robin.cpp test_integration.cpp test_edge_cases.cpp

# Object files
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
COMPREHENSIVE_TEST_OBJECTS = $(COMPREHENSIVE_TEST_SOURCES:.cpp=.o)

# Executables
MAIN_TARGET = scheduler
TEST_TARGET = test_scheduler
COMPREHENSIVE_TEST_TARGET = comprehensive_tests

# Default target
all: $(MAIN_TARGET) $(TEST_TARGET) $(COMPREHENSIVE_TEST_TARGET)

# Main program
$(MAIN_TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test program
$(TEST_TARGET): $(TEST_OBJECTS) Job.o SchedulerBase.o FCFS.o SJN.o SRT.o RoundRobin.o OutputFormatter.o
	$(CXX) $(TESTFLAGS) -o $@ $^

# Comprehensive test program
$(COMPREHENSIVE_TEST_TARGET): $(COMPREHENSIVE_TEST_OBJECTS) Job.o SchedulerBase.o FCFS.o SJN.o SRT.o RoundRobin.o OutputFormatter.o
	$(CXX) $(TESTFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main program
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run comprehensive tests (includes edge cases)
test-all: $(COMPREHENSIVE_TEST_TARGET)
	./$(COMPREHENSIVE_TEST_TARGET)

# Run tests with verbose output
test-verbose: $(TEST_TARGET)
	./$(TEST_TARGET) | tee test_results.txt

# Run comprehensive tests with verbose output
test-all-verbose: $(COMPREHENSIVE_TEST_TARGET)
	./$(COMPREHENSIVE_TEST_TARGET) | tee comprehensive_test_results.txt

# Run specific test categories
test-job: test_framework.o test_job.o Job.o
	$(CXX) $(TESTFLAGS) -o test_job_only $^
	./test_job_only

test-fcfs: test_framework.o test_fcfs.o Job.o SchedulerBase.o FCFS.o
	$(CXX) $(TESTFLAGS) -o test_fcfs_only $^
	./test_fcfs_only

test-sjn: test_framework.o test_sjn.o Job.o SchedulerBase.o SJN.o
	$(CXX) $(TESTFLAGS) -o test_sjn_only $^
	./test_sjn_only

test-srt: test_framework.o test_srt.o Job.o SchedulerBase.o SRT.o
	$(CXX) $(TESTFLAGS) -o test_srt_only $^
	./test_srt_only

test-rr: test_framework.o test_round_robin.o Job.o SchedulerBase.o RoundRobin.o
	$(CXX) $(TESTFLAGS) -o test_rr_only $^
	./test_rr_only

# Memory check with valgrind (if available)
memcheck: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_TARGET)

# Performance profiling
profile: $(MAIN_TARGET)
	gprof ./$(MAIN_TARGET) gmon.out > profile.txt

# Clean up
clean:
	rm -f *.o $(MAIN_TARGET) $(TEST_TARGET) $(COMPREHENSIVE_TEST_TARGET) test_*_only test_results.txt comprehensive_test_results.txt profile.txt gmon.out

# Clean everything including executables
distclean: clean
	rm -f scheduler.exe

# Install dependencies (if needed)
install-deps:
	@echo "No external dependencies required for this project"

# Help
help:
	@echo "Available targets:"
	@echo "  all              - Build main program and all tests"
	@echo "  scheduler        - Build main program only"
	@echo "  test             - Build and run basic tests"
	@echo "  test-all         - Build and run comprehensive tests (includes edge cases)"
	@echo "  test-verbose     - Run basic tests with output to file"
	@echo "  test-all-verbose - Run comprehensive tests with output to file"
	@echo "  test-job         - Run Job class tests only"
	@echo "  test-fcfs        - Run FCFS tests only"
	@echo "  test-sjn         - Run SJN tests only"
	@echo "  test-srt         - Run SRT tests only"
	@echo "  test-rr          - Run Round Robin tests only"
	@echo "  run              - Run the main program"
	@echo "  memcheck         - Run tests with valgrind"
	@echo "  profile          - Profile the main program"
	@echo "  clean            - Remove object files and executables"
	@echo "  distclean        - Remove all generated files"
	@echo "  help             - Show this help message"

# Phony targets
.PHONY: all run test test-all test-verbose test-all-verbose test-job test-fcfs test-sjn test-srt test-rr memcheck profile clean distclean install-deps help
