# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Library flags
LIBS_MAGIC = -lmagic
LIBS_OPENCV = `pkg-config --cflags --libs opencv4`

# Binaries and sources
BINARIES = spearkill file_type ASCII_string_extraction hexdump johntheripper lsb_datdecry00 lsb_customencrypt lsb_customdecrypt 
SOURCES = spearkill.cpp file_type.cpp ASCII_string_extraction.cpp hexdump.cpp johntheripper.cpp lsb_datdecry00.cpp lsb_customencrypt.cpp lsb_customdecrypt.cpp

# Default target
all: $(BINARIES)

# Rules for each binary
spearkill: spearkill.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS_MAGIC) $(LIBS_OPENCV)

file_type: file_type.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS_MAGIC)

ASCII_string_extraction: ASCII_string_extraction.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

hexdump: hexdump.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

johntheripper: johtheripper.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

lsb_datdecry00: lsb_datdecry00.cpp
        $(CXX) $(CXXFLAGS) -o $@ $< $(LIBS_OPENCV)

lsb_customencrypt: lsb_customencrypt.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS_OPENCV)

lsb_customdecrypt: lsb_customdecrypt.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS_OPENCV)

# Clean target to remove binaries
clean:
	rm -f $(BINARIES) *.o

# Install target to move binaries and man page
install:
	mkdir -p /usr/local/bin
	cp $(BINARIES) /usr/local/bin/
	mkdir -p /usr/local/man/man1
	cp spearkill.1 /usr/local/man/man1/

# Uninstall target
uninstall:
	rm -f /usr/local/bin/$(BINARIES)
	rm -f /usr/local/man/man1/spearkill.1

