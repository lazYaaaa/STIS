package ontology

import (
	"testing"
)

func TestUniversityInstanceOf(t *testing.T) {
	o := NewOntology()
	o.AddConcept("Person")
	o.AddConcept("Student", "Person")
	o.AddConcept("Undergraduate", "Student")
	o.AddConcept("Graduate", "Student")
	o.AddConcept("Professor", "Person")
	o.AddConcept("Course")

	o.AddInstance("alice", "Undergraduate")
	o.AddInstance("bob", "Graduate")
	o.AddInstance("dr_smith", "Professor")

	if !o.InstanceOfTrans("alice", "Person") {
		t.Fatalf("expected alice to be instance-of Person via transitive ISA")
	}
	if ok, path := o.IsSubType("Undergraduate", "Person"); !ok {
		t.Fatalf("expected Undergraduate <= Person")
	} else if len(path) < 2 {
		t.Fatalf("expected path of length >=2, got %v", path)
	}
}

func TestLibraryInstanceOf(t *testing.T) {
	o := NewOntology()
	o.AddConcept("Person")
	o.AddConcept("Reader", "Person")
	o.AddConcept("AdultReader", "Reader")
	o.AddConcept("ChildReader", "Reader")
	o.AddConcept("Librarian", "Person")
	o.AddConcept("Item")
	o.AddConcept("Book", "Item")

	o.AddInstance("book1", "Book")
	o.AddInstance("alice", "AdultReader")
	o.AddInstance("bob", "ChildReader")
	o.AddInstance("elena", "Librarian")

	if !o.InstanceOfTrans("book1", "Item") {
		t.Fatalf("expected book1 instance-of Item")
	}

	o.AddRelationType("borrows")
	o.AddRelationType("recommends")
	o.AddRelationType("borrows_reader", "borrows")

	if !o.IsRelSubType("borrows_reader", "borrows") {
		t.Fatalf("expected borrows_reader <= borrows")
	}
}

func TestKripkeAccessibility(t *testing.T) {
	k := NewKripke()
	k.AddWorld("w1")
	k.AddWorld("w2")
	k.AddWorld("w3")
	k.AddAccess("w1", "w2")
	k.AddAccess("w2", "w3")

	if !k.IsAccessible("w1", "w3") {
		t.Fatalf("expected w1 to reach w3 through w2")
	}
	if k.IsAccessible("w3", "w1") {
		t.Fatalf("did not expect w3 to reach w1")
	}
}
