package ontology

type Concept struct {
	Name    string
	Parents []*Concept
}
