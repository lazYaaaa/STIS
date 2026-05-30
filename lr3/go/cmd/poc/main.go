package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)

	for {
		s := chooseScenario(in)
		if s == nil {
			return
		}
		scenario := s

	innerLoop:
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
				break innerLoop
			}
		}
	}
}
