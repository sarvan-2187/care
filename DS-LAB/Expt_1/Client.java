// Exercise 1: Client-Server Communication (bidirectional chat) - CLIENT
// Compile: javac Client.java      Run on Computer 2: java Client <server_ip> [port]
import java.io.*;
import java.net.*;

public class Client {
    static volatile boolean closing = false;   // true once WE end the chat
    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Usage: java Client <server_ip> [port]");
            return;
        }
        String serverIp = args[0];
        int port = args.length > 1 ? Integer.parseInt(args[1]) : 5000;

        Socket socket = new Socket(serverIp, port);
        System.out.println("[*] Client IP  : " + socket.getLocalAddress().getHostAddress());
        System.out.println("[+] Connected to server " + serverIp + ":" + port);
        System.out.println("Type a message and press Enter ('bye' to quit).");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        Thread receiver = new Thread(() -> {
            try {
                String msg;
                while ((msg = in.readLine()) != null) {
                    System.out.print("\nServer (" + serverIp + "): " + msg + "\nClient> ");
                    if (msg.equalsIgnoreCase("bye")) break;
                }
            } catch (IOException ignored) { }
            if (!closing) System.out.println("\n[!] Server disconnected.");
            System.exit(0);
        });
        receiver.setDaemon(true);
        receiver.start();

        BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
        String line;
        System.out.print("Client> ");
        while ((line = keyboard.readLine()) != null) {
            out.println(line);
            if (line.equalsIgnoreCase("bye")) { closing = true; break; }
            System.out.print("Client> ");
        }
        socket.close();
        System.out.println("[*] Client closed.");
    }
}
