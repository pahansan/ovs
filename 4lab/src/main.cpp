#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

std::string to_scientific_string(double value) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(0) << value;
    std::string s = oss.str();

    // Убираем знак + в экспоненте если нужно
    size_t e_pos = s.find('e');
    if (e_pos != std::string::npos && s[e_pos + 2] == '+') {
        s.erase(e_pos + 2, 1); // удаляем '+'
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

void exp2_1() {
    int N = 65536;
    double lambda = 1e-5;
    int m = 1;

    std::vector<double> mu_values = {1, 10, 100, 1000};

    for (double mu : mu_values) {
        std::ofstream f("data/exp2_1/theta_mu_" + std::to_string((int)mu) +
                        ".dat");

        for (int n = 65527; n <= 65536; n++) {
            f << n << " " << std::setprecision(40)
              << calc_Theta(N, n, lambda, mu, m) << '\n';
        }
    }
}

void exp2_2() {
    int N = 65536;
    double mu = 1;
    int m = 1;

    std::vector<double> lambda_values = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};

    for (double lambda : lambda_values) {
        std::ofstream f("data/exp2_2/theta_lambda_" +
                        to_scientific_string(lambda) + ".dat");

        for (int n = 65527; n <= 65536; n++) {
            f << n << " " << std::setprecision(40)
              << calc_Theta(N, n, lambda, mu, m) << '\n';
        }
    }
}

void exp2_3() {
    int N = 65536;
    double mu = 1;
    double lambda = 1e-5;

    std::vector<int> m_values = {1, 2, 3, 4};

    for (int m : m_values) {
        std::ofstream f("data/exp2_3/theta_m_" + std::to_string(m) + ".dat");

        for (int n = 65527; n <= 65536; n++) {
            f << n << " " << std::setprecision(40)
              << calc_Theta(N, n, lambda, mu, m) << '\n';
        }
    }
}

void exp3_1() {
    int N = 1000;
    double lambda = 1e-3;
    int m = 1;

    std::vector<double> mu_values = {1, 2, 4, 6};

    for (double mu : mu_values) {
        std::ofstream f("data/exp3_1/T_mu_" + std::to_string((int)mu) + ".dat");

        for (int n = 900; n <= 1000; n += 10) {
            f << n << " " << std::setprecision(40)
              << calc_T(N, n, lambda, mu, m) << '\n';
        }
    }
}

void exp3_2() {
    int N = 8192;
    double mu = 1;
    int m = 1;

    std::vector<double> lambda_values = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};

    for (double lambda : lambda_values) {
        std::ofstream f("data/exp3_2/T_lambda_" + to_scientific_string(lambda) +
                        ".dat");

        for (int n = 8092; n <= 8192; n += 10) {
            f << n << " " << std::setprecision(40)
              << calc_T(N, n, lambda, mu, m) << '\n';
        }
    }
}

void exp3_3() {
    int N = 8192;
    double mu = 1;
    double lambda = 1e-5;

    std::vector<int> m_values = {1, 2, 3, 4};

    for (int m : m_values) {
        std::ofstream f("data/exp3_3/T_m_" + std::to_string(m) + ".dat");

        for (int n = 8092; n <= 8192; n += 10) {
            f << n << " " << std::setprecision(40)
              << calc_T(N, n, lambda, mu, m) << '\n';
        }
    }
}

int main() {
    std::filesystem::create_directory("data");
    std::filesystem::create_directory("data/exp2_1");
    std::filesystem::create_directory("data/exp2_2");
    std::filesystem::create_directory("data/exp2_3");
    std::filesystem::create_directory("data/exp3_1");
    std::filesystem::create_directory("data/exp3_2");
    std::filesystem::create_directory("data/exp3_3");
    std::filesystem::create_directory("graphs");
    std::filesystem::create_directory("graphs/exp2_1");
    std::filesystem::create_directory("graphs/exp2_2");
    std::filesystem::create_directory("graphs/exp2_3");
    std::filesystem::create_directory("graphs/exp3_1");
    std::filesystem::create_directory("graphs/exp3_2");
    std::filesystem::create_directory("graphs/exp3_3");

    exp2_1();
    exp2_2();
    exp2_3();
    exp3_1();
    exp3_2();
    exp3_3();

    std::cout << "Data generated successfully\n";

    return 0;
}
