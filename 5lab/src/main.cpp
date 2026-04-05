#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

std::string to_scientific_string(double value) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(0) << value;
    std::string s = oss.str();

    size_t e_pos = s.find('e');
    if (e_pos != std::string::npos && s[e_pos + 2] == '+') {
        s.erase(e_pos + 2, 1);
    }
    return s;
}

double mu_l(int l, int N, int m, double mu) {
    if (N - m <= l)
        return (N - l) * mu;
    return m * mu;
}

double calc_Theta(int N, int n, double lambda, double mu, int m) {
    double sum = 0.0;
    for (int j = n + 1; j <= N; j++) {
        double mul = 1.0;
        for (int l = n; l <= j - 1; l++) {
            mul *= mu_l(l, N, m, mu) / (l * lambda);
        }
        sum += mul / (j * lambda);
    }
    return sum + 1 / (n * lambda);
}

std::vector<double> calc_Theta_vector(int N, int n, double lambda, double mu, int m) {
    std::vector<double> Theta_vector(N - n + 1);
    for (int i = n; i <= N; i++)
        Theta_vector[i - n] = calc_Theta(N, i, lambda, mu, m);
    return Theta_vector;
}

double calc_T(int N, int n, double lambda, double mu, int m) {
    double T = 1.0 / mu_l(0, N, m, mu);
    if (n == 1)
        return T;

    double mul = 1.0;
    for (int l = 1; l <= n - 1; l++)
        mul *= l * lambda / mu_l(l, N, m, mu);

    T *= mul;

    double sum = 0.0;
    for (int j = 1; j <= n - 1; j++) {
        mul = 1.0;
        for (int l = j; l <= n - 1; l++)
            mul *= l * lambda / mu_l(l, N, m, mu);
        sum += mul / (j * lambda);
    }

    return T + sum;
}

std::vector<double> calc_T_vector(int N, int n, double lambda, double mu, int m) {
    std::vector<double> T_vector(N - n + 1);
    for (int i = n; i <= N; i++)
        T_vector[i - n] = calc_T(N, i, lambda, mu, m);
    return T_vector;
}

std::string vector_to_string(std::vector<double> vec, int precision = 12) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << std::fixed << std::setprecision(precision) << vec[i];
        if (i < vec.size() - 1) {
            oss << ",";
        }
    }
    return oss.str();
}

std::string make_table_row(int Num, double lambda, int mu, int m, int n, std::vector<double> Theta, std::vector<double> T, int precision = 12) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision);
    oss << Num << ";" << lambda << ";" << mu << ";" << m << ";" << n << ";" << vector_to_string(Theta, precision) << ";" << vector_to_string(T, precision);
    return oss.str();
}

void make_table() {
    int N = 65536;
    std::vector<double> lambda_ = {1e-5, 1e-6, 1e-7};
    std::vector<int> mu_ = {1, 10, 100, 1000};
    std::vector<int> m_ = {1, 2, 3};
    std::string table = "Num;lambda;mu;m;n;Theta;T";
    int n = 65527;
    int num = 0;
    std::ofstream f("data/table.csv");
    std::cout << "num;lambda;mu;m;n;theta;t\n";
    for (const auto &lambda : lambda_)
        for (const auto &mu : mu_)
            for (const auto &m : m_) {
                std::cout << make_table_row(num++, lambda, mu, m, n, calc_Theta_vector(N, n, lambda, mu, m), calc_T_vector(N, n, lambda, mu, m)) + "\n";
            }
}

int main() {
    std::filesystem::create_directory("data");
    std::filesystem::create_directory("graphs");
    make_table();

    std::cout << "Data generated successfully\n";

    return 0;
}
