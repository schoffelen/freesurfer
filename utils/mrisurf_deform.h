#pragma once
/*
 * @file utilities common to mrisurf*.c but not used outside them
 *
 */
/*
 * surfaces Author: Bruce Fischl, extracted from mrisurf.c by Bevin Brett
 *
 * $ © copyright-2014,2018 The General Hospital Corporation (Boston, MA) "MGH"
 *
 * Terms and conditions for use, reproduction, distribution and contribution
 * are found in the 'FreeSurfer Software License Agreement' contained
 * in the file 'LICENSE' found in the FreeSurfer distribution, and here:
 *
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferSoftwareLicense
 *
 * Reporting: freesurfer@nmr.mgh.harvard.edu
 *
 */
// Configurable support for checking that some of the parallel loops get the same
// results regardless of thread count
//
// Two common causes of this being false are
//          floating point reductions
//          random numbers being generated by parallel code 
//

#include "mrisurf_vals.h"

#define VERTEX_INTERIOR 1
#define VERTEX_BORDER   2
#define VERTEX_CHULL    3

int mrisStoreVtotalInV3num(MRI_SURFACE *mris);

int mrisCalculateCanonicalFaceCentroid(MRI_SURFACE *mris, int fno, float *px, float *py, float *pz);

int mrisFlipPatch(MRI_SURFACE *mris);
int mrisTearStressedRegions(MRI_SURFACE *mris, INTEGRATION_PARMS *parms);
int mrisSmoothBoundaryNormals(MRI_SURFACE *mris, int niter);


int mrisLogStatus(MRI_SURFACE *mris, INTEGRATION_PARMS *parms, FILE *fp, float dt, float old_sse);

int mrisOrientSurface     (MRI_SURFACE *mris);
int mrisOrientPlane       (MRI_SURFACE *mris);
int mrisRemoveNegativeArea(MRI_SURFACE *mris, INTEGRATION_PARMS *parms, int base_averages, float min_area_pct, int max_passes);
    
static int transform(float *xptr, float *yptr, float *zptr, float nx, float ny, float nz, float d)
{
  float x = *xptr, y = *yptr, z = *zptr;

  *zptr = nx * x + ny * y + nz * z;
  *yptr = -ny / d * x + nx / d * y;
  *xptr = nx * nz / d * x + ny * nz / d * y - d * z;
  /*
    printf("transform {%f,%f,%f} -> {%f,%f,%f}\n",
    x,y,z,*xptr,*yptr,*zptr);
  */
  return (NO_ERROR);
}

int mrisComputeDuraTerm(MRI_SURFACE *mris, double l_dura, MRI *mri_dura, double dura_thresh);

int mrisComputeSpringTerm           (MRI_SURFACE *mris, double l_spring);
int mrisComputeLaplacianTerm        (MRI_SURFACE *mris, double l_laplacian);
int mrisComputeNormalizedSpringTerm (MRI_SURFACE *mris, double l_spring);

int mrisProjectSurface                     (MRIS*    mris);
int mrisProjectSurface                     (MRIS_MP* mris);

int mrisApplyTopologyPreservingGradient    (MRI_SURFACE *mris, double dt, int which_gradient);
int mrisApplyGradientPositiveAreaPreserving(MRI_SURFACE *mris, double dt);
int mrisApplyGradientPositiveAreaMaximizing(MRI_SURFACE *mris, double dt);

int mrisApplyTopologyPreservingGradient(MRI_SURFACE *mris, double dt, int which_gradient);
int mrisCountCompressed(MRI_SURFACE *mris, double min_dist);


int MRISrestoreExtraGradients(MRI_SURFACE *mris);

int mrisLogStatus(MRI_SURFACE *mris, INTEGRATION_PARMS *parms, FILE *fp, float dt, float old_sse);

struct MRIScomputeSSE_asThoughGradientApplied_ctx {
    MRIScomputeSSE_asThoughGradientApplied_ctx();
    ~MRIScomputeSSE_asThoughGradientApplied_ctx();
    struct Impl;
    Impl* const _impl;
};

double MRIScomputeSSE_asThoughGradientApplied(
    MRIS*              mris, 
    double             delta_t, 
    INTEGRATION_PARMS* parms,
    MRIScomputeSSE_asThoughGradientApplied_ctx& ctx);     

