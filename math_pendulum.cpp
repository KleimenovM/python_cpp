//
// Created by kleim on 9/25/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

float square(float x){
    return x * x;
}

void kah_half(float &comp, float delta, float &old){
    float temp1, temp2;
    temp1 = delta - comp; // delta - compensation
    temp2 = old + temp1; // new temporary value
    comp = (temp2 - old) - temp1; // new compensation
    old = temp2; // new phi
}

class TimeMoment{
private:
    float omega_2;
    float dt;
public:
    float t;
    float phi;
    float xi;
    float init_inv;
    float inv;
    // kahan compensations
    float phi_c, xi_c;

    TimeMoment(float omega, float delta): omega_2(square(omega)), dt(delta){
        t = 0.f;
        phi = 0.f;
        xi = omega;
        inv = square(xi) + omega_2 * square(phi);
        init_inv = inv;
        phi_c = 0.f;
        xi_c = 0.f;
    }

    void step(){
        t += dt;
        phi += xi * dt;
        xi -= omega_2 * phi * dt;
        float next_inv = square(xi) + omega_2 * square(phi);
        inv = next_inv / init_inv - 1;
    }

    void kahStep(){
        float phi_t1, phi_t2, xi_t1, xi_t2;
        t += dt;

        /* phi_t1 = xi * dt - phi_c; // delta - compensation
        phi_t2 = phi + phi_t1; // new temporary value
        phi_c = (phi_t2 - phi) - phi_t1; // new compensation
        phi = phi_t2; // new phi

        xi_t1 = - (omega_2 * phi) * dt - xi_c;
        xi_t2 = xi + xi_t1;
        xi_c = (xi_t2 - xi) - xi_t1;
        xi = xi_t2; */

        kah_half(phi_c, xi * dt, phi);
        kah_half(xi_c, -(omega_2 * phi) * dt, xi);



        // std::cout << phi << '\t' << xi << '\n';

        float next_inv = square(xi) + omega_2 * square(phi);
        inv = next_inv / init_inv - 1;
    }
};

void get_data_out(const std::vector<TimeMoment>& dat, const std::string& filename){
    std::cout << filename << " writing started" << std::endl;
    {
        std::ofstream out_file(filename);
        for(const auto & i : dat){
            auto cur_dat = &i;
            out_file << cur_dat->t << '\t' << cur_dat->phi << '\t' << cur_dat->xi << '\t' << cur_dat->inv << '\n';
        }
        out_file.close();
    }
    std::cout << "writing finished" << std::endl;
}

int main(){
    float DeltaT = 0.000001;

    TimeMoment timeMoment (1, DeltaT);
    std::vector<TimeMoment> list;

    int period = 10000000;
    for(int i = 0; i < period; i++){
        timeMoment.step();
        if (i % 10 == 0)
            list.push_back(timeMoment);
    }

    get_data_out(list, "result1.txt");

    TimeMoment timeMoment2(1, DeltaT);
    list.clear();
    for(int i = 0; i < period; i++){
        timeMoment2.kahStep();
        if(i % 10 == 0)
            list.push_back(timeMoment2);
    }

    get_data_out(list, "result2.txt");
    return 0;
}