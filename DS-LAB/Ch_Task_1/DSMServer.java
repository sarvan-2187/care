// Challenging Task 1: Distributed Shared Memory (DSM) - Memory Manager
// Keeps the shared variables and serves them to every node on the network.
// Compile: javac DSMServer.java     Run on Computer 1: java DSMServer [port]
//
// Protocol (one text line per request):
//   CREATE name value | READ name | WRITE name value | LOCK name | UNLOCK name
// Replies:  OK value version lastWriter   |   OK   |   ERR message
import java.io.*;
import java.net.*;
import java.util.*;

public class DSMServer {

    static class SharedVar {
        int value, version;
        String lastWriter;
        SharedVar(int value, String writer) { this.value = value; this.version = 1; this.lastWriter = writer; }
        String reply() { return "OK " + value + " " + version + " " + lastWriter; }
    }

    static final Map<String, SharedVar> memory = new HashMap<>();
    static final Map<String, String> locks = new HashMap<>();   // name -> "ip:port" of lock holder

    static void log(String s) { System.out.println(s); }

    // synchronized => only one request touches the shared memory at a time
    static synchronized String handle(String line, String ip, String nodeId) {
        String[] p = line.trim().split("\\s+");
        String op = p[0].toUpperCase();
        if (p.length < 2) return "ERR missing variable name";
        String name = p[1];

        if (op.equals("CREATE")) {
            SharedVar v = new SharedVar(Integer.parseInt(p[2]), ip);
            memory.put(name, v);
            log("[DSM] " + ip + " CREATED " + name + " = " + v.value);
            return v.reply();
        }
        SharedVar v = memory.get(name);
        if (v == null) return "ERR variable '" + name + "' does not exist";
        String holder = locks.get(name);

        switch (op) {
            case "READ":
                log("[DSM] " + ip + " READ    " + name + " -> " + v.value);
                return v.reply();
            case "LOCK":
                if (holder != null && !holder.equals(nodeId)) return "ERR locked by " + holder;
                locks.put(name, nodeId);
                log("[DSM] " + ip + " LOCKED  " + name);
                return "OK";
            case "UNLOCK":
                if (nodeId.equals(holder)) {
                    locks.remove(name);
                    log("[DSM] " + ip + " UNLOCKED " + name);
                }
                return "OK";
            case "WRITE":
                if (holder != null && !holder.equals(nodeId)) return "ERR locked by " + holder;
                int old = v.value;
                v.value = Integer.parseInt(p[2]);
                v.version++;
                v.lastWriter = ip;
                log("[DSM] " + ip + " WROTE   " + name + ": " + old + " -> " + v.value
                        + " (version " + v.version + ")");
                return v.reply();
            default:
                return "ERR unknown operation";
        }
    }

    static void serveNode(Socket s) {
        String ip = s.getInetAddress().getHostAddress();
        String nodeId = ip + ":" + s.getPort();
        log("[+] Node " + ip + " connected");
        try (s;
             BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
             PrintWriter out = new PrintWriter(s.getOutputStream(), true)) {
            String line;
            while ((line = in.readLine()) != null) {
                try {
                    out.println(handle(line, ip, nodeId));
                } catch (RuntimeException e) {
                    out.println("ERR bad request");
                }
            }
        } catch (IOException ignored) { }
        synchronized (DSMServer.class) {             // free locks held by a node that left
            locks.values().removeIf(h -> h.equals(nodeId));
        }
        log("[-] Node " + ip + " disconnected");
    }

    public static void main(String[] args) throws IOException {
        int port = args.length > 0 ? Integer.parseInt(args[0]) : 7000;
        try (ServerSocket server = new ServerSocket(port)) {
            log("[*] DSM memory manager running on port " + port);
            while (true) {
                Socket s = server.accept();
                new Thread(() -> serveNode(s)).start();
            }
        }
    }
}
