"""
Challenging Task 1: Distributed Shared Memory (DSM) - Node
Every computer uses this program to access the shared memory.

  python dsm_node.py <dsm_server_ip> [port]

Commands:
  create <name> <value>   create a shared variable
  read   <name>           read the current value
  write  <name> <value>   overwrite the value
  incr   <name> [n]       LOCK -> READ -> value+n -> WRITE -> UNLOCK
  exit
"""
import json
import socket
import sys

if len(sys.argv) < 2:
    sys.exit("Usage: python dsm_node.py <dsm_server_ip> [port]")
SERVER_IP = sys.argv[1]
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 7000


class DSMClient:
    def __init__(self, ip, port):
        self.sock = socket.create_connection((ip, port))
        self.reader = self.sock.makefile("r")

    def call(self, **req):
        self.sock.sendall((json.dumps(req) + "\n").encode())
        reply = json.loads(self.reader.readline())
        if not reply["ok"]:
            raise RuntimeError(reply["error"])
        return reply

    def create(self, name, value): return self.call(op="CREATE", name=name, value=value)
    def read(self, name):          return self.call(op="READ", name=name)
    def write(self, name, value):  return self.call(op="WRITE", name=name, value=value)
    def lock(self, name):          return self.call(op="LOCK", name=name)
    def unlock(self, name):        return self.call(op="UNLOCK", name=name)


def main():
    dsm = DSMClient(SERVER_IP, PORT)
    print(f"[*] This node's IP : {dsm.sock.getsockname()[0]}")
    print(f"[*] DSM server     : {SERVER_IP}:{PORT}")
    print("Commands: create <n> <v> | read <n> | write <n> <v> | incr <n> [k] | exit")
    while True:
        try:
            cmd = input("dsm> ").split()
        except (EOFError, KeyboardInterrupt):
            break
        if not cmd:
            continue
        try:
            if cmd[0] == "exit":
                break
            elif cmd[0] == "create":
                r = dsm.create(cmd[1], int(cmd[2]))
                print(f"Created shared variable {cmd[1]} = {r['value']}")
            elif cmd[0] == "read":
                r = dsm.read(cmd[1])
                print(f"{cmd[1]} = {r['value']}  (version {r['version']}, "
                      f"last written by {r['last_writer']})")
            elif cmd[0] == "write":
                r = dsm.write(cmd[1], int(cmd[2]))
                print(f"Wrote {cmd[1]} = {r['value']}  (version {r['version']})")
            elif cmd[0] == "incr":
                step = int(cmd[2]) if len(cmd) > 2 else 1
                dsm.lock(cmd[1])
                try:
                    old = dsm.read(cmd[1])["value"]
                    print(f"Read  {cmd[1]} = {old}")
                    new = old + step
                    print(f"Modify {old} + {step} = {new}")
                    r = dsm.write(cmd[1], new)
                    print(f"Wrote {cmd[1]} = {new} back to shared memory "
                          f"(version {r['version']})")
                finally:
                    dsm.unlock(cmd[1])
            else:
                print("Unknown command")
        except (IndexError, ValueError):
            print("Bad arguments")
        except RuntimeError as e:
            print("DSM error:", e)
    print("[*] Node stopped.")


if __name__ == "__main__":
    main()
