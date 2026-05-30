package main

import (
	"bufio"
	"fmt"
	"strings"

	"github.com/lazYaaaa/STIS/lr3/go/scenarios"
)

func chooseScenario(in *bufio.Reader) *scenarios.Scenario {
    fmt.Println("Choose scenario:")
    fmt.Println("1) university")
    fmt.Println("2) library")
    fmt.Println("0) exit")

    switch readChoice(in, 0, 2) {
    case 1:
        s := scenarios.BuildUniversity()
        return &s
    case 2:
        s := scenarios.BuildLibrary()
        return &s
    default:
        return nil
    }
}

func queryInstanceOf(in *bufio.Reader, scenario *scenarios.Scenario) {
    fmt.Println("Choose instance:")
    instance := chooseFromList(in, scenario.Instances)
    if instance == "" {
        return
    }

    fmt.Println("Choose concept:")
    concept := chooseFromList(in, scenario.Concepts)
    if concept == "" {
        return
    }

    result := scenario.Ontology.InstanceOfTrans(instance, concept)
    fmt.Printf("instance-of(%s, %s) = %v\n", instance, concept, result)
}

func queryISA(in *bufio.Reader, scenario *scenarios.Scenario) {
    fmt.Println("Choose subtype:")
    sub := chooseFromList(in, scenario.Concepts)
    if sub == "" {
        return
    }

    fmt.Println("Choose supertype:")
    sup := chooseFromList(in, scenario.Concepts)
    if sup == "" {
        return
    }

    ok, path := scenario.Ontology.IsSubType(sub, sup)
    fmt.Printf("ISA(%s, %s) = %v\n", sub, sup, ok)
    if ok && len(path) > 0 {
        fmt.Printf("path: %s\n", strings.Join(path, " -> "))
    }
}

func queryRelISA(in *bufio.Reader, scenario *scenarios.Scenario) {
    fmt.Println("Choose relation type:")
    sub := chooseFromList(in, scenario.RelationType)
    if sub == "" {
        return
    }

    fmt.Println("Choose super relation type:")
    sup := chooseFromList(in, scenario.RelationType)
    if sup == "" {
        return
    }

    fmt.Printf("rel-ISA(%s, %s) = %v\n", sub, sup, scenario.Ontology.IsRelSubType(sub, sup))
}
