Go POC for ontology / Kripke frames used in LR2/LR3.

Structure:
- `ontology/` - concepts, ontology, Kripke frame
- `cmd/poc/` - interactive CLI with scenario selection and menu-driven checks

Run tests:

```bash
cd lr3/go
go test ./...
```

Run CLI:

```bash
cd lr3/go
go run ./cmd/poc
```

The CLI lets you choose a scenario, then pick `instance-of`, `ISA`, or `rel-ISA` checks from menus.
