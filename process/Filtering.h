//
// Created by 森智希 on 2023/05/31.
//

#ifndef IMAGEPROCESSING_FILTERING_H
#define IMAGEPROCESSING_FILTERING_H

#include <random>
#include <algorithm>
#include <Eigen/SparseCore>
#include <Eigen/IterativeLinearSolvers>
#include "image.h"
#include "params.h"

namespace bip {
    template<typename T>
    void addNoise(Image <T> &img, double sigma) {
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::normal_distribution<> dist(0.0, sigma);

        for (int c = 0; c < img.dims(); c++) {
            for (int x = 0; x < img.cols(); x++) {
                for (int y = 0; y < img.rows(); y++) {
                    img(x, y, c) = (T) std::min(std::max((double) img(x, y, c) + dist(engine), 0.0), 255.0);
                }
            }
        }
    }

    void totalVariationMinimized(Image<float> &img, float rho, float lambda, int iter) {
        int N = img.rows() * img.cols();
        int dim = 2;
        auto co = [&](int x, int y) -> int {
            return x + img.cols() * y;
        };

        using Triplet = Eigen::Triplet<float, int64_t>;
        Eigen::SparseMatrix<float> F(dim * N, N);
        Eigen::SparseMatrix<float> I(N, N);
        std::vector<Triplet> F_trip;
        std::vector<Triplet> I_trip;
        Eigen::VectorXf xx0(N), yy(dim * N), uu(dim * N);

        for (int x = 0; x < img.cols() - 1; x++) {
            for (int y = 0; y < img.rows() - 1; y++) {
                // difference x-axis
                F_trip.emplace_back(Triplet(dim * co(x, y) + 0, co(x + 1, y), 1.0));
                F_trip.emplace_back(Triplet(dim * co(x, y) + 0, co(x, y), -1.0));

                // difference y-axis
                F_trip.emplace_back(Triplet(dim * co(x, y) + 1, co(x, y + 1), 1.0));
                F_trip.emplace_back(Triplet(dim * co(x, y) + 1, co(x, y), -1.0));
            }
        }
        for (int x = 0; x < img.cols(); x++) {
            for (int y = 0; y < img.rows(); y++) {
                I_trip.emplace_back(Triplet(co(x, y), co(x, y), 1.0));
                xx0(co(x, y)) = img(x, y, 0);
            }
        }
        F.setFromTriplets(F_trip.begin(), F_trip.end());
        I.setFromTriplets(I_trip.begin(), I_trip.end());

        yy.setOnes();
        uu.setOnes();

        // Eigen::SparseLU<Eigen::SparseMatrix<float>> solver;
        Eigen::SparseMatrix<float> lhs = I + rho * F.transpose() * F;

        std::cout << "row: " << lhs.rows() << ", col: " << lhs.cols() << ", non zero: " << lhs.nonZeros() << std::endl;
        Eigen::BiCGSTAB<Eigen::SparseMatrix<float>> solver;
        solver.compute(lhs);
        Eigen::VectorXf xx;

        // calculate iteration
        for (int i = 0; i < iter; i++) {
            Eigen::VectorXf rhs = F.transpose() * (rho * yy - uu) + xx0;
            xx = solver.solve(rhs);

            Eigen::VectorXf Fxx = F * xx;
            for (int j = 0; j < yy.size(); j++) {
                float z = Fxx(j) + uu(j) / rho;
                yy(j) = z > 0 ? std::max(z - lambda / rho, 0.0f) : std::min(z + lambda / rho, 0.0f);
                uu(j) += rho * (Fxx(j) - yy(j));
            }
        }

        for (int y = 0; y < img.cols(); y++) {
            for (int x = 0; x < img.rows(); x++) {
                img(x, y, 0) = xx(co(x, y));
            }
        }
    }
}
#endif //IMAGEPROCESSING_FILTERING_H
