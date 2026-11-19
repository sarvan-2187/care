# 23CSE312 Distributed Systems Lab - Exercise 1 + Challenging Task 1

Pure Python 3 (standard library only). Run each side on a **different computer on the same network**.

Find each machine's IP: `ipconfig` (Windows) or `ip a` / `ifconfig` (Linux/macOS).
If a connection times out, allow the port through the firewall on the listening machine
(Windows: allow Python when the firewall prompt appears).

| Program | Computer 1 | Computer 2 |
|---|---|---|
| 1. Client-Server chat | `python server.py 5000` | `python client.py <PC1_IP> 5000` |
| 2. P2P file listing | `python peer.py <folder> 6000` | `python peer.py <folder> 6000`, then `list <PC1_IP>` |
| 3. DSM | `python dsm_server.py 7000` and `python dsm_node.py 127.0.0.1` | `python dsm_node.py <PC1_IP>` |

DSM demo order: PC1 `create counter 10` -> PC2 `read counter`, `incr counter` -> PC1 `read counter` (shows 11, written by PC2's IP).

`Lab_Submission.docx` is the report: fill in the yellow-highlighted fields and paste your screenshots.
