# C++ Multiplayer Arena — Real-Time TCP Networking Game

A console-based multiplayer arena game written in **C++17** using **TCP sockets (Winsock)**. One laptop runs the authoritative game host, while other laptops join as clients over the same Wi-Fi/LAN.

## Features

- Multiple clients connect to one game host
- Player names and unique player IDs
- Keyboard movement (`W`, `A`, `S`, `D`)
- Shared arena state broadcast to all connected clients
- Server-side collision/tag detection and score updates
- Basic disconnect handling
- Console-based arena display

## Project structure

```text
Cpp_Multiplayer_Arena/
├── server.cpp          # Host: accepts clients, updates game state, broadcasts
├── client.cpp          # Client: keyboard input, network receive, arena display
├── build.bat           # Compiles both programs with MinGW-w64
├── run_server.bat      # Starts the host
├── run_client.bat      # Starts a client (optional host IP argument)
├── .gitignore
├── .vscode/
│   └── tasks.json      # VS Code build tasks
└── docs/
    ├── ARCHITECTURE.md
    └── NETWORK_PROTOCOL.md
```

## Requirements

- Windows 10/11
- Visual Studio Code (recommended)
- MinGW-w64 GCC with C++17 support
- Both laptops connected to the same Wi-Fi/LAN for a two-laptop demo

> The source uses Windows Winsock. It is not directly portable to Linux/macOS without adapting the socket layer.

## Build

Install a MinGW-w64 toolchain and ensure `g++` is on your Windows `PATH`. Open this folder in VS Code, then open a PowerShell terminal and run:

```powershell
.\build.bat
```

Or compile manually:

```powershell
g++ server.cpp -o server.exe -std=c++17 -lws2_32
g++ client.cpp -o client.exe -std=c++17 -lws2_32
```

## Run on one laptop (local test)

Open separate terminals in this folder.

**Terminal 1 — Host**
```powershell
.\run_server.bat
```

**Terminal 2 — Player 1**
```powershell
.\run_client.bat
```

**Terminal 3 — Player 2**
```powershell
.\run_client.bat
```

The default client address is `127.0.0.1` (loopback), which is only for testing on the same computer.

## Run on two laptops over Wi-Fi

1. Connect both laptops to the same Wi-Fi network.
2. On Laptop 1, run `ipconfig` and note its **IPv4 Address** (for example, `192.168.1.10`).
3. On Laptop 1, run `run_server.bat` and keep the host window open.
4. If Windows Firewall prompts, allow the server on **Private networks**. If needed, create an inbound TCP rule for port `54000` on the host laptop.
5. On Laptop 2, copy the project folder, build it using `build.bat`, and run:

```powershell
.\run_client.bat 192.168.1.10
```

Replace `192.168.1.10` with Laptop 1's actual IPv4 address.

Do not expose this educational prototype directly to the public internet. Use a trusted local network.

## Controls

| Key | Action |
|---|---|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `Q` | Quit |

The client displays `P` for the local player and `O` for other players. Move onto another player's tile to tag them and gain a point.

## Architecture

```text
+---------------------+         TCP MOVE commands
| Laptop 2            | --------------------------------+
| Player Client       |                                 |
| Keyboard + Display  | <----------------------------+  |
+---------------------+       STATE broadcasts       |  |
                                                      v  v
                                             +----------------------+
                                             | Laptop 1             |
                                             | C++ Game Host        |
                                             |                      |
                                             | - Accept connections |
                                             | - Update positions  |
                                             | - Detect tags        |
                                             | - Update scores      |
                                             | - Broadcast state    |
                                             +----------------------+
                                                      ^  ^
+---------------------+       STATE broadcasts       |  |
| Laptop 1            | <----------------------------+  |
| Player Client       | --------------------------------+
| (optional local)    |         TCP MOVE commands
+---------------------+
```

## Important implementation note

The host is authoritative: clients send movement commands, and the host updates positions, detects tags, maintains scores, and broadcasts the shared state. This is a learning/demo prototype, not a production-ready game server. It does not yet include authentication, encryption, matchmaking, lag compensation, or robust packet framing.

## GitHub upload

1. Create a new repository on GitHub (for example, `cpp-multiplayer-arena`).
2. Extract this project ZIP.
3. Open the extracted folder in VS Code.
4. Initialize Git and push:

```bash
git init
git add .
git commit -m "Initial C++ multiplayer arena implementation"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/cpp-multiplayer-arena.git
git push -u origin main
```

Replace `YOUR-USERNAME` with your GitHub username. Alternatively, use GitHub Desktop and choose **Add an Existing Repository**.
