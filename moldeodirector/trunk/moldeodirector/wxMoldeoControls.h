#ifndef WXMOLDEOCONTROLS_H
#define WXMOLDEOCONTROLS_H

///GENERAL CONTROLS

///SLIDER CONTROLS
    #include "wxMoLevelCtrl.h"
    #include "wxMoRotaryCtrl.h"

    ///TODO LIST
    /// wxMoTexLevelCtrl.h  ///texture based
    /// wxMoTexRotaryCtrl.h ///texture based

    ///with colour gradient:  SetStartColour() SetEndColour()
    /// wxMoColourLevelCtrl.h
    /// wxMoColourRotaryCtrl.h
    /// wxMoColorCircleCtrl.h /// a complete circle.... (conic)
    /// wxMoColorRectCtrl.h /// a complete cuad.... (cuadric)

///VECTOR POSITION CONTROLS

    ///position orientaded ( 2d )
    /// wxMoPointerCtrl.h    /// a green cross over a cuad with coord text...

    ///position orientaded ( 3d )
    /// wxMoSphereCtrl.h    /// a sphere rotated with the mouse... (ideal for vector direction)  ....


///TIMELINE CONTROLS
    /// wxMoTimelineRulerBandCtrl o wxMoRibbonCtrl
    #include "wxMoTimelineRulerCtrl.h"
    ///A control sizer to set the dimension of a video
    /// wxMoTimelineBandCtrl o wxMoRibbonCtrl
    #include "wxMoTimelineBandCtrl.h"
    ///A control sizer to set the start and end of a layer or parameter value

///FLOW CONTROL
    /// base object, a frame with controls to move and resize.... with a title
    #include "wxMoldeoObjectCtrl.h"
    #include "wxMoldeoPinCtrl.h"
    #include "wxMoldeoLineCtrl.h"
    #include "wxMoldeoObjectCanvas.h"



#endif
