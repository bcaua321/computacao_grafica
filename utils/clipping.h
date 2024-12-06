#ifndef CLIPPING_H
#define CLIPPING_H

#include <bitset>
#include <vector>
#include "../points.h"

using namespace std;

class Clipping
{
public:
    Clipping() {}
    Clipping(double bordaSup, double bordaInf, double bordaDir, double bordaEsq) {
        this->bordaDir = bordaDir;
        this->bordaEsq = bordaEsq;
        this->bordaSup = bordaSup;
        this->bordaInf = bordaInf;
    }

    string computeCode(double x, double y) {
        string code = "0000"; // TOP | BOTTOM | RIGHT | LEFT

        if (x < this->bordaEsq) code[3] = '1';  // LEFT
        else if (x > this->bordaDir) code[2] = '1'; // RIGHT
        if (y < this->bordaInf) code[1] = '1';  // BOTTOM
        else if (y > this->bordaSup) code[0] = '1'; // TOP

        return code;
    }

    // Função para verificar se dois códigos de região têm interseção
    bool hasCommonBit(const string &code1, const string &code2) {
        for (int i = 0; i < 4; i++) {
            if (code1[i] == '1' && code2[i] == '1') {
                return true; // Há um bit em comum
            }
        }
        return false;
    }

    // Algoritmo Cohen-Sutherland com strings
    void cohenSutherlandClip(vector<vector<double>>& pointA, vector<vector<double>>& pointB) {
        double x1 = pointA[0][0], y1 = pointA[0][1];
        double x2 = pointB[0][0], y2 = pointB[0][1];

        string code1 = computeCode(x1, y1);
        string code2 = computeCode(x2, y2);

        bool accept = false;

        while (true) {
            if (code1 == "0000" && code2 == "0000") {
                // Ambos os pontos estão dentro
                accept = true;
                break;
            } else if (hasCommonBit(code1, code2)) {
                // Ambos os pontos estão fora da mesma região
                break;
            } else {
                // A linha é parcialmente dentro
                string codeOut;
                double x, y;

                // Escolhe um ponto fora (codeOut)
                if (code1 != "0000") codeOut = code1;
                else codeOut = code2;

                // Calcula o ponto de interseção
                if (codeOut[0] == '1') { // Interseção com o topo
                    x = x1 + (x2 - x1) * (this->bordaSup - y1) / (y2 - y1);
                    y = this->bordaSup;
                } else if (codeOut[1] == '1') { // Interseção com a parte inferior
                    x = x1 + (x2 - x1) * (this->bordaInf - y1) / (y2 - y1);
                    y = this->bordaInf;
                } else if (codeOut[2] == '1') { // Interseção com a direita
                    y = y1 + (y2 - y1) * (this->bordaDir - x1) / (x2 - x1);
                    x = this->bordaDir;
                } else if (codeOut[3] == '1') { // Interseção com a esquerda
                    y = y1 + (y2 - y1) * (this->bordaEsq - x1) / (x2 - x1);
                    x = this->bordaEsq;
                }

                // Atualiza o ponto fora e seu código
                if (codeOut == code1) {
                    x1 = x; y1 = y;
                    pointA[0][0]= x1;
                    pointA[0][1] = y1;
                    code1 = computeCode(x1, y1);
                } else {
                    x2 = x; y2 = y;
                    pointB[0][0] = x2;
                    pointB[0][1] = y2;
                    code2 = computeCode(x2, y2);
                }
            }
        }
    }


private:
    double bordaSup, bordaInf, bordaDir, bordaEsq;
};

#endif // CLIPPING_H
