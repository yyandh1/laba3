package main

import (
    "fmt"
    "math"
    "math/rand"
    "time"
)

func getRandomNumber(min, max int) int {
    rand.Seed(time.Now().UnixNano())
    return rand.Intn(max-min+1) + min
}

func Eratosthenes(primeNums *[]int) {
    for i := 2; i < 500; i++ {
        *primeNums = append(*primeNums, i)
    }

    for i := 0; i <= int(math.Sqrt(float64(len(*primeNums)))); i++ {
        j := i + 1
        for j < len(*primeNums) {
            if (*primeNums)[j]%(*primeNums)[i] == 0 {
                *primeNums = append((*primeNums)[:j], (*primeNums)[j+1:]...)
            } else {
                j++
            }
        }
    }
}

func modPow(a, q, randNum int) int {
    result := 1
    for q > 0 {
        if q%2 == 1 {
            result = (result * a) % randNum
        }
        a = (a * a) % randNum
        q /= 2
    }
    return result
}

func MillerRazlozh(m, randNum1 int, primeNums []int) ([]int, []int) {
    mnozUnikPrime := []int{}
    primeMn := []int{}

    for _, prime := range primeNums {
        degree := 0
        if randNum1%prime == 0 {
            for randNum1%prime == 0 {
                randNum1 /= prime
                degree++
                primeMn = append(primeMn, prime)
            }
            mnozUnikPrime = append(mnozUnikPrime, prime)
            m *= int(math.Pow(float64(prime), float64(degree)))
        }
    }

    return mnozUnikPrime, primeMn
}

func Miller(randNum int, mnozUnikPrime []int, t int) bool {
    if randNum == 2 {
        return true
    }
    if randNum < 2 || randNum%2 == 0 {
        return false
    }
    var millerF1, millerF2 bool

    for j := 0; j < t; j++ {
        a := getRandomNumber(2, randNum-1)
        if modPow(a, randNum-1, randNum) == 1 {
            millerF1 = true
        }

        for _, prime := range mnozUnikPrime {
            if modPow(a, (randNum-1)/prime, randNum) == 1 {
                millerF2 = false
                break
            } else {
                millerF2 = true
            }
        }
        if millerF1 && millerF2 {
            return true
        }
    }
    return false
}

func NOD(a, b int) int {
    if b == 0 {
        return a
    }
    return NOD(b, a%b)
}

func PoklingtonRazlozh(randNum int, f, r *int, primeMn []int) {
    for i := len(primeMn) - 1; i >= 0; i-- {
        if *f <= int(math.Sqrt(float64(randNum)))-1 {
            *f *= primeMn[i]
        } else {
            *r *= primeMn[i]
        }
    }
}

func Poklington(randNum int, mnozUnikPrime []int, t int) bool {
    if randNum == 2 || randNum == 5 {
        return true
    }
    if randNum < 2 || randNum%2 == 0 {
        return false
    }

    for j := 0; j < t; j++ {
        a := getRandomNumber(2, randNum-1)
        if modPow(a, randNum-1, randNum) != 1 {
            continue
        }

        poklingF2 := true
        for _, prime := range mnozUnikPrime {
            if modPow(a, (randNum-1)/prime, randNum) == 1 {
                poklingF2 = false
                break
            }
        }
        if poklingF2 {
            return true
        }
    }
    return false
}

func GOST(t, q1 int) bool {
    var p int

    for {
        N1 := int(math.Ceil(math.Pow(2, float64(t-1)) / float64(q1)))
        N2 := int(math.Ceil(math.Pow(2, float64(t-1)) * 0 / float64(q1)))

        N := N1 + N2
        if int(N)%2 != 0 {
            N++
        }

        u := 0
        for math.Pow(2, float64(t)) >= (float64(N+u))*float64(q1)+1 {
            p = (N+u)*q1 + 1
            if modPow(2, p-1, p) == 1 && modPow(2, N+u, p) != 1 {
                return true
            }
            u += 2
        }
    }
    return false
}

func Euler(p int) int {
    result := p

    for i := 2; i*i <= p; i++ {
        if p%i == 0 {
            for p%i == 0 {
                p /= i
            }
            result -= result / i
        }
    }

    if p > 1 {
        result -= result / p
    }

    return result
}

func VerTest(randNum, t, R, F int) bool {
    if NOD(R, F) == 1 {
        verMiller := (float64(Euler(randNum-1)) / float64(randNum-1)) * float64(t)
        verPoklington := (float64(Euler(randNum)) / float64(randNum)) * float64(t)
        result := 1 - verMiller - verPoklington
        return result <= 0.1
    }

    verMiller := (float64(Euler(randNum-1)) / float64(randNum-1)) * float64(t)
    result := 1 - verMiller
    return result <= 0.1
}

func InPut(randNum int, testResult bool, k int) {
    if testResult && k <= 6 {
        fmt.Printf("%d\t\t+\t\t%d\n", randNum, k)
    } else {
        fmt.Printf("%d\t\t-\t\t%d\n", randNum, k)
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())

    var PrimeNums []int
    Eratosthenes(&PrimeNums)

    k := 0
    t := 4

    fmt.Println("Число\tВероятностный тест\tЧисло отвергнутых чисел")
    fmt.Println("-------------------------------------------------------")

    for i := 0; i < 10; i++ {
        RandNum := getRandomNumber(2, 500-2)
        RandNum1 := RandNum - 1
        m := 1
        MnozUnikPrime, PrimeMn := MillerRazlozh(m, RandNum1, PrimeNums)
        F := 1
        R := 1
        PoklingtonRazlozh(RandNum, &F, &R, PrimeMn)

        if !Miller(RandNum, MnozUnikPrime, t) || !Poklington(RandNum, MnozUnikPrime, t) {
            k++
            i--
            continue
        }

        //GOSTResult := GOST(t, q1)

        InPut(RandNum, VerTest(RandNum, t, R, F), k)

        if Miller(RandNum, MnozUnikPrime, t) && Poklington(RandNum, MnozUnikPrime, t) {
            k = 0
        }
    }
}

