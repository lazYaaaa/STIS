import edu.buffalo.sneps.JavaSnepsAPI;
import java.util.HashSet;

public class Lab2API {

    private static final String CONFIG = System.getenv("JAVA_API_CONFIG");

    private static void tellAll(JavaSnepsAPI api, String section, String[] commands) {
        System.out.println(section);
        for (String command : commands) {
            System.out.println("Telling: " + command);
            api.tell(command);
        }
    }

    private static void askAndPrint(JavaSnepsAPI api, String label, String query) {
        System.out.println("Asking " + label + " -> " + query);
        HashSet<String> answers = api.ask(query);
        if (answers == null || answers.isEmpty()) {
            System.out.println("  (no answers)");
            return;
        }
        for (String answer : answers) {
            System.out.println("  " + answer);
        }
    }

    public static void main(String[] args) {
        JavaSnepsAPI api = new JavaSnepsAPI(CONFIG, 5668);

        String[] commands = {
            "set-mode-3",
            "define-frame Isa (nil member class)",
            "define-frame Ako (nil class1 class2)",
            "define-frame Borrows (nil reader book)",
            "define-frame Recommends (nil librarian book)",
            "Isa(AdultReader, Reader).",
            "Isa(ChildReader, Reader).",
            "Isa(Reader, Person).",
            "Isa(Librarian, Person).",
            "Isa(Book, Item).",
            "Isa(alice, AdultReader).",
            "Isa(bob, ChildReader).",
            "Isa(elena, Librarian).",
            "Isa(book1, Book).",
            "Borrows(alice, book1).",
            "Borrows(bob, book1).",
            "Recommends(elena, book1)."
        };

        tellAll(api, "Lab2: Library", commands);
        askAndPrint(api, "Lab2 People", "Isa(?x, Person)");
        askAndPrint(api, "Lab2 Readers", "Isa(?x, Reader)");
        askAndPrint(api, "Lab2 Borrows alice", "Borrows(alice, book1)");
        askAndPrint(api, "Lab2 Recommends elena", "Recommends(elena, book1)");

        api.endLispConnection();
    }
}