// Exercise 1: Client-Server Communication (bidirectional chat) - SERVER
// Compile: javac Server.java      Run on Computer 1: java Server [port]
import java.io.*;
import java.net.*;

public class Server {
    static volatile boolean closing = false;   // true once WE end the chat

    // Returns the IP address this machine uses on the LAN
    static String localIp() {
        try (DatagramSocket s = new DatagramSocket()) {
            s.connect(InetAddress.getByName("8.8.8.8"), 80); // no packet is sent
            return s.getLocalAddress().getHostAddress();
        } catch (IOException e) {
            return "127.0.0.1";
        }
    }

    public static void main(String[] args) throws IOException {
        int port = args.length > 0 ? Integer.parseInt(args[0]) : 5000;

        try (ServerSocket server = new ServerSocket(port)) {   // listens on all interfaces
            System.out.println("[*] Server IP  : " + localIp());
            System.out.println("[*] Listening on port " + port + " ... waiting for a client");

            Socket socket = server.accept();
            String peer = socket.getInetAddress().getHostAddress();
            System.out.println("[+] Connected to client " + peer + ":" + socket.getPort());
            System.out.println("Type a message and press Enter ('bye' to quit).");

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Receiving thread: lets messages arrive while we are typing (full duplex)
            Thread receiver = new Thread(() -> {
                try {
                    String msg;
                    while ((msg = in.readLine()) != null) {
                        System.out.print("\nClient (" + peer + "): " + msg + "\nServer> ");
                        if (msg.equalsIgnoreCase("bye")) break;
                    }
                } catch (IOException ignored) { }
                if (!closing) System.out.println("\n[!] Client disconnected.");
                System.exit(0);
            });
            receiver.setDaemon(true);
            receiver.start();

            BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
            String line;
            System.out.print("Server> ");
            while ((line = keyboard.readLine()) != null) {
                out.println(line);
                if (line.equalsIgnoreCase("bye")) { closing = true; break; }
                System.out.print("Server> ");
            }
            socket.close();
            System.out.println("[*] Server closed.");
        }
    }
}
