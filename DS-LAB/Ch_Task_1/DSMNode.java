// Challenging Task 1: Distributed Shared Memory (DSM) - Node
// Every computer runs this to access the shared memory.
// Compile: javac DSMNode.java     Run: java DSMNode <dsm_server_ip> [port]
//
// Commands:
//   create <name> <value> | read <name> | write <name> <value>
//   incr <name> [n]   (LOCK -> READ -> value+n -> WRITE -> UNLOCK) | exit
import java.io.*;
import java.net.*;

public class DSMNode {
    private final Socket socket;
    private final BufferedReader in;
    private final PrintWriter out;

    DSMNode(String ip, int port) throws IOException {
        socket = new Socket(ip, port);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);
    }

    // Sends one request; returns reply fields {"OK", value, version, lastWriter}
    String[] call(String request) throws IOException {
        out.println(request);
        String reply = in.readLine();
        if (reply == null) throw new IOException("DSM server closed the connection");
        if (reply.startsWith("ERR")) throw new IllegalStateException(reply.substring(4));
        return reply.split(" ");
    }

    String[] create(String n, int v) throws IOException { return call("CREATE " + n + " " + v); }
    String[] read(String n) throws IOException          { return call("READ " + n); }
    String[] write(String n, int v) throws IOException  { return call("WRITE " + n + " " + v); }
    void lock(String n) throws IOException              { call("LOCK " + n); }
    void unlock(String n) throws IOException            { call("UNLOCK " + n); }

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Usage: java DSMNode <dsm_server_ip> [port]");
            return;
        }
        int port = args.length > 1 ? Integer.parseInt(args[1]) : 7000;
        DSMNode dsm = new DSMNode(args[0], port);
        System.out.println("[*] This node's IP : " + dsm.socket.getLocalAddress().getHostAddress());
        System.out.println("[*] DSM server     : " + args[0] + ":" + port);
        System.out.println("Commands: create <n> <v> | read <n> | write <n> <v> | incr <n> [k] | exit");

        BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
        String line;
        System.out.print("dsm> ");
        while ((line = keyboard.readLine()) != null) {
            String[] c = line.trim().split("\\s+");
            try {
                if (c[0].equals("exit")) break;
                switch (c[0]) {
                    case "create": {
                        String[] r = dsm.create(c[1], Integer.parseInt(c[2]));
                        System.out.println("Created shared variable " + c[1] + " = " + r[1]);
                        break;
                    }
                    case "read": {
                        String[] r = dsm.read(c[1]);
                        System.out.println(c[1] + " = " + r[1] + "  (version " + r[2]
                                + ", last written by " + r[3] + ")");
                        break;
                    }
                    case "write": {
                        String[] r = dsm.write(c[1], Integer.parseInt(c[2]));
                        System.out.println("Wrote " + c[1] + " = " + r[1] + "  (version " + r[2] + ")");
                        break;
                    }
                    case "incr": {
                        int step = c.length > 2 ? Integer.parseInt(c[2]) : 1;
                        dsm.lock(c[1]);
                        try {
                            int old = Integer.parseInt(dsm.read(c[1])[1]);
                            System.out.println("Read  " + c[1] + " = " + old);
                            int now = old + step;
                            System.out.println("Modify " + old + " + " + step + " = " + now);
                            String[] r = dsm.write(c[1], now);
                            System.out.println("Wrote " + c[1] + " = " + now
                                    + " back to shared memory (version " + r[2] + ")");
                        } finally {
                            dsm.unlock(c[1]);
                        }
                        break;
                    }
                    case "":
                        break;
                    default:
                        System.out.println("Unknown command");
                }
            } catch (ArrayIndexOutOfBoundsException | NumberFormatException e) {
                System.out.println("Bad arguments");
            } catch (IllegalStateException e) {
                System.out.println("DSM error: " + e.getMessage());
            }
            System.out.print("dsm> ");
        }
        System.out.println("[*] Node stopped.");
        System.exit(0);
    }
}
