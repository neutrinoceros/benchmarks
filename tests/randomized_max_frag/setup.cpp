#include "idefix.hpp"
#include "setup.hpp"

real PM; // particle mass

// Initialisation routine. Can be used to allocate
// Arrays or variables which are used later on
Setup::Setup(Input &input, Grid &grid, DataBlock &data, Output &output) {
  PM = input.Get<real>("Setup", "mass", 0);
}

void Setup::InitFlow(DataBlock &data) {
  DataBlockHost d(data);

  // init flow
  for(int k = 0; k < d.np_tot[KDIR] ; k++) {
    for(int j = 0; j < d.np_tot[JDIR] ; j++) {
      for(int i = 0; i < d.np_tot[IDIR] ; i++) {
        d.Vc(RHO,k,j,i) = ONE_F;
        d.Vc(VX1,k,j,i) = ZERO_F;
        d.Vc(VX2,k,j,i) = ZERO_F;
        d.Vc(VX3,k,j,i) = ZERO_F;
      }
    }
  }

  // randomized initial positions
  for(int k = 0; k < d.nParticles; k++) {
    d.Ps(PX1,k) = d.xbeg[KDIR] + idfx::randm() * (d.xend[KDIR] - d.xbeg[KDIR]);
    d.Ps(PX2,k) = d.xbeg[KDIR] + idfx::randm() * (d.xend[KDIR] - d.xbeg[KDIR]);
    d.Ps(PX3,k) = d.xbeg[KDIR] + idfx::randm() * (d.xend[KDIR] - d.xbeg[KDIR]);
    d.Ps(PVX1,k) = ZERO_F;
    d.Ps(PVX2,k) = ZERO_F;
    d.Ps(PVX3,k) = ZERO_F;

    d.Ps(PMASS,k) = PM;

    // add particle velocity in a process-dependent direction
    //d.Ps(DIMENSIONS + idfx::prank%DIMENSIONS, k) = pow(-1, k) * ONE_F;

    // kill one-out-of two particles
    if(k%2==0) d.PisActive(k) = false;
  }
  d.SyncToDevice();
}

// Analyse data to produce an output
void MakeAnalysis(DataBlock & data) {

}
