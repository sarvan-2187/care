"""
Challenging Task 1: Distributed Shared Memory (DSM) - Memory Manager
Holds the shared variables in memory and serves them to every node on the
network. Runs on Computer 1:   python dsm_server.py [port]

Protocol (one JSON object per line over TCP):
  CREATE name value | READ name | WRITE name value | LOCK name | UNLOCK name
"""
import json
import socket
import sys
import threading

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 7000

shared_memory = {}          # name -> {"value": .., "version": .., "last_writer": ..}
locks = {}                  # name -> "ip:port" of the node holding the lock
table_lock = threading.Lock()


def log(msg):
    print(msg, flush=True)


def handle(req, client_ip, node_id):
    op, name = req.get("op"), req.get("name")
    with table_lock:
        if op == "CREATE":
            shared_memory[name] = {"value": req["value"], "version": 1,
                                   "last_writer": client_ip}
            log(f"[DSM] {client_ip} CREATED {name} = {req['value']}")
            return {"ok": True, **shared_memory[name]}

        if name not in shared_memory:
            return {"ok": False, "error": f"variable '{name}' does not exist"}

        if op == "READ":
            log(f"[DSM] {client_ip} READ    {name} -> {shared_memory[name]['value']}")
            return {"ok": True, **shared_memory[name]}

        if op == "LOCK":
            holder = locks.get(name)
            if holder and holder != node_id:
                return {"ok": False, "error": f"locked by {holder}"}
            locks[name] = node_id
            log(f"[DSM] {client_ip} LOCKED  {name}")
            return {"ok": True}

        if op == "UNLOCK":
            if locks.get(name) == node_id:
                del locks[name]
                log(f"[DSM] {client_ip} UNLOCKED {name}")
            return {"ok": True}

        if op == "WRITE":
            holder = locks.get(name)
            if holder and holder != node_id:
                return {"ok": False, "error": f"locked by {holder}"}
            old = shared_memory[name]["value"]
            shared_memory[name]["value"] = req["value"]
            shared_memory[name]["version"] += 1
            shared_memory[name]["last_writer"] = client_ip
            log(f"[DSM] {client_ip} WROTE   {name}: {old} -> {req['value']} "
                f"(version {shared_memory[name]['version']})")
            return {"ok": True, **shared_memory[name]}

    return {"ok": False, "error": "unknown operation"}


def client_thread(conn, addr):
    ip, node_id = addr[0], f"{addr[0]}:{addr[1]}"
    log(f"[+] Node {ip} connected")
    with conn, conn.makefile("r") as reader:
        for line in reader:
            try:
                reply = handle(json.loads(line), ip, node_id)
            except (ValueError, KeyError) as e:
                reply = {"ok": False, "error": str(e)}
            conn.sendall((json.dumps(reply) + "\n").encode())
    with table_lock:                       # release locks of a node that left
        for n in [n for n, h in locks.items() if h == node_id]:
            del locks[n]
    log(f"[-] Node {ip} disconnected")


def main():
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(("0.0.0.0", PORT))
    srv.listen(10)
    log(f"[*] DSM memory manager running on port {PORT}")
    while True:
        conn, addr = srv.accept()
        threading.Thread(target=client_thread, args=(conn, addr), daemon=True).start()


if __name__ == "__main__":
    main()
