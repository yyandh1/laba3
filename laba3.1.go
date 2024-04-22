package main

import (
    "fmt"
    "math"
)

func func1(x float64) float64 {
    y := x/3 + 0.67
    return y
}

func func2(x float64) float64 {
    y := math.Tan(x/2)
    return y
}

func func3(x float64) float64 {
    y := (0.5 * x) - 1.5
    return y
}

func main() {
    fmt.Println("Funktionswert")
    fmt.Println("X\tY")

    dx := 0.5
    for x := -5.0; x <= 5; x += dx {
        if x >= -5 && x <= -2 {
            fmt.Printf("%.2f  %.2f\n", x, func1(x))
        }
        if x >= -2 && x <= 2 {
            fmt.Printf("%.2f  %.2f\n", x, func2(x))
        }
        if x >= 2 && x <= 5 {
            fmt.Printf("%.2f  %.2f\n", x, func3(x))
        }
    }
}

