// C++ Multiplayer Arena - Player Client
// Build (MinGW on Windows): g++ client.cpp -o client.exe -std=c++17 -lws2_32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

#pragma comment(lib, "Ws2_32.lib")

constexpr int PORT = 54000;
constexpr int ARENA_W = 30;
constexpr int ARENA_H = 15;

struct RemotePlayer {
    int id;
    std::string name;
    int x, y, score;
};

std::vector<RemotePlayer> gamePlayers;
std::mutex stateMutex;
std::atomic<bool> running{true};
int myId = -1;

bool sendAll(SOCKET s, const std::string& data) {
    const char* p = data.c_str();
    int left = static_cast<int>(data.size());
    while (left > 0) {
        int sent = send(s, p, left, 0);
        if (sent == SOCKET_ERROR || sent == 0) return false;
        p += sent;
        left -= sent;
    }
    return true;
}

void parseState(const std::string& line) {
    // STATE|id,name,x,y,score;id,name,x,y,score
    std::vector<RemotePlayer> updated;
    size_t start = line.find('|');
    if (start == std::string::npos) return;
    std::stringstream all(line.substr(start + 1));
    std::string item;

    while (std::getline(all, item, ';')) {
        std::stringstream fields(item);
        std::string sid, name, sx, sy, score;
        if (!std::getline(fields, sid, ',') ||
            !std::getline(fields, name, ',') ||
            !std::getline(fields, sx, ',') ||
            !std::getline(fields, sy, ',') ||
            !std::getline(fields, score, ',')) continue;
        try {
            updated.push_back({std::stoi(sid), name, std::stoi(sx),
                               std::stoi(sy), std::stoi(score)});
        } catch (...) {}
    }

    std::lock_guard<std::mutex> lock(stateMutex);
    gamePlayers = std::move(updated);
}

void receiveLoop(SOCKET serverSocket) {
    char buffer[2048];
    std::string pending;
    while (running) {
        int n = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            running = false;
            break;
        }
        pending.append(buffer, n);
        size_t pos;
        while ((pos = pending.find('\n')) != std::string::npos) {
            std::string line = pending.substr(0, pos);
            pending.erase(0, pos + 1);
            if (line.rfind("STATE|", 0) == 0) parseState(line);
        }
    }
}

void drawArena() {
    std::vector<RemotePlayer> snapshot;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        snapshot = gamePlayers;
    }

    system("cls");
    std::cout << "========== C++ MULTIPLAYER ARENA ==========\n";
    std::cout << "You are Player ID: " << myId
              << " | Move: W A S D | Quit: Q\n\n";

    std::cout << '+';
    for (int x = 0; x < ARENA_W; ++x) std::cout << '-';
    std::cout << "+\n";

    for (int y = 0; y < ARENA_H; ++y) {
        std::cout << '|';
        for (int x = 0; x < ARENA_W; ++x) {
            char cell = ' ';
            for (const auto& p : snapshot) {
                if (p.x == x && p.y == y) {
                    cell = (p.id == myId) ? 'P' : 'O';
                    break;
                }
            }
            std::cout << cell;
        }
        std::cout << "|\n";
    }

    std::cout << '+';
    for (int x = 0; x < ARENA_W; ++x) std::cout << '-';
    std::cout << "+\n\n";

    std::cout << "PLAYER SCORES\n";
    for (const auto& p : snapshot) {
        std::cout << (p.id == myId ? " > " : "   ")
                  << p.name << " (ID " << p.id << "): "
                  << p.score << '\n';
    }
    std::cout << "\nTag an opponent by moving onto their tile.\n";
}

int main(int argc, char* argv[]) {
    std::string hostIP = (argc >= 2) ? argv[1] : "127.0.0.1";

    std::string playerName;
    std::cout << "Enter your player name: ";
    std::getline(std::cin, playerName);
    if (playerName.empty()) playerName = "Player";

    for (char& c : playerName) {
        if (c == '|' || c == ';' || c == ',' || c == '\n' || c == '\r')
            c = '_';
    }
    if (playerName.size() > 16) playerName.resize(16);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Winsock startup failed.\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, hostIP.c_str(), &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid host IP address.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connecting to " << hostIP << ":" << PORT << "...\n";
    if (connect(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr),
                sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed. Start server.exe first and check IP/firewall.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Read the initial WELCOME message before starting the receiver thread.
    char welcomeBuffer[128];
    int welcomeBytes = recv(serverSocket, welcomeBuffer,
                            sizeof(welcomeBuffer) - 1, 0);
    if (welcomeBytes <= 0) {
        std::cerr << "Host closed the connection.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    welcomeBuffer[welcomeBytes] = '\0';
    std::string welcome(welcomeBuffer);
    size_t bar = welcome.find('|');
    size_t newline = welcome.find('\n');
    if (bar != std::string::npos) {
        try { myId = std::stoi(welcome.substr(bar + 1, newline - bar - 1)); }
        catch (...) { myId = -1; }
    }

    // Send the name as a separate command. Host associates it with this socket.
    sendAll(serverSocket, "NAME|" + playerName + "\n");

    std::cout << "Connected! Your player ID is " << myId
              << ". Press any key to enter the arena...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    std::thread receiver(receiveLoop, serverSocket);

    while (running) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 'q' || key == 'Q') {
                running = false;
                break;
            }

            int dx = 0, dy = 0;
            if (key == 'w' || key == 'W') dy = -1;
            else if (key == 's' || key == 'S') dy = 1;
            else if (key == 'a' || key == 'A') dx = -1;
            else if (key == 'd' || key == 'D') dx = 1;

            if (dx != 0 || dy != 0) {
                if (!sendAll(serverSocket, "MOVE|" + std::to_string(dx) +
                             "|" + std::to_string(dy) + "\n")) {
                    running = false;
                }
            }
        }

        drawArena();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    shutdown(serverSocket, SD_BOTH);
    closesocket(serverSocket);
    if (receiver.joinable()) receiver.join();
    WSACleanup();
    std::cout << "Disconnected from the arena.\n";
    return 0;
}
