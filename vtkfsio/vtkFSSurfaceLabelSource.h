/**
 * @file  vtkFSSurfaceLabelSource.h
 * @brief Reads a label, maps it to a surface, and outputs PolyData
 *
 * A FreeSurfer label file consists of a list of vertices that may
 * also have associated vertex indices. This will read in a label, map
 * it to a surface, fill in any holes, and output PolyData, which will
 * appear to be a subset of the surface PolyData.
 */
/*
 * Original Author: Kevin Teich
 * CVS Revision Info:
 *    $Author: kteich $
 *    $Date: 2007/05/15 19:33:14 $
 *    $Revision: 1.2 $
 *
 * Copyright (C) 2002-2007,
 * The General Hospital Corporation (Boston, MA). 
 * All rights reserved.
 *
 * Distribution, usage and copying of this software is covered under the
 * terms found in the License Agreement file named 'COPYING' found in the
 * FreeSurfer source code root directory, and duplicated here:
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferOpenSourceLicense
 *
 * General inquiries: freesurfer@nmr.mgh.harvard.edu
 * Bug reports: analysis-bugs@nmr.mgh.harvard.edu
 *
 */


#ifndef __vtkFSSurfaceLabelSource_h
#define __vtkFSSurfaceLabelSource_h

#include <vector>

class vtkPolyData;
class vtkFSSurfaceSource;

#include "vtkSource.h"
extern "C" {
#include "mrisurf.h"
}

class vtkFSSurfaceLabelSource : public vtkSource {
public:

  static vtkFSSurfaceLabelSource *New();
  vtkTypeRevisionMacro(vtkFSSurfaceLabelSource,vtkSource);

  // Description:
  // vtkFSSurfaceLabelSource needs an MRIS object on which to map the
  // label. The white coordinates should also be available for this
  // surface.
  vtkSetMacro(Mris,MRIS*);
  vtkGetMacro(Mris,MRIS*);

  // Description:
  // The file name of the label to read.
  vtkSetStringMacro(LabelFileName);
  vtkGetStringMacro(LabelFileName);

  // Description:
  // Get the output of this source.
  vtkPolyData* GetOutput ();
  vtkPolyData* GetOutput ( int inOutput );
  void         SetOutput ( vtkPolyData* iOutput );

protected:

  vtkFSSurfaceLabelSource();
  ~vtkFSSurfaceLabelSource();

  void Execute();

  char* LabelFileName;
  MRIS* Mris;

private:
  vtkFSSurfaceLabelSource(const vtkFSSurfaceLabelSource&);  // Not implemented.
  void operator=(const vtkFSSurfaceLabelSource&);  // Not implemented.
};

#endif
