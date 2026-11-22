# Simple TCP Message Protocol

The prototype uses newline-terminated text messages over TCP.

## Client to host

### Set player name
```text
NAME|player_name
```

### Move
```text
MOVE|dx|dy
```

Allowed movement values are `-1`, `0`, and `1`. Diagonal movement is rejected.

## Host to client

### Welcome
```text
WELCOME|player_id
```

### Shared state
```text
STATE|id,name,x,y,score;id,name,x,y,score
```

Each semicolon-separated record represents one connected player.

## Transport
- TCP over IPv4
- Default port: `54000`
- Same-machine test address: `127.0.0.1`
- Two-laptop test: host laptop's LAN IPv4 address
