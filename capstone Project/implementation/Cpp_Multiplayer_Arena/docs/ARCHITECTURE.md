# System Architecture

## Modules

### Module 1 — Player Client
- Reads player name and connects to the host using TCP.
- Captures keyboard movement commands.
- Sends movement commands to the host.
- Receives the latest shared player state.
- Displays the arena and scores.

### Module 2 — C++ Game Host
- Listens for TCP client connections on port `54000`.
- Assigns a unique player ID and starting position.
- Receives and validates movement commands.
- Keeps players inside arena boundaries.
- Detects tags and updates scores.
- Broadcasts the current game state to connected clients.

## Data flow

```text
Keyboard input
     |
     v
Player Client -- MOVE command --> TCP Host
                                  |
                                  v
                         Validate and move player
                                  |
                                  v
                         Collision/tag detection
                                  |
                                  v
                           Update score/state
                                  |
                                  v
Player Client <-- STATE broadcast --+
     |
     v
Render arena and scoreboard
```

The host owns the authoritative game state. Clients do not directly change another player's position or score.
