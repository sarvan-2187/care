# 23CSE312 Distributed Systems Lab

Copy this folder to `S:\DS-LAB` so the layout is:

```
S:\DS-LAB\Expt_1      Lab Exercise 1: Server/Client (chat), Peer (P2P file listing) - Java + Python
S:\DS-LAB\Ch_Task_1   Challenging Task 1: DSMServer / DSMNode (Distributed Shared Memory) - Java + Python
```

Standard libraries only. Run each side on a **different computer on the same network**.
Find each machine's IP with `ipconfig`. If a connection times out, allow Java/Python through Windows Firewall.

| Program | Computer 1 (PowerShell) | Computer 2 (PowerShell) |
|---|---|---|
| Chat | `cd S:\DS-LAB\Expt_1`; `javac Server.java`; `java Server 5000` (or `python server.py 5000`) | `javac Client.java`; `java Client <PC1_IP> 5000` (or `python client.py <PC1_IP> 5000`) |
| P2P listing | `mkdir shared` (add files); `javac Peer.java`; `java Peer shared 6000` | same, then `list <PC1_IP>` |
| DSM | `cd S:\DS-LAB\Ch_Task_1`; `javac *.java`; `java DSMServer 7000`; second window: `java DSMNode 127.0.0.1 7000` | `java DSMNode <PC1_IP> 7000` |

DSM demo: PC1 `create counter 10` -> PC2 `read counter`, `incr counter` -> PC1 `read counter` (shows 11, written by PC2's IP).

Reports: `Lab_Exercise_1_Submission.docx` and `Challenging_Task_1_DSM_Submission.docx`. Fill in the yellow fields.
The screenshots in `assets/screenshots/` come from a single-machine test run (same IP on both sides),
so replace them with screenshots from your two computers before submitting.
