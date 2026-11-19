"""
Exercise 2: Peer-to-Peer File Listing
Every peer is both a server (shares the file list of its own folder)
and a client (asks another peer for that peer's file list).

Run on every computer:  python peer.py <shared_folder> [port]
Then at the prompt type:   list <peer_ip> [port]
"""
import datetime
import json
import os
import socket
import sys
import threading

if len(sys.argv) < 2:
    sys.exit("Usage: python peer.py <shared_folder> [port]")
SHARED_DIR = os.path.abspath(sys.argv[1])
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 6000

if not os.path.isdir(SHARED_DIR):
    sys.exit(f"Folder not found: {SHARED_DIR}")


def get_local_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except OSError:
        return "127.0.0.1"
    finally:
        s.close()


def list_local_files():
    """Read the REAL contents of the shared folder at the moment of the request."""
    files = []
    for name in sorted(os.listdir(SHARED_DIR)):
        path = os.path.join(SHARED_DIR, name)
        if os.path.isfile(path):
            st = os.stat(path)
            files.append({
                "name": name,
                "size": st.st_size,
                "modified": datetime.datetime.fromtimestamp(st.st_mtime)
                                    .strftime("%Y-%m-%d %H:%M:%S"),
            })
    return files


# ---------------- server side of the peer ----------------
def handle_peer(conn, addr):
    with conn:
        request = conn.recv(1024).decode().strip()
        if request == "LIST":
            files = list_local_files()
            reply = {"host": get_local_ip(), "folder": SHARED_DIR, "files": files}
            conn.sendall(json.dumps(reply).encode())
            print(f"\n[server] Sent list of {len(files)} file(s) to {addr[0]}\npeer> ",
                  end="", flush=True)
        else:
            conn.sendall(json.dumps({"error": "unknown command"}).encode())


def serve():
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(("0.0.0.0", PORT))
    srv.listen(5)
    while True:
        conn, addr = srv.accept()
        threading.Thread(target=handle_peer, args=(conn, addr), daemon=True).start()


# ---------------- client side of the peer ----------------
def request_list(ip, port):
    with socket.create_connection((ip, port), timeout=5) as s:
        s.sendall(b"LIST")
        chunks = []
        while True:
            part = s.recv(4096)
            if not part:
                break
            chunks.append(part)
    reply = json.loads(b"".join(chunks).decode())
    if "error" in reply:
        print("Error from peer:", reply["error"])
        return
    print(f"\nFiles shared by peer {reply['host']} (folder: {reply['folder']})")
    print(f"{'No':<4}{'File name':<30}{'Size (bytes)':>14}  {'Last modified'}")
    print("-" * 70)
    for i, f in enumerate(reply["files"], 1):
        print(f"{i:<4}{f['name']:<30}{f['size']:>14}  {f['modified']}")
    print(f"Total: {len(reply['files'])} file(s)\n")


def main():
    threading.Thread(target=serve, daemon=True).start()
    print(f"[*] Peer IP      : {get_local_ip()}")
    print(f"[*] Port         : {PORT}")
    print(f"[*] Shared folder: {SHARED_DIR}")
    print("Commands: list <peer_ip> [port] | mylist | exit")
    while True:
        try:
            cmd = input("peer> ").split()
        except (EOFError, KeyboardInterrupt):
            break
        if not cmd:
            continue
        if cmd[0] == "exit":
            break
        elif cmd[0] == "mylist":
            for f in list_local_files():
                print(f"  {f['name']}  ({f['size']} bytes)")
        elif cmd[0] == "list" and len(cmd) >= 2:
            port = int(cmd[2]) if len(cmd) > 2 else PORT
            try:
                request_list(cmd[1], port)
            except OSError as e:
                print(f"Could not reach {cmd[1]}:{port} -> {e}")
        else:
            print("Commands: list <peer_ip> [port] | mylist | exit")
    print("[*] Peer stopped.")


if __name__ == "__main__":
    main()
