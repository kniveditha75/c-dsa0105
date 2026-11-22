// C++ Multiplayer Arena - Host / Server
// Build (MinGW on Windows): g++ server.cpp -o server.exe -std=c++17 -lws2_32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>

#pragma comment(lib, "Ws2_32.lib")

constexpr int PORT = 54000;
constexpr int ARENA_W = 30;
constexpr int ARENA_H = 15;

struct Player {
    int id;
    SOCKET socket;
    std::string name;
    int x, y, score = 0;
    std::chrono::steady_clock::time_point lastTag =
        std::chrono::steady_clock::now() - std::chrono::seconds(2);
    std::atomic<bool> active{true};
};

std::vector<std::shared_ptr<Player>> players;
std::mutex playersMutex;
std::atomic<int> nextId{1};

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

std::string cleanName(std::string name) {
    for (char& c : name) {
        if (c == '|' || c == ';' || c == ',' || c == '\n' || c == '\r')
            c = '_';
    }
    if (name.empty()) name = "Player";
    if (name.size() > 16) name.resize(16);
    return name;
}

void removePlayer(int id) {
    std::lock_guard<std::mutex> lock(playersMutex);
    for (auto& p : players) {
        if (p->id == id) {
            p->active = false;
            closesocket(p->socket);
        }
    }
    players.erase(std::remove_if(players.begin(), players.end(),
        [id](const std::shared_ptr<Player>& p) { return p->id == id; }),
        players.end());
    std::cout << "Player " << id << " disconnected.\n";
}

void handleClient(std::shared_ptr<Player> player) {
    sendAll(player->socket, "WELCOME|" + std::to_string(player->id) + "\n");
    char buffer[512];
    std::string pending;

    while (player->active) {
        int n = recv(player->socket, buffer, sizeof(buffer), 0);
        if (n <= 0) break;
        pending.append(buffer, n);

        size_t pos;
        while ((pos = pending.find('\n')) != std::string::npos) {
            std::string line = pending.substr(0, pos);
            pending.erase(0, pos + 1);

            // Client command format: MOVE|dx|dy
            std::stringstream ss(line);
            std::string command, sx, sy;
            std::getline(ss, command, '|');
            std::getline(ss, sx, '|');
            std::getline(ss, sy, '|');

            if (command == "NAME") {
                std::string newName = cleanName(sx);
                std::lock_guard<std::mutex> lock(playersMutex);
                player->name = newName;
            } else if (command == "MOVE") {
                try {
                    int dx = std::stoi(sx), dy = std::stoi(sy);
                    if (dx < -1 || dx > 1 || dy < -1 || dy > 1) continue;
                    if (dx != 0 && dy != 0) continue; // no diagonal movement

                    std::lock_guard<std::mutex> lock(playersMutex);
                    player->x = std::clamp(player->x + dx, 0, ARENA_W - 1);
                    player->y = std::clamp(player->y + dy, 0, ARENA_H - 1);

                    // Tag an opponent when standing on the same tile.
                    auto now = std::chrono::steady_clock::now();
                    for (auto& other : players) {
                        if (other->id != player->id &&
                            other->x == player->x && other->y == player->y &&
                            now - player->lastTag > std::chrono::seconds(1)) {
                            player->score++;
                            player->lastTag = now;
                            // Move the tagged player to a fresh arena position.
                            other->x = (other->x + 7) % ARENA_W;
                            other->y = (other->y + 5) % ARENA_H;
                            std::cout << player->name << " tagged "
                                      << other->name << " | score: "
                                      << player->score << "\n";
                            break;
                        }
                    }
                } catch (...) {
                    // Ignore malformed movement messages.
                }
            }
        }
    }
    removePlayer(player->id);
}

void broadcastLoop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::vector<std::shared_ptr<Player>> snapshot;
        std::string message = "STATE|";
        {
            std::lock_guard<std::mutex> lock(playersMutex);
            snapshot = players;
            for (size_t i = 0; i < players.size(); ++i) {
                const auto& p = players[i];
                message += std::to_string(p->id) + "," + p->name + "," +
                    std::to_string(p->x) + "," + std::to_string(p->y) + "," +
                    std::to_string(p->score);
                if (i + 1 < players.size()) message += ";";
            }
        }
        message += "\n";

        for (const auto& p : snapshot) {
            if (p->active && !sendAll(p->socket, message)) {
                // The client handler will detect the disconnect.
            }
        }
    }
}

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Winsock startup failed.\n";
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr),
             sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Is port " << PORT << " already in use?\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "=====================================\n"
              << " C++ MULTIPLAYER ARENA - GAME HOST\n"
              << " Listening on TCP port " << PORT << "\n"
              << " Keep this window open while playing.\n"
              << "=====================================\n";

    std::thread(broadcastLoop).detach();

    std::mt19937 rng(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()));

    while (true) {
        sockaddr_in clientAddr{};
        int clientLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(listenSocket,
            reinterpret_cast<sockaddr*>(&clientAddr), &clientLen);
        if (clientSocket == INVALID_SOCKET) continue;

        auto player = std::make_shared<Player>();
        player->id = nextId++;
        player->socket = clientSocket;
        player->x = static_cast<int>(rng() % ARENA_W);
        player->y = static_cast<int>(rng() % ARENA_H);

        {
            std::lock_guard<std::mutex> lock(playersMutex);
            players.push_back(player);
        }

        std::cout << "New connection. Assigning player ID "
                  << player->id << ".\n";
        std::thread(handleClient, player).detach();
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
