import edu.buffalo.sneps.JavaSnepsAPI;
import java.util.HashSet;

public class Lab3API {

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
            "define-frame Takes (nil student course)",
            "define-frame Teaches (nil professor course)",
            "Isa(Undergraduate, Student).",
            "Isa(Graduate, Student).",
            "Isa(Student, Person).",
            "Isa(Professor, Person).",
            "Isa(Course, Entity).",
            "Isa(alice, Undergraduate).",
            "Isa(bob, Graduate).",
            "Isa(dr_smith, Professor).",
            "Isa(cs101, Course).",
            "Takes(alice, cs101).",
            "Takes(bob, cs101).",
            "Teaches(dr_smith, cs101)."
        };

        tellAll(api, "Lab3: University", commands);
        askAndPrint(api, "Lab3 People", "Isa(?x, Person)");
        askAndPrint(api, "Lab3 Student", "Isa(?x, Student)");
        askAndPrint(api, "Lab3 Takes alice", "Takes(alice, cs101)");
        askAndPrint(api, "Lab3 Teaches dr_smith", "Teaches(dr_smith, cs101)");

        api.endLispConnection();
    }
}