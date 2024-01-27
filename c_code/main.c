/*********************************************************
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef float float32;
typedef double float64;
typedef struct _particle particle;

#define Kb 1e-3
#define NUM_TIME_STEPS 1000000
#define _TIME_STEP 0.01

long seed = -142;

int random_int(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    assert (n <= RAND_MAX);

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew
    assert (end > 0);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}
















struct _particle{
    float64 mass;
    float64 charge;
    float64 *position;
    float64 *velocity;
    float64 *net_force;
};

float64 dvdt1(float64 x, float64 y, float64 z, float64 damping, float64 Temperature){
    return -10 * y - damping * z;
}


float64 dxdt1(float64 x, float64 y, float64 z, float64 damping, float64 Temperature){
    return z;
}


void rk4(particle *p, float64 x, int step, float64 dx, float64 (*dydx)(float64, float64, float64, float64, float64), float64 (*dzdx)(float64, float64, float64, float64, float64), float64 damping, float64 T){
    
    float64 y; float64 z;
    y = p->position[step];
    z = p->velocity[step];

    float64 rand_num = 2 * (rand() / 1000000000.0) - 1;
    // printf("%f\n", 2 * (rand() / 1000000000.0) - 1);
    z = z + 600 * Kb * T * damping * rand_num;
    
    float64 k1;   float64 k2;  float64 k3; float64 k4; float64 h1;  float64 h2;  float64 h3;  float64 h4;
    
    k1 = dx*dydx(x, y, z, damping, T);
    h1 = dx*dzdx(x, y, z, damping, T);
    k2 = dx*dydx(x+dx/2., y+k1/2., z+h1/2., damping, T);
    h2 = dx*dzdx(x+dx/2., y+k1/2., z+h1/2., damping, T);
    k3 = dx*dydx(x+dx/2., y+k2/2., z+h2/2., damping, T);
    h3 = dx*dzdx(x+dx/2., y+k2/2., z+h2/2., damping, T);
    k4 = dx*dydx(x+dx, y+k3, z+h3, damping, T);
    h4 = dx*dzdx(x+dx, y+k3, z+h3, damping, T);

    y = y + 1./6.*(k1+2*k2+2*k3+k4);
    z = z + 1./6.*(h1+2*h2+2*h3+h4);
    
    p->position[step + 1] = y;
    p->velocity[step + 1] = z;
}

int main(int argc, char **argv){
    particle p;
    p.mass = 4;
    p.charge = 0;
    p.position = malloc(sizeof(float64) * NUM_TIME_STEPS);
    p.velocity = malloc(sizeof(float64) * NUM_TIME_STEPS);
    p.net_force = malloc(sizeof(float64) * NUM_TIME_STEPS);

    float64 *energy = malloc(sizeof(float64) * NUM_TIME_STEPS);

    float64 inital_position = 3;
    float64 inital_velocity = 3;

    float64 time = 0;
    float64 dt = _TIME_STEP;
    
    p.position[0] = inital_position;
    p.velocity[0] = inital_velocity;

    float64 damping = 0;
    float64 T = 300;
    float64 (*dvdt1_ptr)(float64 , float64 , float64 , float64 , float64 ) = &dvdt1; // type for conciseness
    float64 (*dxdt1_ptr)(float64 , float64 , float64 , float64 , float64 ) = &dxdt1; // type for conciseness


    for(int i = 0; i < NUM_TIME_STEPS; i++){
        rk4(&p, time, i, dt, dxdt1_ptr, dvdt1_ptr, damping, T);
        time = time + dt;

    }


    FILE *write_ptr;
    FILE *velocity_write_ptr;
    write_ptr = fopen("harmonic_oscillator_position.bin","wb");  // w for write, b for binary
    velocity_write_ptr = fopen("harmonic_oscillator_velocity.bin","wb");  // w for write, b for binary

    fwrite(p.position, sizeof(p.position[0]), NUM_TIME_STEPS, write_ptr);
    fwrite(p.velocity, sizeof(p.velocity[0]), NUM_TIME_STEPS, velocity_write_ptr);

    free(p.position);
    free(p.velocity);
    free(p.net_force);
    free(energy);
    fclose(write_ptr);
    fclose(velocity_write_ptr);

    return 0;
} //main