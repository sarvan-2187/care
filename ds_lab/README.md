# 23CSE312 Distributed Systems Lab - Exercise 1 + Challenging Task 1

Every program is provided in **Java** (`java/`) and **Python 3** (top-level folders). Standard libraries only. Run each side on a **different computer on the same network**.

Find each machine's IP: `ipconfig` (Windows) or `ip a` / `ifconfig` (Linux/macOS).
If a connection times out, allow the port through the firewall on the listening machine
(Windows: allow Python when the firewall prompt appears).

Java: compile first with `javac *.java` inside the folder.

| Program | Computer 1 | Computer 2 |
|---|---|---|
| 1. Client-Server chat | `java Server 5000` / `python server.py 5000` | `java Client <PC1_IP> 5000` / `python client.py <PC1_IP> 5000` |
| 2. P2P file listing | `java Peer shared 6000` / `python peer.py shared 6000` | same, then `list <PC1_IP>` |
| 3. DSM | `java DSMServer 7000` + `java DSMNode 127.0.0.1 7000` (or the `.py` equivalents) | `java DSMNode <PC1_IP> 7000` |

DSM demo order: PC1 `create counter 10` -> PC2 `read counter`, `incr counter` -> PC1 `read counter` (shows 11, written by PC2's IP).

`Lab_Submission.docx` is the report (logo, Java + Python code, output screenshots). Fill in the yellow-highlighted fields.
The screenshots in `assets/screenshots/` come from a single-machine test run, so both sides show the same IP;
replace them with screenshots from your two computers before submitting.
