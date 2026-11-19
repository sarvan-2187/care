"""
Exercise 1: Client-Server Communication (bidirectional chat) - CLIENT
Run on Computer B:  python client.py <server_ip> [port]
"""
import socket
import sys
import threading

if len(sys.argv) < 2:
    sys.exit("Usage: python client.py <server_ip> [port]")
SERVER_IP = sys.argv[1]
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 5000


def receive_loop(sock):
    """Print every message the server sends until it disconnects."""
    while True:
        data = sock.recv(1024)
        if not data:
            print("\n[!] Server disconnected.")
            break
        msg = data.decode().strip()
        print(f"\nServer ({SERVER_IP}): {msg}\nClient> ", end="", flush=True)
        if msg.lower() == "bye":
            break


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, PORT))
    print(f"[*] Client IP  : {sock.getsockname()[0]}")
    print(f"[+] Connected to server {SERVER_IP}:{PORT}")
    print("Type a message and press Enter ('bye' to quit).")

    t = threading.Thread(target=receive_loop, args=(sock,), daemon=True)
    t.start()

    try:
        while t.is_alive():
            msg = input("Client> ")
            if not t.is_alive():
                break
            sock.sendall(msg.encode())
            if msg.lower() == "bye":
                break
    except (EOFError, KeyboardInterrupt, BrokenPipeError):
        pass
    finally:
        sock.close()
        print("[*] Client closed.")


if __name__ == "__main__":
    main()
