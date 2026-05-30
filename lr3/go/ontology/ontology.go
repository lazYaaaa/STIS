package ontology

type Ontology struct {
	ByName       map[string]*Concept
	Instances    map[string][]*Concept // instance name -> declared concepts
	RelationType map[string]*Concept   // treat relation types as concepts for rel-ISA
}

func NewOntology() *Ontology {
	return &Ontology{ByName: map[string]*Concept{}, Instances: map[string][]*Concept{}, RelationType: map[string]*Concept{}}
}

func (o *Ontology) AddConcept(name string, parentNames ...string) *Concept {
	c, ok := o.ByName[name]
	if !ok {
		c = &Concept{Name: name}
		o.ByName[name] = c
	}
	for _, pn := range parentNames {
		p, ok := o.ByName[pn]
		if !ok {
			p = &Concept{Name: pn}
			o.ByName[pn] = p
		}
		c.Parents = append(c.Parents, p)
	}
	return c
}

func (o *Ontology) AddInstance(instName, conceptName string) {
	if c, ok := o.ByName[conceptName]; ok {
		o.Instances[instName] = append(o.Instances[instName], c)
	}
}

// IsSubType checks transitive ISA: returns true and the path from sub->...->sup
func (o *Ontology) IsSubType(sub, sup string) (bool, []string) {
	start, ok1 := o.ByName[sub]
	goal, ok2 := o.ByName[sup]
	if !ok1 || !ok2 {
		return false, nil
	}
	visited := map[string]bool{}
	var path []string
	var dfs func(*Concept) bool
	dfs = func(c *Concept) bool {
		if c == nil || visited[c.Name] {
			return false
		}
		visited[c.Name] = true
		path = append(path, c.Name)
		if c == goal {
			return true
		}
		for _, p := range c.Parents {
			if dfs(p) {
				return true
			}
		}
		path = path[:len(path)-1]
		return false
	}
	if dfs(start) {
		return true, path
	}
	return false, nil
}

func (o *Ontology) InstanceOfTrans(instance, target string) bool {
	decls, ok := o.Instances[instance]
	if !ok {
		return false
	}
	for _, c := range decls {
		if c.Name == target {
			return true
		}
		if ok, _ := o.IsSubType(c.Name, target); ok {
			return true
		}
	}
	return false
}

// Relation types: treat them as concepts to reuse IsSubType
func (o *Ontology) AddRelationType(name string, parentNames ...string) *Concept {
	r, ok := o.RelationType[name]
	if !ok {
		r = &Concept{Name: name}
		o.RelationType[name] = r
	}
	for _, pn := range parentNames {
		p, ok := o.RelationType[pn]
		if !ok {
			p = &Concept{Name: pn}
			o.RelationType[pn] = p
		}
		r.Parents = append(r.Parents, p)
	}
	return r
}

func (o *Ontology) IsRelSubType(sub, sup string) bool {
	s, ok1 := o.RelationType[sub]
	g, ok2 := o.RelationType[sup]
	if !ok1 || !ok2 {
		return false
	}
	visited := map[string]bool{}
	var dfs func(*Concept) bool
	dfs = func(c *Concept) bool {
		if c == nil || visited[c.Name] {
			return false
		}
		visited[c.Name] = true
		if c == g {
			return true
		}
		for _, p := range c.Parents {
			if dfs(p) {
				return true
			}
		}
		return false
	}
	return dfs(s)
}
