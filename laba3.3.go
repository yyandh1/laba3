package main

import (
    "fmt"
    "math"
)

func coffee(Tsr, Tc, HeatCoef float64, t int, Coffee *[]float64) {
    for i := 0; i <= t; i++ {
        *Coffee = append(*Coffee, Tc)
        Tc = Tc - HeatCoef*(Tc-Tsr)
    }
}

func aproxA(Coffee []float64) float64 {
    var ET, Et, ETt, ET2 float64
    len := len(Coffee)

    for i := 0; i < len; i++ {
        ET += Coffee[i]
        Et += float64(i)
        ETt += Coffee[i] * float64(i)
        ET2 += Coffee[i] * Coffee[i]
    }
    return (float64(len)*ETt - (Et * ET)) / ((float64(len) * ET2) - (ET * ET))
}

func aproxB(Coffee []float64, a float64) float64 {
    var ET, Et float64
    len := len(Coffee)

    for i := 0; i < len; i++ {
        ET += Coffee[i]
        Et += float64(i)
    }
    return (Et - a*ET) / float64(len)
}

func Correl(Coffee []float64) float64 {
    var sumTemp float64
    for _, T := range Coffee {
        sumTemp += T
    }

    len := len(Coffee)
    TMedium := sumTemp / float64(len)
    tMedium := (float64(len) - 1) * float64(len) / 2
    var sumNumbers, tSumSquare, TSumSquare float64

    for i := 0; i < len; i++ {
        sumNumbers += ((float64(i) - tMedium) * (Coffee[i] - TMedium))
        tSumSquare += ((float64(i) - tMedium) * (float64(i) - tMedium))
        TSumSquare += ((Coffee[i] - TMedium) * (Coffee[i] - TMedium))
    }
    return sumNumbers / math.Sqrt(TSumSquare*tSumSquare)
}

func main() {
    fmt.Println("Введите температуру воздуха и кофе, коэффициент охлаждения,")
    fmt.Println("максимальное время охлаждения в минутах")
    var Tsr, Tc, HeatCoef float64
    var t int
    fmt.Scan(&Tsr, &Tc, &HeatCoef, &t)

    var Coffee []float64
    coffee(Tsr, Tc, HeatCoef, t, &Coffee)

    fmt.Println("Время\tТемпература кофе")
    for i, temperature := range Coffee {
        fmt.Println(i, "\t", fmt.Sprintf("%.2f", temperature))
    }

    a := aproxA(Coffee)
    b := aproxB(Coffee, a)
    correl := Correl(Coffee)
    fmt.Printf("\nЛиния апроксимации: T = %s * t + %s\n", fmt.Sprintf("%.2f", a), fmt.Sprintf("%.2f", b))
    fmt.Printf("\nКоэффициент корреляции %s\n", fmt.Sprintf("%.3f", correl))
}

