package scenarios

import ont "example.com/lr3go/ontology"

type Scenario struct {
    Name         string
    Ontology     *ont.Ontology
    Concepts     []string
    Instances    []string
    RelationType []string
}

func BuildUniversity() Scenario {
    o := ont.NewOntology()
    o.AddConcept("Person")
    o.AddConcept("Student", "Person")
    o.AddConcept("Undergraduate", "Student")
    o.AddConcept("Graduate", "Student")
    o.AddConcept("Professor", "Person")
    o.AddConcept("Course")

    o.AddInstance("alice", "Undergraduate")
    o.AddInstance("bob", "Graduate")
    o.AddInstance("dr_smith", "Professor")
    o.AddInstance("cs101", "Course")

    o.AddRelationType("takes")
    o.AddRelationType("teaches")

    return Scenario{
        Name:         "University",
        Ontology:     o,
        Concepts:     []string{"Person", "Student", "Undergraduate", "Graduate", "Professor", "Course"},
        Instances:    []string{"alice", "bob", "dr_smith", "cs101"},
        RelationType: []string{"takes", "teaches"},
    }
}

func BuildLibrary() Scenario {
    o := ont.NewOntology()
    o.AddConcept("Person")
    o.AddConcept("Reader", "Person")
    o.AddConcept("AdultReader", "Reader")
    o.AddConcept("ChildReader", "Reader")
    o.AddConcept("Librarian", "Person")
    o.AddConcept("Item")
    o.AddConcept("Book", "Item")

    o.AddInstance("alice", "AdultReader")
    o.AddInstance("bob", "ChildReader")
    o.AddInstance("elena", "Librarian")
    o.AddInstance("book1", "Book")

    o.AddRelationType("borrows")
    o.AddRelationType("recommends")
    o.AddRelationType("borrows_reader", "borrows")
    o.AddRelationType("recommends_librarian", "recommends")

    return Scenario{
        Name:         "Library",
        Ontology:     o,
        Concepts:     []string{"Person", "Reader", "AdultReader", "ChildReader", "Librarian", "Item", "Book"},
        Instances:    []string{"alice", "bob", "elena", "book1"},
        RelationType: []string{"borrows", "recommends", "borrows_reader", "recommends_librarian"},
    }
}
