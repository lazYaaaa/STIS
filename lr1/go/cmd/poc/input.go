package main

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"
)

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
