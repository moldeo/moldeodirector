#ifndef MOCONNECTIONSWINDOW_H
#define MOCONNECTIONSWINDOW_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#ifdef WXART2D
#include "wxart2d.h"

//(*Headers(moConnectionsWindow)
#include <wx/panel.h>
//*)

#include <wx/scrolwin.h>
#include <wx/bitmap.h>


class a2dConnector: public a2dWindowViewConnector
{
    A2D_DECLARE_EVENT_TABLE()

public:

    a2dConnector();

    void SetDisplayWindow( a2dDocumentViewWindow* display );

    void OnPostCreateView( a2dTemplateEvent& event );
    void OnPostCreateDocument( a2dTemplateEvent& event );
	void OnDisConnectView(  a2dTemplateEvent& event );
};

//! pin specific for Resistor and Capacitor and Gnd objects.
class moPin: public a2dPin
{
    DECLARE_DYNAMIC_CLASS(moPin)

public:
    //! constructor
    moPin();

    //! constructor
    moPin( a2dCanvasObject* parent, const wxString& name, a2dPinClass* pinclass,  double xc, double yc, double angle = 0 , int w = 0, int h = 0,  int radius = 0 );

    //! copy constructor
    moPin( const a2dPin &other, CloneOptions options );

    //! destructor
    ~moPin();

    //! clone this object
    a2dObject* Clone( CloneOptions options ) const;

    //! Pins of this class can only connect to ElementWire pins and ElementObject pins

    static a2dPinClass* ElementObject;
    //static a2dPinClass* ElementOutlet;
    //static a2dPinClass* ElementInlet;
    //! Pins of this class can only connect to ElementObject pins
    static a2dPinClass* ElementWire;

    //! called to initialize static stockobjects
    static void InitializeExtraClasses();

protected:
    void DoRender( a2dIterC& ic, OVERLAP clipparent );
    a2dBoundingBox DoGetUnTransformedBbox( a2dBboxFlags flags = a2dCANOBJ_BBOX_NON ) const;

private:
    //!this is a not implemented copy constructor that avoids automatic creation of one
    moPin( const a2dPin &other );
};


class moPinInlet : public moPin {

  public:

};


class moPinOutlet : public moPin {

  public:

};


class ElementConnectionGenerator : public a2dConnectionGenerator
{

public:

    ElementConnectionGenerator();
    ~ElementConnectionGenerator();

    virtual a2dPinClass* GetPinClassForTask( a2dPinClass* pinClass, a2dConnectTask task, a2dCanvasObject* obj ) const;

};

moDeclareDynamicArray( moPinOutlet*, moPinOutlets )
moDeclareDynamicArray( moPinInlet*, moPinInlets )


class moMoldeoCanvasObject : public a2dRect, public moIDirectorActions {

    DECLARE_DYNAMIC_CLASS(moMoldeoCanvasObject)

    public:

        moMoldeoCanvasObject();
        moMoldeoCanvasObject( double xc, double yc, double w, double h, double angle, double radius, moMobDescriptor p_MobDescriptor, moIDirectorActions* parenthandler );
        moMoldeoCanvasObject( const moMoldeoCanvasObject &other, CloneOptions options );
        virtual ~moMoldeoCanvasObject();

        //! clone this object
        virtual a2dObject* Clone( CloneOptions options ) const;
        void OnCanvasObjectMouseEvent( a2dCanvasObjectMouseEvent& event );

public:
    static const a2dPropertyIdString PROPID_refdes;
    static const a2dPropertyIdString PROPID_spice;
    static const a2dPropertyIdString PROPID_freeda;

    wxString GetNetlistLine( wxString simulator );

    const a2dNamedProperty* FindProperty( const wxString name );

    //! Get name of net connected to pin
    /*
        The name of the net is determined by a label connected to the net.
        If no label is connected, it will determine a net name, based on the
        components refdes and pin name. Eg. for a component Q1 with pin e
        the netname will become netQ1_e.
    */
    static wxString GetNetName( a2dPin* pin );

    private:
    //! Private function to determine all pins connected to a net.
    static void GetNetPins(  a2dCanvasObjectList* pins, a2dPin* pin );

    public:
        virtual void Render (a2dIterC &ic, OVERLAP clipparent);

    public:
        ///DIRECTOR ACTIONS

        //moDirectorStatus    SetMob( moMobDescriptor p_MobDescriptor );
        moDirectorStatus    SetMob( moMobDescriptor p_MobDescriptor );
        moMobDescriptor&    GetMob();

        moMobDescriptor     m_MobDescriptor;

    protected:

        //void OnLeftDown( wxMouseEvent& event );
        //void OnHandleEvent (a2dHandleMouseEvent &event);
        //bool ProcessCanvasObjectEvent( a2dIterC &ic, a2dHitEvent &hitEvent );

        //void OnEnterObject (a2dCanvasObjectMouseEvent &event);
        //void OnLeaveObject (a2dCanvasObjectMouseEvent &event);

        a2dText*  m_pMoldeoCanvasObjectTitle;

        moPinInlets    m_PinInlets;

        moPinInlets    m_PinOutlets;

        A2D_DECLARE_EVENT_TABLE()

};

moDeclareDynamicArray( moMoldeoCanvasObject*, moMoldeoCanvasObjects )


class moConnectionsToolContr : public a2dStToolContr {

  public:

        moConnectionsToolContr( a2dCanvasView* view, wxFrame* where);
        virtual ~moConnectionsToolContr();

        void OnMouseEvent(wxMouseEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnKeyUp(wxKeyEvent& event);


        a2dDragTool*  m_pDragTool;
        a2dSelectTool*  m_pSelectTool;

    A2D_DECLARE_EVENT_TABLE()
};


class moConnectionsWindow: public wxPanel, public moIDirectorActions
{
	public:

		moConnectionsWindow(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moConnectionsWindow();
		void Init( moIDirectorActions*   pActionsHandler );

		//(*Declarations(moConnectionsWindow)
		//*)

    public:
        /// reload everything
        moDirectorStatus ProjectUpdated( moProjectDescriptor p_projectdescriptor );

        /// only mob updated, search for mob and update it....
        moDirectorStatus MobUpdated( moMobDescriptor p_MobDesc );

        void DeleteAll();

	protected:

		//(*Identifiers(moConnectionsWindow)
		//*)

	private:

		//(*Handlers(moConnectionsWindow)
		void OnPaint(wxPaintEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

        void OnSize(wxSizeEvent& event);
        //void OnMouseEvents(wxMouseEvent& event);

        a2dDrawer2D*            m_pDrawer2D;
        a2dCanvas*              m_pCanvas;
        a2dCanvasDocument*      m_pConnectionsCanvasDocument;
        moMoldeoCanvasObjects   m_MoldeoCanvasObjects;


		DECLARE_EVENT_TABLE()
};

#endif

#endif
