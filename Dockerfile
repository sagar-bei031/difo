# Use an official Ubuntu image as the base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Update package lists and install necessary tools
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake

# Copy the entire project directory into the container
COPY . /app

# Clean any existing build directory (if any)
RUN rm -rf build

# Create a build directory and compile the project
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Make the compiled binary executable
RUN chmod +x /app/build/src/difo

# Set the entry point for the container
ENTRYPOINT ["/app/build/src/difo"]
