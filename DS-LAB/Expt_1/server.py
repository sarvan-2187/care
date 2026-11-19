"""
Exercise 1: Client-Server Communication (bidirectional chat) - SERVER
Run on Computer A:  python server.py [port]
"""
import os
import socket
import sys
import threading

HOST = "0.0.0.0"          # listen on all network interfaces
PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 5000


def get_local_ip():
    """Return the IP address this machine uses on the LAN."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))   # no packet is sent; only picks the outgoing interface
        return s.getsockname()[0]
    except OSError:
        return "127.0.0.1"
    finally:
        s.close()
closing = False          # True once WE end the chat


def receive_loop(conn, peer):
    """Print every message the client sends until it disconnects."""
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            msg = data.decode().strip()
            print(f"\nClient ({peer}): {msg}\nServer> ", end="", flush=True)
            if msg.lower() == "bye":
                break
    except OSError:
        pass
    if not closing:                       # the other side ended the chat
        print(f"\n[!] Client {peer} disconnected.")
        os._exit(0)


def main():
    global closing
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen(1)
    print(f"[*] Server IP  : {get_local_ip()}")
    print(f"[*] Listening on port {PORT} ... waiting for a client")

    conn, addr = server.accept()
    peer = addr[0]
    print(f"[+] Connected to client {peer}:{addr[1]}")
    print("Type a message and press Enter ('bye' to quit).")

    # receiving runs in its own thread, so sending and receiving happen at the same time
    t = threading.Thread(target=receive_loop, args=(conn, peer), daemon=True)
    t.start()

    try:
        while t.is_alive():
            msg = input("Server> ")
            if not t.is_alive():
                break
            if msg.lower() == "bye":
                closing = True
            conn.sendall(msg.encode())
            if closing:
                break
    except (EOFError, KeyboardInterrupt, BrokenPipeError):
        pass
    finally:
        conn.close()
        server.close()
        print("[*] Server closed.")


if __name__ == "__main__":
    main()
