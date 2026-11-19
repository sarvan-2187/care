// Exercise 2: Peer-to-Peer File Listing
// Every peer is a server (shares its folder's file list) AND a client (asks other peers).
// Compile: javac Peer.java     Run on every computer: java Peer <shared_folder> [port]
// Then type:  list <peer_ip> [port]   |   mylist   |   exit
import java.io.*;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class Peer {
    static File sharedDir;
    static int port;
    static final SimpleDateFormat FMT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    static String localIp() {
        try (DatagramSocket s = new DatagramSocket()) {
            s.connect(InetAddress.getByName("8.8.8.8"), 80);
            return s.getLocalAddress().getHostAddress();
        } catch (IOException e) {
            return "127.0.0.1";
        }
    }

    // Reads the REAL folder contents at the moment of the request (no dummy data)
    static List<File> localFiles() {
        File[] all = sharedDir.listFiles();
        List<File> files = new ArrayList<>();
        if (all != null)
            for (File f : all) if (f.isFile()) files.add(f);
        files.sort(Comparator.comparing(File::getName));
        return files;
    }

    // ---------------- server side of the peer ----------------
    static void serve() {
        try (ServerSocket server = new ServerSocket(port)) {
            while (true) {
                Socket s = server.accept();
                new Thread(() -> handle(s)).start();   // one thread per requesting peer
            }
        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }

    static void handle(Socket s) {
        try (s;
             BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
             PrintWriter out = new PrintWriter(s.getOutputStream(), true)) {
            if ("LIST".equals(in.readLine())) {
                List<File> files = localFiles();
                out.println("HOST|" + localIp() + "|" + sharedDir.getAbsolutePath());
                for (File f : files)
                    out.println(f.getName() + "|" + f.length() + "|" + FMT.format(new Date(f.lastModified())));
                out.println("END");
                System.out.print("\n[server] Sent list of " + files.size() + " file(s) to "
                        + s.getInetAddress().getHostAddress() + "\npeer> ");
            } else {
                out.println("ERROR|unknown command");
            }
        } catch (IOException ignored) { }
    }

    // ---------------- client side of the peer ----------------
    static void requestList(String ip, int p) throws IOException {
        try (Socket s = new Socket()) {
            s.connect(new InetSocketAddress(ip, p), 5000);
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            PrintWriter out = new PrintWriter(s.getOutputStream(), true);
            out.println("LIST");

            String[] head = in.readLine().split("\\|");
            System.out.println("\nFiles shared by peer " + head[1] + " (folder: " + head[2] + ")");
            System.out.printf("%-4s%-30s%14s  %s%n", "No", "File name", "Size (bytes)", "Last modified");
            System.out.println("-".repeat(70));
            int n = 0;
            String line;
            while ((line = in.readLine()) != null && !line.equals("END")) {
                String[] f = line.split("\\|");
                System.out.printf("%-4d%-30s%14s  %s%n", ++n, f[0], f[1], f[2]);
            }
            System.out.println("Total: " + n + " file(s)\n");
        }
    }

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Usage: java Peer <shared_folder> [port]");
            return;
        }
        sharedDir = new File(args[0]).getAbsoluteFile();
        port = args.length > 1 ? Integer.parseInt(args[1]) : 6000;
        if (!sharedDir.isDirectory()) {
            System.out.println("Folder not found: " + sharedDir);
            return;
        }

        Thread server = new Thread(Peer::serve);
        server.setDaemon(true);
        server.start();

        System.out.println("[*] Peer IP      : " + localIp());
        System.out.println("[*] Port         : " + port);
        System.out.println("[*] Shared folder: " + sharedDir);
        System.out.println("Commands: list <peer_ip> [port] | mylist | exit");

        BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
        String line;
        System.out.print("peer> ");
        while ((line = keyboard.readLine()) != null) {
            String[] cmd = line.trim().split("\\s+");
            if (cmd[0].equals("exit")) break;
            if (cmd[0].equals("mylist")) {
                for (File f : localFiles())
                    System.out.println("  " + f.getName() + "  (" + f.length() + " bytes)");
            } else if (cmd[0].equals("list") && cmd.length >= 2) {
                int p = cmd.length > 2 ? Integer.parseInt(cmd[2]) : port;
                try {
                    requestList(cmd[1], p);
                } catch (IOException e) {
                    System.out.println("Could not reach " + cmd[1] + ":" + p + " -> " + e.getMessage());
                }
            } else if (!cmd[0].isEmpty()) {
                System.out.println("Commands: list <peer_ip> [port] | mylist | exit");
            }
            System.out.print("peer> ");
        }
        System.out.println("[*] Peer stopped.");
        System.exit(0);
    }
}
