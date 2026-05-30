package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"example.com/lr3go/scenarios"
)

func main() {
	in := bufio.NewReader(os.Stdin)

	for {
		s := chooseScenario(in)
		if s == nil {
			return
		}
		scenario := s

		for {
			fmt.Println()
			fmt.Printf("Scenario: %s\n", scenario.Name)
			fmt.Println("1) instance-of")
			fmt.Println("2) ISA")
			fmt.Println("3) rel-ISA")
			fmt.Println("4) change scenario")
			fmt.Println("0) exit")

			choice := readChoice(in, 0, 4)
			switch choice {
			case 0:
				return
			case 1:
				queryInstanceOf(in, scenario)
			case 2:
				queryISA(in, scenario)
			case 3:
				queryRelISA(in, scenario)
			case 4:
				goto nextScenario
			}
		}
	nextScenario:
	}
}

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

func chooseFromList(in *bufio.Reader, items []string) string {
	for i, item := range items {
		fmt.Printf("%d) %s\n", i+1, item)
	}
	fmt.Println("0) cancel")

	choice := readChoice(in, 0, len(items))
	if choice == 0 {
		return ""
	}
	return items[choice-1]
}

func readChoice(in *bufio.Reader, min, max int) int {
	for {
		fmt.Print("> ")
		line, _ := in.ReadString('\n')
		line = strings.TrimSpace(line)
		value, err := strconv.Atoi(line)
		if err == nil && value >= min && value <= max {
			return value
		}
		fmt.Printf("enter a number from %d to %d\n", min, max)
	}
}
