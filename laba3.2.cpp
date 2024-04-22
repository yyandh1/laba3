#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <map>
using namespace std;

int getRandomNumber(int min, int max) {  //генерация случайного числа в заданном диапазоне
    return rand() % (max - min + 1) + min;
}

void Eratosthenes(vector<int>& PrimeNums) {  //решето Эратосфена
    for(int i = 2; i < 500; i++){ // Заполняем вектор числами от 2 до 500, потому что 1 и 0 - не простые
        PrimeNums.push_back(i);
    }

    for (int i = 0; i <= sqrt(PrimeNums.size()); i++) {
        int j = i + 1;
        while (j < PrimeNums.size()) {
            if (PrimeNums[j] % PrimeNums[i] == 0) {
                for (int k = j; k < PrimeNums.size() - 1; k++) { //если чисто составное
                    PrimeNums[k] = PrimeNums[k + 1]; //сдвигаем влево
                }
                PrimeNums.pop_back(); //и удаляем последний элемент
            } else {
                j++;                  //если простое, идем дальше
            }
        }
    }
}

int modPow(int a, int q, int RandNum) {  // Функция для возведения в степень по модулю
    int result = 1; // a - основание q - степень 
    while (q > 0) {
        if (q % 2 == 1) {
            result = (result * a) % RandNum;
        }
        a = (a * a) % RandNum;
        q /= 2;
    }
    return result;
}

int MillerRazlozh(int m, int RandNum1, const vector<int>& PrimeNums, vector<int>& MnozUnikPrime, vector<int>& PrimeMn) {
    for (size_t i = 0; i < PrimeNums.size(); i++) { // проверям для каждого простого числа является ли 
        int degree = 0; // оно делителем для RandNum1
        if (RandNum1 % PrimeNums[i] == 0) { // если является делителем, то простой множитель
            while (RandNum1 % PrimeNums[i] == 0) { 
                RandNum1 /= PrimeNums[i];
                degree += 1;
                PrimeMn.push_back(PrimeNums[i]); 
            }
            MnozUnikPrime.push_back(PrimeNums[i]); // добавляется в вектор множества уникальных делителей
            m *= pow(PrimeNums[i], degree);
        }
    }
    return m/2; // возвращаем именно m/2 для получения d
}

bool Miller(int RandNum, const vector<int>& MnozUnikPrime, int t) {
    if (RandNum == 2) { // если число равно двум, оно простое
        return true;
    }
    if (RandNum < 2 || RandNum % 2 == 0) { // если число меньше двух или четное, оно составное
        return false;
    }
    bool MillerF1 = false; // для проверки теоремы ферма
    bool MillerF2 = false;

    for (int j=0; j<t; j++){
        int a = getRandomNumber(2,RandNum-1); //случайное число a в диапазоне от 2 до RandNum-1
        if (modPow(a,RandNum-1,RandNum) == 1) {//малая теорема ферма
            MillerF1 = true;
        }

        for (size_t i = 0; i < MnozUnikPrime.size(); i++) {
            if (modPow(a, (RandNum-1)/MnozUnikPrime[i], RandNum) == 1) { // а возводим в степень и проверяем его по свойству теста
                MillerF2 = false; // если остаток = 1, то число считается составным
                break;
            } else {
                MillerF2 = true; // если остаток отличен от 1, число считается простым
            }
        }
        if (MillerF1==true && MillerF2==true) { // если число удовлетворяет двум условиям, оно простое
            return true;
        }
    }
    return false;
}

int NOD(int a, int b) { // ищем наибольший общий делитель
    if (b == 0) {
        return a;
    }
    return NOD(b, a % b);
}

void PoklingtonRazlozh(int RandNum, int& F, int& R, const vector<int>& PrimeMn) {// Раскладываем на простые числа используя
    for (size_t i = PrimeMn.size() - 1; i + 1 > 0; i--) { // разложение для миллера. Тут проходимся начиная с последнего
        if (F <= sqrt(RandNum) - 1) { // если F меньше или равно "", то F умножается на простой множитель
            F *= PrimeMn[i];
        } else { // в противном случае умножаем R на простой множитель
            R *= PrimeMn[i]; // цель разложения в том чтобы как можно ближе подойти к корню из рандомного числа
        }
    }
}

bool Poklington(int RandNum, const vector<int>& MnozUnikPrime, int t) {
    if (RandNum == 2 || RandNum == 5) {// если число равно 2 или 5, оно простое
        return true;
    }
    if (RandNum < 2 || RandNum % 2 == 0) { // если число меньше двух или четное, оно составное
        return false;
    }
    bool PoklingF1 = false;
    bool PoklingF2 = false;
    for (int j=0; j < t; j++) {
        int a = getRandomNumber(2,RandNum-1);
        if (modPow(a,RandNum-1,RandNum) != 1) { // по теореме ферма для простого числа остаток должен быть 1
            PoklingF1 = false;
        } else {
            PoklingF1 = true;
        }
        for (size_t i = 0; i < MnozUnikPrime.size(); i++) { // условие теста Поклингтона
            if (modPow(a, (RandNum-1)/MnozUnikPrime[i], RandNum) == 1) { // не должно давать остаток 1 
                PoklingF2 = false; // при делении на RandNum для всех простых делителей
                break;
            } else {
                PoklingF2 = true;
            }
        }
        if (PoklingF1 == true && PoklingF2 == true) { // если ни разу флаг не менялся, то число простое
            return true;
        }
    }
    return false;
}

bool GOST(int t, int q1) {
    int p = 0;

    while (true) {
        int N1 = ceil(pow(2, t - 1) / q1); // создаем два числа, если число дробное, то
        int N2 = ceil(pow(2, t - 1)*0/ (q1)); // округляем в большую сторону

        double N = N1 + N2;// если число оказалось нечетным, то
        if (static_cast<int>(round(N)) % 2 != 0) { // мы добавим 1 и сделаем его четным
            N++;
        }

        for (int u = 0; pow(2, t) >= (N + u) * q1 + 1; u += 2) { // ищем простое число p
            p = (N + u) * q1 + 1; // если р - простое число, а не делится на р, то 
            // а**(р-1) должно дать остаток 1, также проверяем, чтобы р не было делителем 2**(N + u)
            if ((modPow(2, p - 1, p) == 1) && (modPow(2, N + u, p) != 1)) {
                return true;
            }
        }
    }
    return false;
}

int Eiler(int p) { // определяем количество взаимно простых чисел для p 
    int result = p;
    for (int i = 2; i * i <= p; i++) { //проходимся до корня из числа
        if (p % i == 0) { //если число разделилось на i, то мы уменьшаем р на i так как все числа,
            while (p % i == 0){ // которые делятся на i не являются взаимно простыми с p
                p /= i;
            }
            result -= result / i; // из результата вычитаем количество чисел result/i
        }
    }
    if (p > 1){ // если п - простое число, которое не разделилось, то оно простое и результатом
        result -= result / p; // функции будет р-1
    }
        
    return result;
}

bool VerTest(int RandNum, int t, int R, int F) {
    if (NOD(R,F) == 1) { // если число простое, то вычисляем вероятность ошибки тестов
    /*вычисляем функцию эйлера и делим на RandNum-1 для оценки теста миллера и погклингтона
    умножаем на t так как это количество итераций тестов
    из конечного результата вычитаем вероятности*/
        double verMiller = (static_cast<double>(Eiler(RandNum-1))/static_cast<double>(RandNum-1)) * t;
        double verPoklington = (static_cast<double>(Eiler(RandNum))/static_cast<double>(RandNum)) * t;
        double result = 1 - verMiller - verPoklington;
        return (result <= 0.1);
    } else {
        /*Если нод не равен 1, то поклингтон бесполезен*/
        double verMiller = (static_cast<double>(Eiler(RandNum-1))/static_cast<double>(RandNum-1)) * t;
        double result = 1 - verMiller;
        return (result <= 0.1);
    }
}

void InPut(int RandNum, bool testResult, int k) { //выводим результаты
    if (testResult && k <= 6) {
        cout << RandNum << " \t\t" << "+" << " \t\t" << k << endl;
    } else {
        cout << RandNum << " \t\t" << "-" << " \t\t" << k << endl;
    }
}

int main() {
    system("chcp 65001");
    srand(time(0));
    vector<int> PrimeNums;
    Eratosthenes(PrimeNums);

    int t1 = 10;
    int k = 0;
    int t = 4;
    int q1 = 3;

    cout << "Число\tВероятностный тест\tЧисло отвергнутых чисел" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < 10; i++) {
        vector<int> MnozUnikPrime;
        vector<int> PrimeMn;
        int RandNum = getRandomNumber(2, 500 - 2);
        int RandNum1 = RandNum - 1;
        int m = 1;
        m = MillerRazlozh(m, RandNum1, PrimeNums, MnozUnikPrime, PrimeMn); // число, которое разложили на простые
        int F = 1;
        int R = 1;
        PoklingtonRazlozh(RandNum, F, R, PrimeMn);

        if (m*2+1!=RandNum||!Miller(RandNum, MnozUnikPrime, t) || !Poklington(RandNum, MnozUnikPrime, t)||R*F+1!=RandNum) {
            k++;
            i--;
            continue;
        }

        bool GOSTResult = GOST(t, q1);

        InPut(RandNum, VerTest(RandNum, t, R, F), k);

        if (Miller(RandNum, MnozUnikPrime, t) && Poklington(RandNum, MnozUnikPrime, t)) {
            k=0;
        }
    }
    return 0;
}