#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

void listFiles(const std::string& path) {
    std::cout << "Files in " << path << ":\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << entry.path().filename().string() << "\n";
    }
    std::cout << std::endl;
}

void createDirectory(const std::string& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created: " << path << std::endl;
    } else {
        std::cout << "Failed to create directory: " << path << std::endl;
    }
}

void deleteFile(const std::string& path) {
    if (fs::remove(path)) {
        std::cout << "File deleted: " << path << std::endl;
    } else {
        std::cout << "Failed to delete file: " << path << std::endl;
    }
}

void deleteDirectory(const std::string& path) {
    if (fs::remove_all(path)) {
        std::cout << "Directory deleted: " << path << std::endl;
    } else {
        std::cout << "Failed to delete directory: " << path << std::endl;
    }
}

void handleCommand(const std::string& command, const std::vector<std::string>& args) {
    if (command == "ls") {
        std::string path = args.empty() ? fs::current_path().string() : args[0];
        listFiles(path);
    } else if (command == "mkdir") {
        if (args.empty()) {
            std::cout << "Missing directory name.\n";
        } else {
            std::string path = args[0];
            createDirectory(path);
        }
    } else if (command == "rm") {
        if (args.empty()) {
            std::cout << "Missing file/directory name.\n";
        } else {
            std::string path = args[0];
            if (fs::is_directory(path)) {
                deleteDirectory(path);
            } else {
                deleteFile(path);
            }
        }
    } else if (command == "exit") {
        std::cout << "Exiting the file manager.\n";
        exit(0);
    } else {
        std::cout << "Invalid command: " << command << ".\n";
    }
}

void printPrompt() {
    std::cout << "\n=== File Manager ===\n";
    std::cout << "Available commands: ls, mkdir, rm, exit\n";
    std::cout << "Enter a command: ";
}

int main() {
    while (true) {
        printPrompt();
        
        std::string input;
        std::getline(std::cin, input);
        
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        if (!tokens.empty()) {
            std::string command = tokens[0];
            tokens.erase(tokens.begin());
            handleCommand(command, tokens);
        }
    }
    
    return 0;
}
