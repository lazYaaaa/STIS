package ontology

type World struct {
	Name      string
	Valuation map[string][]string
}

type KripkeFrame struct {
	Worlds map[string]*World
	Access map[string][]string
}

func NewKripke() *KripkeFrame {
	return &KripkeFrame{Worlds: map[string]*World{}, Access: map[string][]string{}}
}

func (k *KripkeFrame) AddWorld(name string) *World {
	w, ok := k.Worlds[name]
	if !ok {
		w = &World{Name: name, Valuation: map[string][]string{}}
		k.Worlds[name] = w
	}
	return w
}

func (k *KripkeFrame) AddAccess(from, to string) {
	k.Access[from] = append(k.Access[from], to)
}

func (k *KripkeFrame) IsAccessible(from, to string) bool {
	visited := map[string]bool{}
	var dfs func(string) bool
	dfs = func(cur string) bool {
		if cur == to {
			return true
		}
		if visited[cur] {
			return false
		}
		visited[cur] = true
		for _, n := range k.Access[cur] {
			if dfs(n) {
				return true
			}
		}
		return false
	}
	return dfs(from)
}
